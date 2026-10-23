#include "client.hpp"

#include <algorithm>

#include "../headers/codes.hpp"

namespace client_mod {

    using namespace bios_protocol;
    using bytegen_mod::Expect;
    namespace rsp = responses;

    namespace {

        inline constexpr uint32_t MAX_STRING_LEN = 1u << 20;    // no real BIOS string gets anywhere near this
        inline constexpr uint32_t PROGRESS_MIN = 4096;          // dump progress only for bigger dumps
        inline constexpr uint32_t PROGRESS_STEP = 1024;
        inline constexpr size_t POST_PAIR_BYTES = 12;
        inline constexpr size_t TELE_QUERY_BYTES = 6;
        inline constexpr size_t TELE_STATUS_BYTES = 25;    // 5 params (cycles, instr, stall, load-use, branch flush), 5 bytes each
        inline constexpr size_t REG_FRAME_BYTES = 31 * 5 + 1;   // after the opening 0x75, includes the closing 0x75
        inline constexpr auto MAX_READ_WAIT = std::chrono::milliseconds{50};

        uint32_t le32(const uint8_t* p) {
            return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8)
                | (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
        }

        std::string strip_nul(const std::string& text) {
            std::string out{};
            out.reserve(text.size());
            for (const char c : text) if (c != '\0') out.push_back(c);
            return out;
        }

        // consecutive program output events become one, so a burst of output is printed in one go
        void append_merged(rsp::Events& out, rsp::Event&& ev) {
            if (const auto* next = std::get_if<rsp::EvProgramOutput>(&ev); next != nullptr && !out.empty()) {
                if (auto* last = std::get_if<rsp::EvProgramOutput>(&out.back())) {
                    last->bytes += next->bytes;
                    return;
                }
            }
            out.push_back(std::move(ev));
        }

    }

    // ------------------------------------------------------------------------------------------------
    // SessionCore: small helpers
    // ------------------------------------------------------------------------------------------------

    SessionCore::SessionCore(const profile_mod::Profile& prof) :
        profile{prof}
    { }

    SessionState SessionCore::idle_state() const {
        return linked ? SessionState::Idle : SessionState::Disconnected;
    }

    // raw bytes never go out while a command is in flight or during the cooldown (BIOS drain protection)
    bool SessionCore::raw_allowed() const {
        return transport_open && (state == SessionState::Idle || state == SessionState::Disconnected
            || state == SessionState::ProgramRunning);
    }

    bool SessionCore::quiet() const {
        return active.has_value() && active->quiet;
    }

    // floor: cooldown_ms since the later of the last host byte and the error arriving
    TimePoint SessionCore::floor_end() const {
        return std::max(cooldown_start, last_host_write) + profile.cooldown_floor();
    }

    TimePoint SessionCore::cap_end() const {
        return cooldown_start + profile.ready_cap();
    }

    void SessionCore::reset_parser() {
        stage = Stage::None;
        own_state = 0;
        after_own = Stage::None;
        pending_f0 = false;
        pending_err.reset();
        auto_net_ack = false;
        data_buf.clear();
        str = StrFrame{};
        mem_expected = 0;
        mem_offset = 0;
        mem_readback = false;
        mem_then_run = false;
        prog_hold.clear();
        hold_deadline.reset();
    }

    void SessionCore::expect_state(uint8_t state_byte, Stage next) {
        stage = Stage::AwaitOwnState;
        own_state = state_byte;
        after_own = next;
    }

    void SessionCore::enter(Stage next, rsp::Events& ev, TimePoint now) {
        stage = next;
        data_buf.clear();
        switch (next) {
            case Stage::Program:
                enter_program(ev, now);
                break;
            case Stage::DdBody:
                dd = rsp::DeviceData{};
                dd_next = DD_PARAM_BIOS;
                dd_phase = DdPhase::Param;
                break;
            case Stage::MemData:
                if (mem_expected == 0) mem_complete(ev, now);
                break;
            default:
                break;
        }
    }

    void SessionCore::begin_parse(const bytegen_mod::Transaction& tx) {
        reset_parser();
        switch (tx.expect) {
            case Expect::SynAck:            expect_state(BIOSST_NET, Stage::SynAck); break;
            case Expect::ConnectAck:        stage = Stage::PostBody; break;     // 0A was already logged before AB
            case Expect::Echo:              expect_state(BIOSST_MSG, Stage::EchoHeader); break;
            case Expect::SelfTest:          expect_state(BIOSST_ST, Stage::SelfTestByte); break;
            case Expect::TelemetrySet:      expect_state(BIOSST_META, Stage::Completion); break;
            case Expect::TelemetryQuery:    expect_state(BIOSST_META, Stage::TeleQuery); break;
            case Expect::TelemetryStatus:   expect_state(BIOSST_META, Stage::TeleStatusOpen); break;
            case Expect::MemDump:
            case Expect::Verify:
                expect_state(BIOSST_MEM, Stage::MemConfirm);
                mem_expected = tx.data_size;
                mem_offset = tx.data_offset;
                mem_readback = tx.expect == Expect::Verify;
                break;
            case Expect::Load:              expect_state(BIOSST_PGLD, Stage::LoadComplete); break;
            case Expect::Run:               expect_state(BIOSST_PGEX, Stage::Program); break;   // no F0 1C at all if no valid program, just EC 01
            case Expect::DeviceData:        expect_state(BIOSST_DD, Stage::DdHeader); break;
        }
    }

    void SessionCore::finish(TxOutcome result) {
        if (!active) return;
        done_seq = tx_seq;
        outcome = result;
        active.reset();
    }

    // completion marker: F0 00 (or F0 50) after the command's own state log
    void SessionCore::finish_ok(rsp::Events& ev) {
        if (active) {
            apply_completion(*active, ev);
            finish(TxOutcome::Ok);
        } else if (auto_net_ack) {
            linked = true;     // the ACK's POST frame was auto-detected (raw 0xAC), same effect as a normal `connect`
        }
        reset_parser();
        response_deadline.reset();
        program_notice_at.reset();
        state = idle_state();
    }

    void SessionCore::apply_completion(const bytegen_mod::Transaction& tx, rsp::Events& ev) {
        switch (tx.expect) {
            case Expect::ConnectAck:
                linked = true;
                break;
            case Expect::SelfTest:
                cache.program_valid = false;    // the memory test overwrites program space
                break;
            case Expect::TelemetrySet:
                if (tx.tele_bios) cache.telemetry.bios = *tx.tele_bios;
                if (tx.tele_prog_reset) cache.telemetry.program_reset = *tx.tele_prog_reset;
                if (!tx.quiet) ev.push_back(rsp::EvTelemetryApplied{});
                break;
            default:
                break;
        }
    }

    // error / client timeout: bump the generation (the writer stops within one chunk and flushes TX),
    // fail the command, then discard everything until the BIOS is ready again
    void SessionCore::start_cooldown(rsp::Events& ev, TimePoint now, TxOutcome result) {
        ++generation;
        finish(result);
        reset_parser();
        response_deadline.reset();
        program_notice_at.reset();
        message_buffer.clear();
        if (!raw_queue.empty()) {
            ev.push_back(rsp::EvRawDropped{raw_queue.size()});
            raw_queue.clear();
        }
        cooldown_start = now;
        cooldown_ready = false;
        cooldown_f0 = false;
        state = SessionState::Cooldown;
        ev.push_back(rsp::EvCooldownStart{});
    }

    // ends only when BOTH the floor has passed and the ready signal (F0 00 / F0 50) arrived,
    // or by the floor alone once the cap is over (with a warning)
    void SessionCore::check_cooldown(rsp::Events& ev, TimePoint now) {
        if (state != SessionState::Cooldown) return;
        if (now < floor_end()) return;
        if (cooldown_ready) {
            end_cooldown(ev, false);
        } else if (now >= cap_end()) {
            end_cooldown(ev, true);
        }
    }

    void SessionCore::end_cooldown(rsp::Events& ev, bool by_fallback) {
        reset_parser();
        state = idle_state();
        ev.push_back(rsp::EvCooldownEnd{by_fallback});
    }

    // unsolicited 50: the BIOS rebooted, clear the cache and go disconnected
    void SessionCore::on_reboot(rsp::Events& ev) {
        ++generation;
        finish(TxOutcome::Rebooted);
        cache.clear();
        linked = false;
        limited = false;
        reset_parser();
        response_deadline.reset();
        program_notice_at.reset();
        message_buffer.clear();
        state = SessionState::Disconnected;
        ev.push_back(rsp::EvReboot{});
    }

    void SessionCore::protocol_mismatch(uint8_t byte, rsp::Events& ev, TimePoint now) {
        ev.push_back(rsp::EvProtocolMismatch{byte});
        if (active && active->expect == Expect::Load) cache.program_valid = false;     // can't tell where the load stopped
        start_cooldown(ev, now, TxOutcome::ProtocolError);
    }

    void SessionCore::bios_error_frame(uint8_t family, uint8_t code, rsp::Events& ev, TimePoint now) {
        ev.push_back(rsp::EvBiosError{bios_error::decode(family, code)});

        // cache rules
        if (family == ERR_TELEMETRY) cache.telemetry = rsp::TelemetrySettings{};   // unknown, re-query after the cooldown
        if (family == ERR_CONNNECT) linked = false;                                // the BIOS cleared its connection bit
        if (family == ERR_CRITICAL) {                                              // EE is followed by a BIOS reset
            cache.telemetry = rsp::TelemetrySettings{ false, false, false };
            cache.program_valid = false;
        }
        // EF 01 mid-load means the data phase began (the old program is gone), EC 02-06 come before it and leave it valid
        if (active && active->expect == Expect::Load && family == ERR_BIOS) cache.program_valid = false;

        start_cooldown(ev, now, TxOutcome::BiosError);
    }

    // ------------------------------------------------------------------------------------------------
    // SessionCore: per byte analysis
    // ------------------------------------------------------------------------------------------------

    rsp::Events SessionCore::on_byte(uint8_t byte, TimePoint now) {
        rsp::Events ev{};
        if (monitor_on) ev.push_back(rsp::EvMonitorByte{byte});

        if (state == SessionState::Cooldown) {
            cooldown_byte(byte, ev, now);
            return ev;
        }
        // keep the deadline alive while bytes keep coming in
        if (state == SessionState::AwaitingResponse && response_deadline) {
            response_deadline = std::max(*response_deadline, now + profile.response_timeout(0));
        }
        if (stage == Stage::Program) {
            program_byte(byte, ev, now);
            return ev;
        }
        if (str.active) {
            str_byte(byte, ev, now);
            return ev;
        }
        if (pending_f0) {
            pending_f0 = false;
            state_byte(byte, ev, now);
            return ev;
        }
        if (pending_err) {
            const auto family = *pending_err;
            pending_err.reset();
            bios_error_frame(family, byte, ev, now);
            return ev;
        }
        if (data_byte(byte, ev, now)) return ev;
        boundary_byte(byte, ev, now);
        return ev;
    }

    // a byte where a frame may start: only here are F0 xx, errors and 50 recognized
    void SessionCore::boundary_byte(uint8_t byte, rsp::Events& ev, TimePoint now) {
        if (byte == FB_BIOSST_UPDT) {
            pending_f0 = true;
            return;
        }
        if (bios_error::is_error_family(byte)) {
            if (bios_error::is_single_byte(byte)) bios_error_frame(byte, 0x00, ev, now);
            else pending_err = byte;
            return;
        }
        if (accept(byte, ev, now)) return;

        const bool messages_allowed = stage == Stage::None || stage == Stage::PostBody || stage == Stage::EchoBody;
        if (byte == FB_MSG_STR && messages_allowed) {
            start_str();
            return;
        }
        if (byte == FB_MSG_FLSH && messages_allowed) {
            flush_message(ev);
            if (stage == Stage::EchoBody) enter(Stage::Completion, ev, now);
            return;
        }
        if (byte == FB_ST_TESTBYTE) {
            test_byte(ev);
            return;
        }
        if (active) {
            protocol_mismatch(byte, ev, now);
            return;
        }
        ev.push_back(rsp::EvUnsolicited{byte});
    }

    // the byte the current boundary stage is waiting for
    bool SessionCore::accept(uint8_t byte, rsp::Events& ev, TimePoint now) {
        switch (stage) {
            case Stage::SynAck:
                if (byte != FB_NET_SYNACK) return false;
                finish_ok(ev);  // the shell sends AC straight away (separate transaction)
                return true;
            case Stage::PostBody:
                if (byte != FB_ST_PASS && byte != FB_ST_FAIL) return false;
                post = rsp::PostResults{};
                post.passed = byte == FB_ST_PASS;
                enter(Stage::PostResultsHdr, ev, now);
                return true;
            case Stage::PostResultsHdr:
                if (byte != FB_ST_RESULTS) return false;
                enter(Stage::PostPairs, ev, now);
                return true;
            case Stage::PostFinish:
                if (byte != FB_ST_FINISH) return false;
                cache.post = post;
                ev.push_back(rsp::EvPostResults{post});
                enter(Stage::Completion, ev, now);
                return true;
            case Stage::EchoHeader:
                if (byte != FB_MSG_ECHO) return false;
                enter(Stage::EchoBody, ev, now);
                return true;
            case Stage::SelfTestByte:
                if (byte != FB_ST_TESTBYTE) return false;
                enter(Stage::PostBody, ev, now);
                return true;
            case Stage::TeleStatusOpen:
                if (byte != FB_META_DISP) return false;
                counters = rsp::TelemetryCounters{};
                enter(Stage::TeleStatusBody, ev, now);
                return true;
            case Stage::TeleStatusClose:
                if (byte != FB_META_DISP) return false;
                if (!quiet()) ev.push_back(rsp::EvTelemetryStatus{counters, active ? active->tele_filter : std::variant<bool, std::set<commands::TelemetryParam>>{true}});
                enter(Stage::Completion, ev, now);
                return true;
            case Stage::MemConfirm:
                if (byte != FB_MEM_CONF) return false;
                enter(Stage::MemData, ev, now);
                return true;
            case Stage::LoadComplete:
                if (byte != FB_PRG_LOAD) return false;
                load_complete(ev, now);
                return true;
            case Stage::LoadVerifyHdr:
                if (byte != FB_PRG_VERIFY) return false;
                enter(Stage::MemConfirm, ev, now);
                return true;
            case Stage::AfterProgram:
                if (byte != FB_REG_DISP) return false;
                enter(Stage::RegFrame, ev, now);
                return true;
            case Stage::DdHeader:
                if (byte != FB_DD_DISP) return false;
                enter(Stage::DdBody, ev, now);
                return true;
            // the state byte alone didn't say which reply this is, this first content byte does
            case Stage::AutoMeta:
                if (byte == FB_META_DISP) {                       // status: 7D ... 7D
                    counters = rsp::TelemetryCounters{};
                    enter(Stage::TeleStatusBody, ev, now);
                    return true;
                }
                if (byte == TB_META_BIOSTR || byte == TB_META_PRGTR || byte == TB_META_PRGRST) {   // query: 70/71/72 v ...
                    enter(Stage::TeleQuery, ev, now);              // clears data_buf, then seed it with this byte
                    data_buf.push_back(byte);
                    return true;
                }
                return false;    // an empty-body (set) reply is caught earlier, in state_byte's AutoMeta case
            case Stage::AutoNet:
                if (byte == FB_NET_SYNACK) {                       // the SYN's reply: just AB, done
                    finish_ok(ev);
                    return true;
                }
                if (byte == FB_MSG_STR) {                           // the ACK's reply: its POST frame always opens with the message
                    auto_net_ack = true;
                    enter(Stage::PostBody, ev, now);
                    start_str();
                    return true;
                }
                return false;
            default:
                return false;
        }
    }

    // fixed / length known data: no frame detection inside
    bool SessionCore::data_byte(uint8_t byte, rsp::Events& ev, TimePoint now) {
        switch (stage) {
            case Stage::PostPairs:
                data_buf.push_back(byte);
                if (data_buf.size() == POST_PAIR_BYTES) {
                    for (size_t i{0}; i < 6; ++i) {
                        const auto test = data_buf[i * 2];
                        if (test < post.tests.size()) post.tests[test] = data_buf[i * 2 + 1] != 0;
                    }
                    enter(Stage::PostFinish, ev, now);
                }
                return true;

            case Stage::TeleQuery:
                data_buf.push_back(byte);
                if (data_buf.size() == TELE_QUERY_BYTES) {
                    rsp::TelemetrySettings settings{};
                    for (size_t i{0}; i < 3; ++i) {
                        const auto param = data_buf[i * 2];
                        const bool on = data_buf[i * 2 + 1] != 0;
                        if (param == TB_META_BIOSTR) settings.bios = on;
                        else if (param == TB_META_PRGTR) settings.program = on;
                        else if (param == TB_META_PRGRST) settings.program_reset = on;
                        else {
                            protocol_mismatch(param, ev, now);
                            return true;
                        }
                    }
                    cache.telemetry = settings;
                    if (!quiet()) ev.push_back(rsp::EvTelemetrySettings{settings});
                    enter(Stage::Completion, ev, now);
                }
                return true;

            case Stage::TeleStatusBody:
                data_buf.push_back(byte);
                if (data_buf.size() == TELE_STATUS_BYTES) {
                    for (size_t i{0}; i < 5; ++i) {
                        const auto param = data_buf[i * 5];
                        const auto value = le32(&data_buf[i * 5 + 1]);
                        switch (param) {
                            case META_PARAM_CLKCYC: counters.cycles = value; break;
                            case META_PARAM_INSCNT: counters.instr = value; break;
                            case META_PARAM_STLCNT: counters.stall = value; break;
                            case META_PARAM_LSECNT: counters.load_use = value; break;
                            case META_PARAM_BRFCNT: counters.branch_flush = value; break;
                            default:
                                protocol_mismatch(param, ev, now);
                                return true;
                        }
                    }
                    enter(Stage::TeleStatusClose, ev, now);
                }
                return true;

            case Stage::MemData:
                data_buf.push_back(byte);
                if (!quiet() && mem_expected >= PROGRESS_MIN
                    && (data_buf.size() % PROGRESS_STEP == 0 || data_buf.size() == mem_expected)) {
                    ev.push_back(rsp::EvDumpProgress{static_cast<uint32_t>(data_buf.size()), mem_expected});
                }
                if (data_buf.size() == mem_expected) mem_complete(ev, now);
                return true;

            case Stage::RegFrame:
                data_buf.push_back(byte);
                if (data_buf.size() == REG_FRAME_BYTES) {
                    if (data_buf.back() != FB_REG_DISP) {
                        protocol_mismatch(data_buf.back(), ev, now);
                        return true;
                    }
                    std::array<uint32_t, 31> regs{};
                    for (size_t i{0}; i < regs.size(); ++i) {
                        if (data_buf[i * 5] != i + 1) {
                            protocol_mismatch(data_buf[i * 5], ev, now);
                            return true;
                        }
                        regs[i] = le32(&data_buf[i * 5 + 1]);
                    }
                    ev.push_back(rsp::EvRegisters{regs});
                    enter(Stage::Completion, ev, now);
                }
                return true;

            case Stage::DdBody:
                dd_byte(byte, ev, now);
                return true;

            default:
                return false;
        }
    }

    // DA, 00 string, 01 string, 02..0A [param, u32], no end marker
    void SessionCore::dd_byte(uint8_t byte, rsp::Events& ev, TimePoint now) {
        switch (dd_phase) {
            case DdPhase::Param:
                if (byte != dd_next) {
                    protocol_mismatch(byte, ev, now);
                    return;
                }
                dd_phase = dd_next <= DD_PARAM_ARCH ? DdPhase::StrStart : DdPhase::Word;
                dd_word = 0;
                dd_word_bytes = 0;
                return;
            case DdPhase::StrStart:
                if (byte != FB_MSG_STR) {
                    protocol_mismatch(byte, ev, now);
                    return;
                }
                start_str();    // str_complete() moves on to the next param, no 3F for device data strings
                return;
            case DdPhase::Word:
                dd_word |= static_cast<uint32_t>(byte) << (8 * dd_word_bytes);
                if (++dd_word_bytes == 4) {
                    store_dd_word(dd_next, dd_word);
                    if (dd_next == DD_PARAM_ROMSZ) {
                        cache.device = dd;
                        if (!quiet()) ev.push_back(rsp::EvDeviceData{dd, active ? active->dd_filter : std::set<commands::DeviceDataParam>{}});
                        enter(Stage::Completion, ev, now);
                    } else {
                        ++dd_next;
                        dd_phase = DdPhase::Param;
                    }
                }
                return;
        }
    }

    void SessionCore::store_dd_word(uint8_t param, uint32_t value) {
        switch (param) {
            case DD_PARAM_REGCNT:   dd.reg_count = value; break;
            case DD_PARAM_CLKSPD:   dd.clk_hz = value; break;
            case DD_PARAM_BAUDTK:   dd.baud = value; break;
            case DD_PARAM_RAMOFS:   dd.ram_offset = value; break;
            case DD_PARAM_RAMSZ:    dd.ram_size = value; break;
            case DD_PARAM_PROGOFS:  dd.prog_offset = value; break;
            case DD_PARAM_PROGSZ:   dd.prog_size = value; break;
            case DD_PARAM_ROMOFS:   dd.rom_offset = value; break;
            case DD_PARAM_ROMSZ:    dd.rom_size = value; break;
            default: break;
        }
    }

    // byte after F0
    void SessionCore::state_byte(uint8_t st, rsp::Events& ev, TimePoint now) {
        cache.bios_state = st;
        if (st == BIOSST_IDLE) limited = false;
        if (st == BIOSST_STFIDL) limited = true;
        if (log_on) ev.push_back(rsp::EvStateLog{st});
        const bool ready = st == BIOSST_IDLE || st == BIOSST_STFIDL;

        switch (stage) {
            case Stage::AwaitOwnState:
                if (st == own_state) {
                    enter(after_own, ev, now);
                    return;
                }
                if (ready) return;  // idle heartbeat from before the command was picked up
                break;
            case Stage::Completion:
            case Stage::PostBody:
            case Stage::AfterProgram:
                if (ready) {
                    finish_ok(ev);
                    return;
                }
                break;
            case Stage::None:
                begin_auto(st, ev, now);    // raw bytes (sendbyte/sendbytes) with no active transaction
                return;
            case Stage::AutoMeta:
                // the state byte arrived straight back, with nothing in between: the raw bytes triggered
                // a telemetry-set (empty reply body). We don't know what was set, so the cached settings
                // become unknown rather than risk printing stale values (matches the ERR_TELEMETRY rule)
                if (ready) {
                    cache.telemetry = rsp::TelemetrySettings{};
                    finish_ok(ev);
                    return;
                }
                break;
            default:
                break;
        }
        protocol_mismatch(st, ev, now);
    }

    // entered from Stage::None (no active transaction) when a BIOS state update arrives. Each case here
    // mirrors what begin_parse() does for the matching command, minus anything that needed the original
    // request to know (a dump's size, an echo's content). BIOSST_MEM and BIOSST_PGLD are left alone: the
    // reply is unbounded without knowing the size that was sent, so framing it would risk misreading a
    // coincidental 0xF0 inside raw data as a state marker. Their bytes still come through as before
    // (logged to [FROM BIOS] under `monitor`, otherwise unparsed).
    void SessionCore::begin_auto(uint8_t st, rsp::Events& ev, TimePoint now) {
        switch (st) {
            case BIOSST_PGEX:
                enter(Stage::Program, ev, now);           // run, started by raw bytes (e.g. sendbyte 0xCC)
                break;
            case BIOSST_MSG:
                enter(Stage::EchoHeader, ev, now);         // echo: self-describing (the string carries its own length)
                break;
            case BIOSST_ST:
                cache.program_valid = false;               // self test overwrites program space, same as the normal path
                enter(Stage::SelfTestByte, ev, now);
                break;
            case BIOSST_DD:
                enter(Stage::DdHeader, ev, now);            // device data: fixed, self-describing set of fields
                break;
            case BIOSST_META:
                enter(Stage::AutoMeta, ev, now);            // ambiguous: query / status / set all share this state byte
                break;
            case BIOSST_NET:
                enter(Stage::AutoNet, ev, now);             // ambiguous: the SYN's AB vs the ACK's POST frame
                break;
            default:
                break;
        }
    }

    // only the ready signal matters, everything else is discarded
    void SessionCore::cooldown_byte(uint8_t byte, rsp::Events& ev, TimePoint now) {
        if (cooldown_f0) {
            cooldown_f0 = false;
            if (byte == BIOSST_IDLE || byte == BIOSST_STFIDL) {
                cooldown_ready = true;
                cache.bios_state = byte;
                limited = byte == BIOSST_STFIDL;
                if (log_on) ev.push_back(rsp::EvStateLog{byte});
            }
        } else if (byte == FB_BIOSST_UPDT) {
            cooldown_f0 = true;
        }
        check_cooldown(ev, now);
    }

    // program output: messages (3D len bytes 3F) are printed as messages, F0 2C ends the program,
    // 50 F0 00 means the BIOS rebooted under the program, everything else is raw output
    void SessionCore::program_byte(uint8_t byte, rsp::Events& ev, TimePoint now) {
        program_notice_at = now + profile.program_notice();    // BIOS activity also re-arms the "still running" notice
        if (str.active) {
            str_byte(byte, ev, now);
            return;
        }
        if (!prog_hold.empty()) {
            const auto first = static_cast<uint8_t>(prog_hold.front());
            if (prog_hold.size() == 1 && first == FB_BIOSST_UPDT && byte == BIOSST_PGDN) {
                prog_hold.clear();
                hold_deadline.reset();
                program_done(ev, now);
                return;
            }
            if (prog_hold.size() == 1 && first == FB_ST_TESTBYTE && byte == FB_BIOSST_UPDT) {
                prog_hold.push_back(static_cast<char>(byte));
                hold_deadline = now + profile.fallback_time();
                return;
            }
            if (prog_hold.size() == 2) {    // 50 F0
                if (byte == BIOSST_IDLE || byte == BIOSST_STFIDL) {
                    prog_hold.clear();
                    hold_deadline.reset();
                    on_reboot(ev);
                    return;
                }
                if (byte == BIOSST_PGDN) {
                    emit_output(ev, FB_ST_TESTBYTE);
                    prog_hold.clear();
                    hold_deadline.reset();
                    program_done(ev, now);
                    return;
                }
            }
            flush_hold(ev);     // wasn't a marker after all, it was program output
        }
        if (byte == FB_BIOSST_UPDT || byte == FB_ST_TESTBYTE) {
            prog_hold.push_back(static_cast<char>(byte));
            hold_deadline = now + profile.fallback_time();
            return;
        }
        if (byte == FB_MSG_STR) {
            start_str();
            return;
        }
        if (byte == FB_MSG_FLSH) {
            flush_message(ev);
            return;
        }
        emit_output(ev, byte);
    }

    // 3D + 4 byte length (LE) + bytes, stored in the message buffer (a new 3D replaces it)
    void SessionCore::str_byte(uint8_t byte, rsp::Events& ev, TimePoint now) {
        if (str.len_bytes < 4) {
            str.len |= static_cast<uint32_t>(byte) << (8 * str.len_bytes);
            ++str.len_bytes;
            if (str.len_bytes == 4) {
                if (str.len > MAX_STRING_LEN) {
                    const auto len = str.len;
                    str = StrFrame{};
                    if (stage == Stage::Program) {  // not a real message frame, hand the bytes back as program output
                        emit_output(ev, FB_MSG_STR);
                        for (int i{0}; i < 4; ++i) emit_output(ev, static_cast<uint8_t>(len >> (8 * i)));
                    } else {
                        protocol_mismatch(FB_MSG_STR, ev, now);
                    }
                    return;
                }
                if (str.len == 0) str_complete();
            }
            return;
        }
        message_buffer.push_back(static_cast<char>(byte));
        if (++str.got == str.len) str_complete();
    }

    void SessionCore::start_str() {
        str = StrFrame{};
        str.active = true;
        message_buffer.clear();
    }

    void SessionCore::str_complete() {
        str.active = false;
        if (stage == Stage::DdBody) {
            if (dd_next == DD_PARAM_BIOS) dd.bios_name = strip_nul(message_buffer);
            else dd.arch = strip_nul(message_buffer);
            ++dd_next;
            dd_phase = DdPhase::Param;
        }
    }

    // 0x50 at a frame boundary that isn't part of a self test reply: the BIOS rebooted
    void SessionCore::test_byte(rsp::Events& ev) {
        if (expect_boot) {      // boot output after `reset`, the cache was already cleared
            expect_boot = false;
            return;
        }
        if (cache.bios_state == BIOSST_ST) return;     // self test started by raw bytes
        on_reboot(ev);
    }

    void SessionCore::enter_program(rsp::Events& ev, TimePoint now) {
        state = SessionState::ProgramRunning;
        response_deadline.reset();     // a program may run as long as it likes
        program_notice_at = now + profile.program_notice();
        prog_hold.clear();
        hold_deadline.reset();
        ev.push_back(rsp::EvProgramStart{});
    }

    // F0 2C: back in BIOS mode, the 75 register frame (if C5 was set) and F0 00 follow
    void SessionCore::program_done(rsp::Events& ev, TimePoint now) {
        cache.bios_state = BIOSST_PGDN;
        if (log_on) ev.push_back(rsp::EvStateLog{BIOSST_PGDN});
        ev.push_back(rsp::EvProgramDone{});
        program_notice_at.reset();
        state = SessionState::AwaitingResponse;
        response_deadline = now + profile.response_timeout(REG_FRAME_BYTES + 3);
        enter(Stage::AfterProgram, ev, now);
    }

    void SessionCore::load_complete(rsp::Events& ev, TimePoint now) {
        if (!active) {
            enter(Stage::Completion, ev, now);
            return;
        }
        const auto& tx = *active;
        cache.program_valid = true;
        cache.program_offset = tx.data_offset;
        cache.program_size = tx.data_size;
        cache.telemetry.program = tx.load_args.telemode;            // the load overwrites 0x71 / 0x72
        cache.telemetry.program_reset = tx.load_args.telereset;
        cache.last_load = tx.load_args;
        if (!tx.quiet) ev.push_back(rsp::EvLoadComplete{tx.data_offset, tx.data_size});

        if (tx.load_verify) {
            mem_expected = tx.data_size;
            mem_offset = tx.data_offset;
            mem_readback = true;
            mem_then_run = tx.load_run;
            enter(Stage::LoadVerifyHdr, ev, now);
        } else if (tx.load_run) {
            expect_state(BIOSST_PGEX, Stage::Program);
        } else {
            enter(Stage::Completion, ev, now);
        }
    }

    void SessionCore::mem_complete(rsp::Events& ev, TimePoint now) {
        if (!quiet()) ev.push_back(rsp::EvMemDump{mem_offset, data_buf});
        if (mem_readback && active && active->compare_image) {
            const auto& image = *active->compare_image;
            const auto common = std::min(image.size(), data_buf.size());
            rsp::EvVerifyResult result{ static_cast<uint32_t>(common), std::nullopt, std::nullopt };
            for (size_t i{0}; i < common; ++i) {
                if (image[i] != data_buf[i]) {
                    result.mismatch_addr = mem_offset + static_cast<uint32_t>(i);
                    break;
                }
            }
            if (image.size() != data_buf.size()) {
                result.sizes = std::pair{ static_cast<uint32_t>(data_buf.size()), static_cast<uint32_t>(image.size()) };
            }
            ev.push_back(result);
        }
        if (mem_then_run) {
            data_buf.clear();
            expect_state(BIOSST_PGEX, Stage::Program);
        } else {
            enter(Stage::Completion, ev, now);
        }
    }

    void SessionCore::emit_output(rsp::Events& ev, uint8_t byte) {
        if (!ev.empty()) {
            if (auto* last = std::get_if<rsp::EvProgramOutput>(&ev.back())) {
                last->bytes.push_back(static_cast<char>(byte));
                return;
            }
        }
        ev.push_back(rsp::EvProgramOutput{std::string(1, static_cast<char>(byte))});
    }

    void SessionCore::flush_hold(rsp::Events& ev) {
        for (const char c : prog_hold) emit_output(ev, static_cast<uint8_t>(c));
        prog_hold.clear();
        hold_deadline.reset();
    }

    void SessionCore::flush_message(rsp::Events& ev) {
        ev.push_back(rsp::EvMessage{message_buffer});
    }

    // ------------------------------------------------------------------------------------------------
    // SessionCore: timers
    // ------------------------------------------------------------------------------------------------

    rsp::Events SessionCore::on_tick(TimePoint now) {
        rsp::Events ev{};
        switch (state) {
            case SessionState::Cooldown:
                check_cooldown(ev, now);
                break;
            case SessionState::AwaitingResponse:
                if (response_deadline && now >= *response_deadline) {
                    ev.push_back(rsp::EvClientTimeout{});
                    if (active && active->expect == Expect::Load) cache.program_valid = false;
                    start_cooldown(ev, now, TxOutcome::Timeout);
                }
                break;
            case SessionState::ProgramRunning:
                if (hold_deadline && now >= *hold_deadline) flush_hold(ev);
                if (program_notice_at && now >= *program_notice_at) {
                    ev.push_back(rsp::EvProgramStillRunning{});
                    program_notice_at.reset();
                }
                break;
            default:
                break;
        }
        return ev;
    }

    std::optional<TimePoint> SessionCore::next_deadline() const {
        std::optional<TimePoint> next{};
        const auto consider = [&next](std::optional<TimePoint> tp) {
            if (tp && (!next || *tp < *next)) next = tp;
        };
        if (state == SessionState::AwaitingResponse) consider(response_deadline);
        if (state == SessionState::Cooldown) {
            consider(floor_end());
            consider(cap_end());
        }
        consider(hold_deadline);
        consider(program_notice_at);
        return next;
    }

    // ------------------------------------------------------------------------------------------------
    // SessionCore: shell / writer side
    // ------------------------------------------------------------------------------------------------

    std::expected<uint64_t, error::Error> SessionCore::submit(bytegen_mod::Transaction tx) {
        using SemErr = error::SemanticError;
        if (!transport_open) return std::unexpected(error::Error(SemErr::NoTransport));
        if (state != SessionState::Idle && state != SessionState::Disconnected) return std::unexpected(error::Error(SemErr::NotIdle));
        if (!raw_queue.empty()) return std::unexpected(error::Error(SemErr::RawQueuePending));

        begin_parse(tx);
        active = std::move(tx);
        job_taken = false;
        outcome = TxOutcome::Pending;
        response_deadline.reset();
        state = SessionState::Sending;
        return ++tx_seq;
    }

    std::expected<void, error::Error> SessionCore::enqueue_raw(std::span<const uint8_t> bytes, Nanos gap, TimePoint now) {
        if (!transport_open) return std::unexpected(error::Error(error::SemanticError::NoTransport));
        for (const auto byte : bytes) raw_queue.push_back(RawByte{byte, gap});
        // the user is actively feeding the running program: push the "still running" notice back out
        // rather than let it fire while they're mid-interaction (e.g. typing a number via sendbyte)
        if (state == SessionState::ProgramRunning) program_notice_at = now + profile.program_notice();
        return {};
    }

    // done once its outcome is in and the session can take a new command (cooldown over),
    // or once the program started (the prompt comes back while it runs)
    bool SessionCore::finished(uint64_t seq) const {
        const bool busy = state == SessionState::Sending || state == SessionState::AwaitingResponse
            || state == SessionState::Cooldown;
        if (busy) return false;
        return done_seq >= seq || state == SessionState::ProgramRunning;
    }

    TxOutcome SessionCore::outcome_for(uint64_t seq) const {
        if (done_seq >= seq) return outcome;
        return TxOutcome::ProgramRunning;
    }

    Snapshot SessionCore::snapshot() const {
        Snapshot snap{ state, transport_open, linked, limited, cache, monitor_on, log_on, {} };
        for (const auto& raw : raw_queue) snap.raw_pending.push_back(raw.byte);
        return snap;
    }

    void SessionCore::set_monitor(bool on) { monitor_on = on; }
    void SessionCore::set_log(bool on) { log_on = on; }
    void SessionCore::set_profile(const profile_mod::Profile& prof) { profile = prof; }

    void SessionCore::transport_opened() {
        transport_open = true;
        linked = false;
        limited = false;
        reset_parser();
        state = SessionState::Disconnected;
    }

    void SessionCore::transport_closed() {
        ++generation;
        finish(TxOutcome::LinkLost);
        transport_open = false;
        linked = false;
        limited = false;
        expect_boot = false;
        cache.clear();
        raw_queue.clear();
        message_buffer.clear();
        reset_parser();
        response_deadline.reset();
        program_notice_at.reset();
        state = SessionState::Disconnected;
    }

    void SessionCore::reset_for_switch(const profile_mod::Profile& prof) {
        transport_closed();
        profile = prof;
    }

    // the CPU was reset through the bridge: same as a reboot, but the boot byte is expected
    void SessionCore::after_sim_reset() {
        ++generation;
        finish(TxOutcome::Rebooted);
        cache.clear();
        linked = false;
        limited = false;
        expect_boot = true;
        raw_queue.clear();
        message_buffer.clear();
        reset_parser();
        response_deadline.reset();
        program_notice_at.reset();
        state = SessionState::Disconnected;
    }

    std::optional<WriterJob> SessionCore::take_job() {
        if (!tx_job_ready()) return std::nullopt;
        job_taken = true;
        return WriterJob{
            generation, tx_seq, false, active->bytes, profile_mod::Profile::CHUNK_SIZE,
            profile.chunk_gap(profile_mod::Profile::CHUNK_SIZE), profile.tx_stall_limit(),
            active->expect == bytegen_mod::Expect::Load
        };
    }

    std::optional<WriterJob> SessionCore::take_raw(TimePoint now) {
        if (!raw_ready() || now < raw_next) return std::nullopt;
        const auto raw = raw_queue.front();
        raw_queue.pop_front();
        raw_next = now + raw.gap;
        return WriterJob{ generation, 0, true, { raw.byte }, 1, raw.gap, profile.tx_stall_limit() };
    }

    bool SessionCore::tx_job_ready() const {
        return state == SessionState::Sending && !job_taken && active.has_value();
    }

    bool SessionCore::raw_ready() const {
        return raw_allowed() && !raw_queue.empty();
    }

    TimePoint SessionCore::raw_next_time() const {
        return raw_next;
    }

    // Sending -> AwaitingResponse, only if this is still the current transaction
    void SessionCore::writer_done(uint64_t seq, TimePoint now) {
        if (!active || seq != tx_seq || state != SessionState::Sending) return;
        state = SessionState::AwaitingResponse;
        const auto timeout = active->timeout_override.value_or(profile.response_timeout(bytegen_mod::expected_rx_bytes(*active)));
        response_deadline = now + timeout;
    }

    void SessionCore::note_host_write(TimePoint now) {
        last_host_write = now;
    }

    uint64_t SessionCore::current_generation() const {
        return generation;
    }

    rsp::Events SessionCore::on_link_lost(std::string detail) {
        if (!transport_open) return {};
        rsp::Events ev{};
        ev.push_back(rsp::EvLinkLost{std::move(detail)});
        transport_closed();
        return ev;
    }

    // ------------------------------------------------------------------------------------------------
    // Session: locking wrapper
    // ------------------------------------------------------------------------------------------------

    Session::Session(const profile_mod::Profile& prof) :
        mtx{},
        cv{},
        core{prof}
    { }

    std::expected<uint64_t, error::Error> Session::submit(bytegen_mod::Transaction tx) {
        std::expected<uint64_t, error::Error> result{};
        {
            std::scoped_lock lock{mtx};
            result = core.submit(std::move(tx));
        }
        cv.notify_all();
        return result;
    }

    TxOutcome Session::wait_done(uint64_t seq) {
        std::unique_lock lock{mtx};
        cv.wait(lock, [this, seq] { return core.finished(seq); });
        return core.outcome_for(seq);
    }

    Snapshot Session::snapshot() const {
        std::scoped_lock lock{mtx};
        return core.snapshot();
    }

    std::expected<void, error::Error> Session::enqueue_raw(std::span<const uint8_t> bytes, Nanos gap, TimePoint now) {
        std::expected<void, error::Error> result{};
        {
            std::scoped_lock lock{mtx};
            result = core.enqueue_raw(bytes, gap, now);
        }
        cv.notify_all();
        return result;
    }

    void Session::set_monitor(bool on) {
        std::scoped_lock lock{mtx};
        core.set_monitor(on);
    }

    void Session::set_log(bool on) {
        std::scoped_lock lock{mtx};
        core.set_log(on);
    }

    void Session::set_profile(const profile_mod::Profile& prof) {
        std::scoped_lock lock{mtx};
        core.set_profile(prof);
    }

    void Session::transport_opened() {
        { std::scoped_lock lock{mtx}; core.transport_opened(); }
        cv.notify_all();
    }

    void Session::transport_closed() {
        { std::scoped_lock lock{mtx}; core.transport_closed(); }
        cv.notify_all();
    }

    void Session::reset_for_switch(const profile_mod::Profile& prof) {
        { std::scoped_lock lock{mtx}; core.reset_for_switch(prof); }
        cv.notify_all();
    }

    void Session::after_sim_reset() {
        { std::scoped_lock lock{mtx}; core.after_sim_reset(); }
        cv.notify_all();
    }

    // blocks until there is a transaction to send, or a raw byte whose gap is over
    std::optional<WriterJob> Session::writer_next(std::stop_token st) {
        std::unique_lock lock{mtx};
        while (!st.stop_requested()) {
            if (auto job = core.take_job()) return job;
            if (auto job = core.take_raw(Clock::now())) {
                lock.unlock();
                cv.notify_all();    // the raw queue shrank
                return job;
            }
            if (core.raw_ready()) {
                cv.wait_until(lock, st, core.raw_next_time(), [this] { return core.tx_job_ready(); });
            } else {
                cv.wait(lock, st, [this] { return core.tx_job_ready() || core.raw_ready(); });
            }
        }
        return std::nullopt;
    }

    // pacing wait that an abort (generation bump) or shutdown cuts short
    bool Session::writer_wait(uint64_t gen, TimePoint until, std::stop_token st) {
        std::unique_lock lock{mtx};
        cv.wait_until(lock, st, until, [this, gen] { return core.current_generation() != gen; });
        return core.current_generation() == gen && !st.stop_requested();
    }

    bool Session::gen_current(uint64_t gen) const {
        std::scoped_lock lock{mtx};
        return core.current_generation() == gen;
    }

    void Session::note_host_write(TimePoint now) {
        std::scoped_lock lock{mtx};
        core.note_host_write(now);
    }

    void Session::writer_done(uint64_t seq, TimePoint now) {
        { std::scoped_lock lock{mtx}; core.writer_done(seq, now); }
        cv.notify_all();
    }

    rsp::Events Session::on_bytes(std::span<const uint8_t> bytes, TimePoint now) {
        rsp::Events out{};
        {
            std::scoped_lock lock{mtx};
            for (const auto byte : bytes) {
                for (auto& ev : core.on_byte(byte, now)) append_merged(out, std::move(ev));
            }
            for (auto& ev : core.on_tick(now)) append_merged(out, std::move(ev));
        }
        cv.notify_all();
        return out;
    }

    rsp::Events Session::on_link_lost(std::string detail) {
        rsp::Events out{};
        {
            std::scoped_lock lock{mtx};
            out = core.on_link_lost(std::move(detail));
        }
        cv.notify_all();
        return out;
    }

    // the reader never blocks forever: at most until the next session deadline (and 50 ms for shutdown)
    std::chrono::milliseconds Session::read_timeout(TimePoint now) const {
        std::scoped_lock lock{mtx};
        const auto next = core.next_deadline();
        if (!next) return MAX_READ_WAIT;
        if (*next <= now) return std::chrono::milliseconds{1};
        const auto left = std::chrono::ceil<std::chrono::milliseconds>(*next - now);
        return std::clamp(left, std::chrono::milliseconds{1}, MAX_READ_WAIT);
    }

}
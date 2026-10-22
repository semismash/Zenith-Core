#include "bytegen.hpp"

#include "../headers/codes.hpp"
#include "../headers/overload.hpp"

namespace bytegen_mod {

    using namespace bios_protocol;

    namespace {

        inline constexpr size_t POST_FRAME_BYTES = 1 + 5 + 26 + 1 + 1 + 1 + 12 + 1;   // 50, 3D len "BIOS Loaded..." 3F, 5C, 5D, pairs, 5F
        inline constexpr size_t STATE_LOG_BYTES = 2;
        inline constexpr size_t DD_REPLY_BYTES = 105;
        inline constexpr size_t TELE_STATUS_BYTES = 25;    // 5 params (cycles, instr, stall, load-use, branch flush), 5 bytes each
        inline constexpr size_t TELE_QUERY_BYTES = 6;

        Transaction make_echo(const commands::CommandEcho& cmd) {
            Transaction tx{};
            tx.expect = Expect::Echo;
            tx.bytes = { TB_MSG_ECHO, TB_MSG_STR };
            put_u32(tx.bytes, static_cast<uint32_t>(cmd.msg.size()));
            tx.bytes.insert(tx.bytes.end(), cmd.msg.begin(), cmd.msg.end());
            return tx;
        }

        Transaction make_selftest() {
            Transaction tx{};
            tx.expect = Expect::SelfTest;
            tx.bytes = { TB_ST_INIT };
            return tx;
        }

        // 7A 7A is a query, anything in between is a silent update
        Transaction make_telemetry(const commands::CommandTelemetry& cmd) {
            Transaction tx{};
            if (!cmd.telemode && !cmd.telereset && !cmd.inst_reset) {
                tx.expect = Expect::TelemetryQuery;
                tx.bytes = { TB_META_START, TB_META_START };
                return tx;
            }
            tx.expect = Expect::TelemetrySet;
            tx.bytes = { TB_META_START };
            if (cmd.inst_reset) tx.bytes.push_back(TB_META_RESET);     // no argument, not counted in the 4 params
            if (cmd.telemode) {
                tx.bytes.push_back(TB_META_BIOSTR);
                tx.bytes.push_back(*cmd.telemode ? META_ARG_ON : META_ARG_OFF);
            }
            if (cmd.telereset) {
                tx.bytes.push_back(TB_META_PRGRST);
                tx.bytes.push_back(*cmd.telereset ? META_ARG_ON : META_ARG_OFF);
            }
            tx.bytes.push_back(TB_META_START);
            tx.tele_bios = cmd.telemode;
            tx.tele_prog_reset = cmd.telereset;
            return tx;
        }

        Transaction make_status(const commands::CommandTelemetryStatus& cmd) {
            Transaction tx{};
            tx.expect = Expect::TelemetryStatus;
            tx.bytes = { TB_META_DISP };
            tx.tele_filter = cmd.telemetry_args;
            return tx;
        }

        Transaction make_dump(const commands::CommandHexDump& cmd) {
            Transaction tx{};
            tx.expect = Expect::MemDump;
            tx.bytes = { TB_MEM_DUMP };
            put_u32(tx.bytes, cmd.byte_count);  // size first, then offset
            put_u32(tx.bytes, cmd.start_addr);
            tx.data_offset = cmd.start_addr;
            tx.data_size = cmd.byte_count;
            return tx;
        }

        Transaction make_verify(const responses::DeviceCache& cache) {
            Transaction tx{};
            tx.expect = Expect::Verify;
            tx.bytes = { TB_PRG_VERIFY };
            tx.data_offset = cache.program_offset;
            tx.data_size = cache.program_size;
            return tx;
        }

        // CA [C0] [C1] C2 offset C3 v C4 v C5 v CA size data
        // every setting is sent explicitly, the BIOS defaults them to off (the CLI defaults telemode/telereset to on)
        Transaction make_load(const commands::CommandLoad& cmd) {
            Transaction tx{};
            tx.expect = Expect::Load;
            const auto offset = cmd.start_addr.value_or(0);
            const auto& image = *cmd.image;

            tx.bytes.reserve(image.size() + 24);
            tx.bytes.push_back(TB_PRG_LOAD);
            if (cmd.run) tx.bytes.push_back(PRG_RUNNOW);
            if (cmd.verify) tx.bytes.push_back(PRG_VERIFY);
            tx.bytes.push_back(PRG_OFFSET);
            put_u32(tx.bytes, offset);
            tx.bytes.push_back(PRG_T_MODE);
            tx.bytes.push_back(cmd.telemode ? META_ARG_ON : META_ARG_OFF);
            tx.bytes.push_back(PRG_T_RST);
            tx.bytes.push_back(cmd.telereset ? META_ARG_ON : META_ARG_OFF);
            tx.bytes.push_back(PRG_REGDISP);
            tx.bytes.push_back(cmd.reg_disp ? META_ARG_ON : META_ARG_OFF);
            tx.bytes.push_back(TB_PRG_LOAD);
            put_u32(tx.bytes, static_cast<uint32_t>(image.size()));
            tx.bytes.insert(tx.bytes.end(), image.begin(), image.end());

            tx.data_offset = offset;
            tx.data_size = static_cast<uint32_t>(image.size());
            tx.load_verify = cmd.verify;
            tx.load_run = cmd.run;
            tx.load_args = responses::LoadArgs{ cmd.telemode, cmd.telereset, cmd.reg_disp };
            if (cmd.verify) tx.compare_image = cmd.image;
            return tx;
        }

        Transaction make_run() {
            Transaction tx{};
            tx.expect = Expect::Run;
            tx.bytes = { TB_PRG_RUN };
            return tx;
        }

        Transaction make_device_data(std::set<commands::DeviceDataParam> filter, bool quiet) {
            Transaction tx{};
            tx.expect = Expect::DeviceData;
            tx.bytes = { TB_DD_DATA };
            tx.dd_filter = std::move(filter);
            tx.quiet = quiet;
            return tx;
        }

    }

    void put_u32(std::vector<uint8_t>& out, uint32_t value) {
        for (int i{0}; i < 4; ++i) out.push_back(static_cast<uint8_t>(value >> (8 * i)));
    }

    size_t expected_rx_bytes(const Transaction& tx) {
        switch (tx.expect) {
            case Expect::SynAck:            return STATE_LOG_BYTES + 1;
            case Expect::ConnectAck:        return POST_FRAME_BYTES + STATE_LOG_BYTES;
            case Expect::Echo:              return STATE_LOG_BYTES * 2 + tx.bytes.size() + 2;
            case Expect::SelfTest:          return POST_FRAME_BYTES + STATE_LOG_BYTES * 2;
            case Expect::TelemetrySet:      return STATE_LOG_BYTES * 2;
            case Expect::TelemetryQuery:    return STATE_LOG_BYTES * 2 + TELE_QUERY_BYTES;
            case Expect::TelemetryStatus:   return STATE_LOG_BYTES * 2 + TELE_STATUS_BYTES;
            case Expect::MemDump:
            case Expect::Verify:            return STATE_LOG_BYTES * 2 + 1 + tx.data_size;
            case Expect::Load:              return STATE_LOG_BYTES * 3 + 1 + (tx.load_verify ? tx.data_size + 2 : 0);
            case Expect::Run:               return STATE_LOG_BYTES;
            case Expect::DeviceData:        return STATE_LOG_BYTES * 2 + DD_REPLY_BYTES;
        }
        return STATE_LOG_BYTES * 2;
    }

    Transaction make_connect_syn(std::optional<std::chrono::nanoseconds> timeout) {
        Transaction tx{};
        tx.expect = Expect::SynAck;
        tx.bytes = { TB_NET_SYN };
        tx.timeout_override = timeout;
        tx.quiet = true;
        return tx;
    }

    Transaction make_connect_ack() {
        Transaction tx{};
        tx.expect = Expect::ConnectAck;
        tx.bytes = { TB_NET_ACK };
        return tx;
    }

    std::vector<Transaction> make_sync() {
        Transaction query{};
        query.expect = Expect::TelemetryQuery;
        query.bytes = { TB_META_START, TB_META_START };
        query.quiet = true;
        return { make_device_data({}, true), std::move(query) };
    }

    std::vector<Transaction> build(const commands::Command& cmd, const responses::DeviceCache& cache) {
        return std::visit(overload{
            [](const commands::CommandEcho& c) -> std::vector<Transaction> {
                if (c.terminal_echo) return {};    // -t never reaches the BIOS
                return { make_echo(c) };
            },
            [](const commands::CommandSelfTest&) -> std::vector<Transaction> { return { make_selftest() }; },
            [](const commands::CommandTelemetry& c) -> std::vector<Transaction> { return { make_telemetry(c) }; },
            [](const commands::CommandTelemetryStatus& c) -> std::vector<Transaction> { return { make_status(c) }; },
            [](const commands::CommandHexDump& c) -> std::vector<Transaction> { return { make_dump(c) }; },
            [&cache](const commands::CommandVerify&) -> std::vector<Transaction> { return { make_verify(cache) }; },
            [](const commands::CommandLoad& c) -> std::vector<Transaction> {
                if (!c.image) return {};    // the analyzer always fills it in, never sent without it
                return { make_load(c) };
            },
            [](const commands::CommandRun&) -> std::vector<Transaction> { return { make_run() }; },
            [](const commands::CommandDeviceInfo& c) -> std::vector<Transaction> { return { make_device_data(c.device_data_args, false) }; },
            [](const commands::CommandSync&) -> std::vector<Transaction> { return make_sync(); },
            [](const auto&) -> std::vector<Transaction> { return {}; },    // client side, nothing to send
        }, cmd);
    }

}
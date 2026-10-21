#include "responseprint.hpp"

#include <algorithm>
#include <array>
#include <cstdio>

#include <replxx.hxx>
#include <toml.hpp>

#include "../headers/codes.hpp"
#include "../headers/overload.hpp"

namespace print_mod {

    using namespace bios_protocol;
    namespace rsp = responses;

    namespace {

        // messages.toml tables become dotted keys: [client] cooldown_start -> "client.cooldown_start"
        void flatten(const toml::table& tbl, const std::string& prefix, std::unordered_map<std::string, std::string>& out) {
            for (auto&& [key, node] : tbl) {
                const std::string name{key.str()};
                const std::string full = prefix.empty() ? name : prefix + "." + name;
                if (const auto* sub = node.as_table()) {
                    flatten(*sub, full, out);
                } else if (auto text = node.value<std::string>()) {
                    out.insert_or_assign(full, *text);
                }
            }
        }

        // program output: printable ASCII and \n \r \t go through as they are, the rest as \xNN
        std::string escape_output(std::string_view bytes) {
            std::string out{};
            out.reserve(bytes.size());
            for (const char c : bytes) {
                const auto u = static_cast<unsigned char>(c);
                if ((u >= 0x20 && u < 0x7F) || c == '\n' || c == '\r' || c == '\t') out.push_back(c);
                else out += std::format("\\x{:02X}", u);
            }
            return out;
        }

        std::string strip_nul(std::string_view text) {
            std::string out{};
            for (const char c : text) if (c != '\0') out.push_back(c);
            return out;
        }

        inline constexpr std::array<std::string_view, 31> abi_names{
            "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", "a6",
            "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
        };

    }

    // ------------------------------------------------------------------------------------------------
    // Messages
    // ------------------------------------------------------------------------------------------------

    std::expected<void, std::string> Messages::load(std::string_view toml_text) {
        try {
            const auto tbl = toml::parse(toml_text, "messages.toml");
            table.clear();
            flatten(tbl, "", table);
        } catch (const toml::parse_error& err) {
            return std::unexpected(std::format("{} (line {})", err.description(), err.source().begin.line));
        }
        return {};
    }

    bool Messages::contains(std::string_view key) const {
        return table.contains(std::string(key));
    }

    std::string Messages::get(std::string_view key) const {
        if (const auto found = table.find(std::string(key)); found != table.end()) return found->second;
        return std::format("<missing message: {}>", key);
    }

    // ------------------------------------------------------------------------------------------------
    // Printer
    // ------------------------------------------------------------------------------------------------

    Printer::Printer(const Messages& messages) :
        msgs{messages},
        mtx{},
        rx{nullptr},
        at_line_start{true}
    { }

    void Printer::attach(replxx::Replxx* replxx) {
        std::scoped_lock lock{mtx};
        rx = replxx;
    }

    // raw write, no newline added (flushed messages and program output go through here)
    void Printer::emit(std::string_view text) {
        if (text.empty()) return;
        const std::string out{text};
        if (rx != nullptr) {
            rx->print("%s", out.c_str());
        } else {
            std::fwrite(out.data(), 1, out.size(), stdout);
            std::fflush(stdout);
        }
        at_line_start = out.back() == '\n';
    }

    // always starts on a fresh line, even after a message without a trailing newline
    void Printer::emit_line(std::string_view text) {
        if (!at_line_start) emit("\n");
        emit(std::string(text) + "\n");
    }

    void Printer::print(const rsp::Events& events) {
        std::scoped_lock lock{mtx};
        for (const auto& ev : events) render(ev);
    }

    void Printer::line(std::string_view text) {
        std::scoped_lock lock{mtx};
        emit_line(text);
    }

    void Printer::error(const error::Error& err) {
        line(msgs.fmt(err.message_key(), err.detail));
    }

    void Printer::clear_screen() {
        std::scoped_lock lock{mtx};
        if (rx != nullptr) {
            rx->clear_screen();
        } else {
            std::fputs("\x1b[2J\x1b[H", stdout);
            std::fflush(stdout);
        }
        at_line_start = true;
    }

    std::string Printer::on_off(std::optional<bool> value) const {
        if (!value) return msgs.get("word.unknown");
        return msgs.get(*value ? "word.on" : "word.off");
    }

    std::string Printer::state_name(uint8_t state) const {
        switch (state) {
            case BIOSST_IDLE:   return msgs.get("state.idle");
            case BIOSST_MSG:    return msgs.get("state.message");
            case BIOSST_ST:     return msgs.get("state.self_test");
            case BIOSST_META:   return msgs.get("state.telemetry");
            case BIOSST_MEM:    return msgs.get("state.memory");
            case BIOSST_NET:    return msgs.get("state.connection");
            case BIOSST_PGLD:   return msgs.get("state.program_load");
            case BIOSST_PGEX:   return msgs.get("state.program_exec");
            case BIOSST_PGDN:   return msgs.get("state.program_done");
            case BIOSST_DD:     return msgs.get("state.device_data");
            case BIOSST_ERR:    return msgs.get("state.error");
            case BIOSST_STFIDL: return msgs.get("state.post_fail_idle");
            default:            return msgs.fmt("state.unknown", state);
        }
    }

    void Printer::render(const rsp::Event& ev) {
        std::visit(overload{
            [this](const rsp::EvMonitorByte& e) { emit_line(msgs.get("marker.from_bios") + std::format("0x{:02X}", e.byte)); },
            [this](const rsp::EvStateLog& e) { emit_line(msgs.get("marker.bios_state") + state_name(e.state)); },
            [this](const rsp::EvBiosError& e) {
                const auto text = msgs.get(bios_error::message_key(e.error));
                if (bios_error::is_single_byte(e.error.family)) emit_line(msgs.fmt("bios_error.format_single", e.error.family, text));
                else emit_line(msgs.fmt("bios_error.format", e.error.family, e.error.code, text));
            },
            [this](const rsp::EvClientTimeout&) { emit_line(msgs.get("client.timeout")); },
            [this](const rsp::EvProtocolMismatch& e) { emit_line(msgs.fmt("client.protocol_mismatch", e.byte)); },
            [this](const rsp::EvUnsolicited& e) { emit_line(msgs.fmt("client.unsolicited", e.byte)); },
            [this](const rsp::EvCooldownStart&) { emit_line(msgs.get("client.cooldown_start")); },
            [this](const rsp::EvCooldownEnd& e) { emit_line(msgs.get(e.by_fallback ? "client.cooldown_fallback" : "client.cooldown_end")); },
            [this](const rsp::EvMessage& e) { emit(strip_nul(e.text)); },     // no prefix, no newline added
            [this](const rsp::EvProgramOutput& e) { emit(escape_output(e.bytes)); },
            [this](const rsp::EvProgramStart&) { emit_line(msgs.get("client.program_start")); },
            [this](const rsp::EvProgramDone&) { emit_line(msgs.get("client.program_done")); },
            [this](const rsp::EvProgramStillRunning&) { emit_line(msgs.get("client.program_stuck")); },
            [this](const rsp::EvReboot&) { emit_line(msgs.get("client.reboot")); },
            [this](const rsp::EvLinkLost& e) { emit_line(msgs.fmt("client.link_lost", e.detail)); },
            [this](const rsp::EvRawDropped& e) { emit_line(msgs.fmt("client.raw_dropped", e.count)); },
            [this](const rsp::EvPostResults& e) { render_post(e.post); },
            [this](const rsp::EvTelemetrySettings& e) {
                emit_line(msgs.fmt("client.telemetry_settings", on_off(e.settings.bios), on_off(e.settings.program), on_off(e.settings.program_reset)));
            },
            [this](const rsp::EvTelemetryApplied&) { emit_line(msgs.get("client.telemetry_applied")); },
            [this](const rsp::EvTelemetryStatus& e) { render_status(e); },
            [this](const rsp::EvDumpProgress& e) {
                if (!at_line_start) emit("\r");
                emit(msgs.fmt("client.dump_progress", e.received, e.total));
                if (e.received == e.total) emit("\n");
            },
            [this](const rsp::EvMemDump& e) { render_dump(e.offset, e.data); },
            [this](const rsp::EvVerifyResult& e) {
                if (e.sizes) emit_line(msgs.fmt("client.verify_size", e.sizes->first, e.sizes->second));
                else if (e.mismatch_addr) emit_line(msgs.fmt("client.verify_fail", *e.mismatch_addr));
                else emit_line(msgs.fmt("client.verify_pass", e.compared));
                if (e.sizes && e.mismatch_addr) emit_line(msgs.fmt("client.verify_fail", *e.mismatch_addr));
            },
            [this](const rsp::EvLoadComplete& e) { emit_line(msgs.fmt("client.load_complete", e.size, e.offset)); },
            [this](const rsp::EvDeviceData& e) { render_device(e); },
            [this](const rsp::EvRegisters& e) { render_registers(e); },
        }, ev);
    }

    void Printer::render_post(const rsp::PostResults& post) {
        emit_line(msgs.get(post.passed ? "post.passed" : "post.failed"));
        for (size_t i{0}; i < post.tests.size(); ++i) {
            emit_line(msgs.fmt("post.test_line", msgs.get(std::format("post.test_{}", i)), msgs.get(post.tests[i] ? "post.pass" : "post.fail")));
        }
    }

    // 16 bytes per row: address, hex (gap after 8), ascii
    void Printer::render_dump(uint32_t offset, const std::vector<uint8_t>& data) {
        for (size_t row{0}; row < data.size(); row += 16) {
            std::string hex{};
            std::string ascii{};
            for (size_t col{0}; col < 16; ++col) {
                if (col == 8) hex.push_back(' ');
                if (row + col < data.size()) {
                    const auto byte = data[row + col];
                    hex += std::format("{:02X} ", byte);
                    ascii.push_back(byte >= 0x20 && byte < 0x7F ? static_cast<char>(byte) : '.');
                } else {
                    hex += "   ";
                    ascii.push_back(' ');
                }
            }
            emit_line(msgs.fmt("dump.row", offset + static_cast<uint32_t>(row), hex, ascii));
        }
    }

    void Printer::render_device(const rsp::EvDeviceData& info) {
        using commands::DeviceDataParam;
        const auto& d = info.data;
        const bool all = info.filter.empty();
        const auto want = [&info, all](DeviceDataParam p) { return all || info.filter.contains(p); };

        const auto rom_end = d.rom_offset + d.rom_size - 1;
        const auto ram_end = d.ram_offset + d.ram_size - 1;

        if (all) emit_line(msgs.fmt("device.bios", d.bios_name));
        if (want(DeviceDataParam::Arch)) emit_line(msgs.fmt("device.arch", d.arch));
        if (want(DeviceDataParam::Reg)) emit_line(msgs.fmt("device.reg", d.reg_count));
        if (want(DeviceDataParam::ROM)) emit_line(msgs.fmt("device.rom", d.rom_size / 1024, d.rom_offset, rom_end));
        if (want(DeviceDataParam::RAM)) emit_line(msgs.fmt("device.ram", d.ram_size / 1024, d.ram_offset, ram_end));
        if (want(DeviceDataParam::Mem)) {
            const auto mem_start = std::min(d.rom_offset, d.ram_offset);
            const auto mem_end = std::max(rom_end, ram_end);
            emit_line(msgs.fmt("device.mem", (d.rom_size + d.ram_size) / 1024, mem_start, mem_end));
        }
        if (all) emit_line(msgs.fmt("device.program", d.prog_size / 1024, d.prog_offset, d.prog_offset + d.prog_size - 1));
        if (want(DeviceDataParam::Clk)) emit_line(msgs.fmt("device.clk", static_cast<double>(d.clk_hz) / 1.0e6));
        if (want(DeviceDataParam::Baud)) emit_line(msgs.fmt("device.baud", d.baud));
    }

    void Printer::render_status(const rsp::EvTelemetryStatus& status) {
        using commands::TelemetryParam;
        const auto& c = status.counters;
        const auto* selected = std::get_if<std::set<TelemetryParam>>(&status.filter);
        const auto want = [selected](TelemetryParam p) { return selected == nullptr || selected->contains(p); };

        if (want(TelemetryParam::Instr)) emit_line(msgs.fmt("status.instr", c.instr));
        if (want(TelemetryParam::Stall)) emit_line(msgs.fmt("status.stall", c.stall));
        if (want(TelemetryParam::StallPcnt)) {     // derived client side: stalls per 100 instructions
            if (c.instr == 0) emit_line(msgs.get("status.stallpcnt_na"));
            else emit_line(msgs.fmt("status.stallpcnt", static_cast<double>(c.stall) * 100.0 / static_cast<double>(c.instr)));
        }
        if (want(TelemetryParam::LoadUseStall)) emit_line(msgs.fmt("status.loaduse", c.load_use));
        if (want(TelemetryParam::BranchFlush)) emit_line(msgs.fmt("status.brflush", c.branch_flush));
    }

    void Printer::render_registers(const rsp::EvRegisters& regs) {
        emit_line(msgs.get("registers.header"));
        for (size_t i{0}; i < regs.regs.size(); ++i) {
            const auto value = regs.regs[i];
            emit_line(msgs.fmt("registers.row", i + 1, abi_names[i], value, static_cast<int32_t>(value)));
        }
    }

}
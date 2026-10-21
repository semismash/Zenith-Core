#include "cmd_analyze.hpp"

#include <algorithm>
#include <cctype>
#include <format>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>

#include "../headers/overload.hpp"

namespace analyze_mod {

    using error::Error;
    using SemErr = error::SemanticError;
    using client_mod::SessionState;
    using profile_mod::ProfileKind;

    namespace {

        std::string to_lower(std::string text) {
            std::ranges::transform(text, text.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            return text;
        }

        bool is_hex_digit(char c) {
            return std::isxdigit(static_cast<unsigned char>(c)) != 0;
        }

        uint8_t hex_value(char c) {
            if (c >= '0' && c <= '9') return static_cast<uint8_t>(c - '0');
            return static_cast<uint8_t>(std::tolower(static_cast<unsigned char>(c)) - 'a' + 10);
        }

        std::expected<std::vector<uint8_t>, Error> parse_readmemh(const std::string& text, const std::string& name) {
            std::vector<uint8_t> image{};
            size_t width{0};    // 2 or 8, fixed by the first token
            std::istringstream lines{text};
            std::string line{};
            size_t line_no{0};
            while (std::getline(lines, line)) {
                ++line_no;
                if (const auto comment = line.find("//"); comment != std::string::npos) line.resize(comment);
                std::istringstream words{line};
                std::string token{};
                while (words >> token) {
                    if (token.front() == '@') continue;     // address lines are ignored, data always goes to --offset
                    std::string digits{};
                    for (const char c : token) {
                        if (c == '_') continue;             // $readmemh allows underscores as separators
                        if (!is_hex_digit(c)) return std::unexpected(Error(SemErr::HexBadToken, std::format("{}:{}: '{}'", name, line_no, token)));
                        digits.push_back(c);
                    }
                    if (digits.size() != 2 && digits.size() != 8) {
                        return std::unexpected(Error(SemErr::HexBadToken, std::format("{}:{}: '{}'", name, line_no, token)));
                    }
                    if (width == 0) width = digits.size();
                    if (digits.size() != width) {
                        return std::unexpected(Error(SemErr::HexMixedWidth, std::format("{}:{}", name, line_no)));
                    }
                    uint32_t value{0};
                    for (const char c : digits) value = (value << 4) | hex_value(c);
                    if (width == 2) {
                        image.push_back(static_cast<uint8_t>(value));
                    } else {    // 32-bit words are stored little endian, the way the core reads them
                        for (int i{0}; i < 4; ++i) image.push_back(static_cast<uint8_t>(value >> (8 * i)));
                    }
                }
            }
            return image;
        }

    }

    std::expected<std::vector<uint8_t>, Error> read_program_image(const std::filesystem::path& path) {
        std::error_code ec{};
        if (!std::filesystem::is_regular_file(path, ec)) return std::unexpected(Error(SemErr::FileNotFound, path.string()));

        const auto ext = to_lower(path.extension().string());
        if (ext != ".bin" && ext != ".hex") return std::unexpected(Error(SemErr::FileBadExtension, path.string()));

        std::ifstream file{path, std::ios::binary};
        if (!file) return std::unexpected(Error(SemErr::FileReadFailed, path.string()));
        const std::string content{std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}};
        if (file.bad()) return std::unexpected(Error(SemErr::FileReadFailed, path.string()));

        std::vector<uint8_t> image{};
        if (ext == ".bin") {
            image.assign(content.begin(), content.end());
        } else {
            auto parsed = parse_readmemh(content, path.filename().string());
            if (!parsed) return std::unexpected(parsed.error());
            image = std::move(*parsed);
        }
        while (image.size() % 4 != 0) image.push_back(0x00);    // the BIOS only takes whole words
        return image;
    }

    std::expected<void, Error> CommandAnalyzer::require_transport(const Context& ctx) const {
        if (!ctx.link_open || !ctx.snap.transport_open) return std::unexpected(Error(SemErr::NoTransport));
        return {};
    }

    // BIOS-interfacing commands: connected, BIOS idle, nothing queued
    std::expected<void, Error> CommandAnalyzer::require_bios(const Context& ctx, bool allowed_when_limited) const {
        if (auto res = require_transport(ctx); !res) return res;
        switch (ctx.snap.state) {
            case SessionState::Idle:            break;
            case SessionState::Disconnected:    return std::unexpected(Error(SemErr::NotConnected));
            case SessionState::ProgramRunning:  return std::unexpected(Error(SemErr::ProgramRunning));
            default:                            return std::unexpected(Error(SemErr::NotIdle));
        }
        if (!ctx.snap.raw_pending.empty()) return std::unexpected(Error(SemErr::RawQueuePending, std::to_string(ctx.snap.raw_pending.size())));
        if (ctx.snap.limited && !allowed_when_limited) return std::unexpected(Error(SemErr::LimitedState));
        return {};
    }

    std::expected<void, Error> CommandAnalyzer::check_connect(const commands::CommandConnect& cmd, const Context& ctx) const {
        if (ctx.profile.kind == ProfileKind::Sim) {
            if (!ctx.link_open || !ctx.snap.transport_open) return std::unexpected(Error(SemErr::NoTransport, "run `net` first"));
        } else if (!ctx.link_open && !cmd.port_name && ctx.profile.serial_port.empty()) {
            return std::unexpected(Error(SemErr::NoSerialPort));
        }
        if (ctx.snap.state == SessionState::ProgramRunning) return std::unexpected(Error(SemErr::ProgramRunning));
        if (ctx.snap.state != SessionState::Idle && ctx.snap.state != SessionState::Disconnected) return std::unexpected(Error(SemErr::NotIdle));
        if (!ctx.snap.raw_pending.empty()) return std::unexpected(Error(SemErr::RawQueuePending, std::to_string(ctx.snap.raw_pending.size())));
        return {};
    }

    std::expected<void, Error> CommandAnalyzer::check_load(commands::CommandLoad& cmd, const Context& ctx) const {
        if (auto res = require_bios(ctx, false); !res) return res;

        auto image = read_program_image(cmd.filename);
        if (!image) return std::unexpected(image.error());
        if (image->empty()) return std::unexpected(Error(SemErr::ProgramEmpty, cmd.filename));

        const auto& device = ctx.snap.cache.device;
        const uint32_t prog_ofs = device ? device->prog_offset : DEFAULT_PROG_OFFSET;
        const uint32_t prog_size = device ? device->prog_size : DEFAULT_PROG_SIZE;
        const uint64_t top = static_cast<uint64_t>(prog_ofs) + prog_size;
        const uint32_t offset = cmd.start_addr.value_or(prog_ofs);

        if (offset % 4 != 0) return std::unexpected(Error(SemErr::OffsetUnaligned, std::format("0x{:08X}", offset)));
        if (offset < prog_ofs || offset >= top) {
            return std::unexpected(Error(SemErr::OffsetOutOfRange, std::format("0x{:08X} (program space 0x{:08X}-0x{:08X})", offset, prog_ofs, top - 1)));
        }
        if (static_cast<uint64_t>(offset) + image->size() + PRG_TAIL_BYTES > top) {
            return std::unexpected(Error(SemErr::ProgramTooBig, std::format("{} bytes + {} byte tail at 0x{:08X}, {} bytes free",
                image->size(), PRG_TAIL_BYTES, offset, top - offset)));
        }

        cmd.start_addr = offset;
        cmd.image = std::make_shared<const std::vector<uint8_t>>(std::move(*image));
        return {};
    }

    std::expected<void, Error> CommandAnalyzer::analyze(commands::Command& cmd, const Context& ctx) const {
        using namespace commands;
        const bool sim = ctx.profile.kind == ProfileKind::Sim;

        return std::visit(overload{
            [&ctx](const CommandSwitch&) -> std::expected<void, Error> {
                if (ctx.snap.state != SessionState::Disconnected && ctx.snap.state != SessionState::Idle) {
                    return std::unexpected(Error(SemErr::SwitchNotAllowed));
                }
                return {};
            },
            [&ctx, sim](const CommandNet&) -> std::expected<void, Error> {
                if (!sim) return std::unexpected(Error(SemErr::SimOnly, "net"));
                if (ctx.link_open) return std::unexpected(Error(SemErr::TransportAlreadyOpen));
                return {};
            },
            [sim](const CommandScan&) -> std::expected<void, Error> {
                if (sim) return std::unexpected(Error(SemErr::FpgaOnly, "scan"));
                return {};
            },
            [this, &ctx](const CommandConnect& c) -> std::expected<void, Error> { return check_connect(c, ctx); },
            [this, &ctx](CommandLoad& c) -> std::expected<void, Error> { return check_load(c, ctx); },
            [this, &ctx](const CommandRun&) -> std::expected<void, Error> {
                if (auto res = require_bios(ctx, false); !res) return res;
                if (!ctx.snap.cache.program_valid) return std::unexpected(Error(SemErr::NoValidProgram));
                return {};
            },
            [this, &ctx](const CommandVerify&) -> std::expected<void, Error> {
                if (auto res = require_bios(ctx, false); !res) return res;
                if (!ctx.snap.cache.program_valid) return std::unexpected(Error(SemErr::NoValidProgram));
                return {};
            },
            [this, &ctx](const CommandHexDump& c) -> std::expected<void, Error> {
                if (auto res = require_bios(ctx, false); !res) return res;
                if (c.byte_count == 0) return std::unexpected(Error(SemErr::DumpSizeZero));
                if (static_cast<uint64_t>(c.start_addr) + c.byte_count > BIOS_DATA_TOP) {
                    return std::unexpected(Error(SemErr::DumpOutOfBounds, std::format("0x{:08X} + {} (limit 0x{:08X})", c.start_addr, c.byte_count, BIOS_DATA_TOP - 1)));
                }
                return {};
            },
            [this, &ctx](const CommandEcho& c) -> std::expected<void, Error> {
                if (c.terminal_echo) return {};    // client side only
                if (auto res = require_bios(ctx, false); !res) return res;
                if (c.msg.empty()) return std::unexpected(Error(SemErr::EchoEmpty));
                if (c.msg.size() > ECHO_BUF_SIZE) return std::unexpected(Error(SemErr::EchoTooLong, std::to_string(c.msg.size())));
                return {};
            },
            [this, &ctx](const CommandSelfTest&) -> std::expected<void, Error> { return require_bios(ctx, true); },
            [this, &ctx](const CommandTelemetry&) -> std::expected<void, Error> { return require_bios(ctx, false); },
            [this, &ctx](const CommandTelemetryStatus&) -> std::expected<void, Error> { return require_bios(ctx, false); },
            [this, &ctx](const CommandDeviceInfo&) -> std::expected<void, Error> { return require_bios(ctx, false); },
            [this, &ctx](const CommandSync&) -> std::expected<void, Error> { return require_bios(ctx, false); },
            [this, &ctx](const CommandSendByte&) -> std::expected<void, Error> { return require_transport(ctx); },
            [this, &ctx](const CommandSendByteList& c) -> std::expected<void, Error> {
                if (!c.tx_byte_list) return {};    // only lists the queue
                if (c.tx_byte_list->empty()) return std::unexpected(Error(SemErr::BytesEmpty));
                if (c.interval == 0) return std::unexpected(Error(SemErr::IntervalZero));
                return require_transport(ctx);
            },
            [](const auto&) -> std::expected<void, Error> { return {}; },    // client side (config, monitor, log, help ...)
        }, cmd);
    }

}
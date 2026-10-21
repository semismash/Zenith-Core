#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "bios_error.hpp"
#include "commands.hpp"

namespace responses {

    // 0xDA reply
    struct DeviceData {
        std::string bios_name;
        std::string arch;
        uint32_t reg_count{0};
        uint32_t clk_hz{0};
        uint32_t baud{0};
        uint32_t ram_offset{0};
        uint32_t ram_size{0};
        uint32_t prog_offset{0};
        uint32_t prog_size{0};
        uint32_t rom_offset{0};
        uint32_t rom_size{0};
    };

    // none = unknown (after boot, after an E7 error)
    struct TelemetrySettings {
        std::optional<bool> bios;           // 0x70
        std::optional<bool> program;        // 0x71
        std::optional<bool> program_reset;  // 0x72
    };

    struct TelemetryCounters {
        uint32_t instr{0};
        uint32_t stall{0};
        uint32_t load_use{0};
        uint32_t branch_flush{0};
    };

    struct PostResults {
        bool passed{false};
        std::array<bool, 6> tests{};
    };

    struct LoadArgs {
        bool telemode{false};
        bool telereset{false};
        bool reg_disp{false};
    };

    // device data and state cache, updated from the bytes the BIOS sends (see Cache rules)
    struct DeviceCache {
        std::optional<DeviceData> device;
        std::optional<uint8_t> bios_state;
        std::optional<PostResults> post;
        bool program_valid{false};
        uint32_t program_offset{0};
        uint32_t program_size{0};
        TelemetrySettings telemetry;
        std::optional<LoadArgs> last_load;  // CC re-runs with these

        void clear() { *this = DeviceCache{}; }
    };

    // events: emitted by the session (reader thread), turned into text by the response printer
    struct EvMonitorByte { uint8_t byte; };
    struct EvStateLog { uint8_t state; };
    struct EvBiosError { bios_error::BiosError error; };
    struct EvClientTimeout {};
    struct EvProtocolMismatch { uint8_t byte; };
    struct EvUnsolicited { uint8_t byte; };
    struct EvCooldownStart {};
    struct EvCooldownEnd { bool by_fallback; };
    struct EvMessage { std::string text; };             // 0x3F flush
    struct EvProgramOutput { std::string bytes; };      // raw program output
    struct EvProgramStart {};
    struct EvProgramDone {};
    struct EvProgramStillRunning {};
    struct EvReboot {};
    struct EvLinkLost { std::string detail; };
    struct EvRawDropped { size_t count; };
    struct EvPostResults { PostResults post; };
    struct EvTelemetrySettings { TelemetrySettings settings; };
    struct EvTelemetryApplied {};
    struct EvTelemetryStatus {
        TelemetryCounters counters;
        std::variant<bool, std::set<commands::TelemetryParam>> filter;
    };
    struct EvDumpProgress { uint32_t received; uint32_t total; };
    struct EvMemDump { uint32_t offset; std::vector<uint8_t> data; };
    struct EvVerifyResult {
        uint32_t compared;
        std::optional<uint32_t> mismatch_addr;                  // first differing address
        std::optional<std::pair<uint32_t, uint32_t>> sizes;     // read back vs expected, if they differ
    };
    struct EvLoadComplete { uint32_t offset; uint32_t size; };
    struct EvDeviceData {
        DeviceData data;
        std::set<commands::DeviceDataParam> filter;
    };
    struct EvRegisters { std::array<uint32_t, 31> regs; };   // x1 - x31

    using Event = std::variant<
        EvMonitorByte, EvStateLog, EvBiosError, EvClientTimeout, EvProtocolMismatch,
        EvUnsolicited, EvCooldownStart, EvCooldownEnd, EvMessage, EvProgramOutput,
        EvProgramStart, EvProgramDone, EvProgramStillRunning, EvReboot, EvLinkLost,
        EvRawDropped, EvPostResults, EvTelemetrySettings, EvTelemetryApplied, EvTelemetryStatus,
        EvDumpProgress, EvMemDump, EvVerifyResult, EvLoadComplete, EvDeviceData, EvRegisters
    >;

    using Events = std::vector<Event>;

}
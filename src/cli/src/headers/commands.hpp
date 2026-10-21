#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <variant>
#include <vector>

namespace commands {

    // CommandName enum removed, the variant index already tells the commands apart

    enum class DeviceDataParam {
        Arch, Reg, ROM, RAM, Mem, Clk, Baud
    };

    enum class TelemetryParam { // cycles & CPI param TBA later
        Instr, Stall, StallPcnt, LoadUseStall, BranchFlush
    };

    // commands list:
    struct CommandConfig {
        std::optional<std::string> key;     // none = print all settings of the active profile
        std::optional<std::string> value;   // none = print this one setting
    };

    struct CommandSwitch {
        bool fpga_else_sim; // fpga = true, sim = false
    };

    struct CommandReset {};

    struct CommandNet {
        std::optional<std::string> host;    // defaults to the profile's host/port
        std::optional<uint16_t> port;
    };

    struct CommandScan {};

    struct CommandConnect {
        std::optional<std::string> port_name;   // fpga only, falls back to the serial_port setting
        std::optional<double> timeout_s;        // SYN-ACK wait, wall-clock seconds
        std::optional<double> retry_s;          // retry period after a failed attempt
    };

    struct CommandLoad {
        std::string filename;
        bool run;
        bool verify;
        std::optional<uint32_t> start_addr;     // the analyzer fills in the program offset from device data if not given
        bool telemode;
        bool telereset;
        bool reg_disp;
        std::shared_ptr<const std::vector<uint8_t>> image;  // padded program image, filled in by the analyzer
    };

    struct CommandRun {};   // no offset, the BIOS always runs from the last load offset

    struct CommandVerify {};

    struct CommandTelemetry {
        std::optional<bool> telemode;   // 0x70
        std::optional<bool> telereset;  // 0x72
        bool inst_reset;                // 0x73
    };

    struct CommandMonitor {
        std::optional<bool> is_monitor; // none = show current status
    };

    struct CommandLog {
        std::optional<bool> is_log;     // none = show current status
    };

    struct CommandEcho {
        std::string msg;
        bool terminal_echo;
    };

    struct CommandDeviceInfo {
        std::set<DeviceDataParam> device_data_args;    // empty = everything
    };

    struct CommandSync {};

    struct CommandSendByte {
        uint8_t tx_byte;
    };

    struct CommandSendByteList {
        std::optional<std::vector<uint8_t>> tx_byte_list;   // none = list the bytes still queued
        uint32_t interval;                                  // in units of 10 baud ticks (1 byte-time)
    };

    struct CommandTelemetryStatus {
        std::variant<bool, std::set<TelemetryParam>> telemetry_args;
    };

    struct CommandSelfTest {};

    struct CommandHexDump {
        uint32_t byte_count;
        uint32_t start_addr;
    };

    struct CommandClear {};
    struct CommandHelp {
        std::optional<std::string> topic;
    };
    struct CommandAbout {};
    struct CommandGitHub {};
    struct CommandExit {};

    using Command = std::variant<
        CommandConfig, CommandSwitch, CommandReset, CommandNet,
        CommandScan, CommandConnect, CommandLoad, CommandRun,
        CommandVerify, CommandTelemetry, CommandMonitor, CommandLog,
        CommandEcho, CommandDeviceInfo, CommandSync, CommandSendByte,
        CommandSendByteList, CommandTelemetryStatus, CommandSelfTest, CommandHexDump,
        CommandClear, CommandHelp, CommandAbout, CommandGitHub, CommandExit
    >;

}
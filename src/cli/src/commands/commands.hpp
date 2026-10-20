#pragma once

#include <set>
#include <vector>
#include <cstdint>
#include <string>
#include <variant>

namespace commands {

    // probably not required, to be removed later
    enum class CommandName {
        Scan, Connect,
        Load, Run, Verify,
        Telemetry, Status,
        Monitor, Log,
        Echo, DeviceInfo, Sync,
        SendByte, SendBytes, HexDump,
        Clear, Help, About, GitHub
    };

    enum class DeviceDataParam {
        Arch, Reg, ROM, RAM, Mem, Clk, Baud
    };

    enum class TelemetryParam { // cycles & CPI param TBA later
        Instr, Stall, StallPcnt, LoadUseStall, BranchFlush
    };
    
    // commands list:
    struct CommandScan {};

    struct CommandConnect {
        // ports TBD
    };

    struct CommandLoad {
        std::string filename;
        bool run;
        bool verify;
        uint32_t start_addr;
        bool telemode;
        bool telereset;
        bool reg_disp;
    };

    struct CommandRun {
        uint32_t start_addr;
    };

    struct CommandVerify {};

    struct CommandTelemetry {
        bool telemode;
        bool telereset;
        bool inst_reset;
    };

    struct CommandMonitor {
        bool is_monitor;
    };

    struct CommandLog {
        bool is_log;
    };

    struct CommandEcho {
        std::string msg;
        bool terminal_echo;
    };

    struct CommandDeviceInfo {
        std::set<DeviceDataParam> device_data_args;
    };

    struct CommandSync {};

    struct CommandSendByte {
        uint8_t tx_byte;
    };

    struct CommandSendByteList {
        std::vector<uint8_t> tx_byte_list;
    };

    struct CommandTelemetryStatus {
        std::variant<bool, std::set<TelemetryParam>> telemetry_args;
    };

    struct CommandSelfTest {};

    struct CommandHexDump {
        uint32_t byte_count;
        uint32_t start_addr;
    };

    struct CommandHelp {};
    struct CommandAbout {};
    struct CommandGitHub {};

    using Command = std::variant<
        CommandScan, CommandConnect, CommandLoad, CommandRun, 
        CommandVerify, CommandTelemetry, CommandMonitor, CommandLog, 
        CommandEcho, CommandDeviceInfo, CommandUpdateInfo, CommandSendByte, 
        CommandSendByteList, CommandTelemetryStatus, CommandSelfTest, CommandHexDump, 
        CommandHelp, CommandAbout, CommandGitHub
    >;
    
}
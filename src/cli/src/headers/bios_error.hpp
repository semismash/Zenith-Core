#pragma once

#include <cstdint>
#include <string_view>
#include <variant>

#include "codes.hpp"
#include "overload.hpp"

namespace bios_error {

    enum class BiosErrorType {
        BIOSErrorMessage,
        BIOSErrorSelfTest,
        BIOSErrorTelemetry,
        BIOSErrorMemory,
        BIOSErrorConnect,
        BIOSErrorProgram,
        BIOSErrorDeviceData,
        BIOSErrorCritical,
        BIOSErrorBIOS,
        BIOSErrorUnknown
    };

    enum class MessageErrorType {
        GetMsgTooBig,
        PutMsgTooBig,
        GetMsgUnverified,
        Unknown
    };

    enum class SelfTestErrorType { SelfTestFail };

    enum class TelemetryErrorType {
        TelemetryUnverified,
        TelemetryParamInvalid,
        TelemetryArgInvalid,
        Unknown
    };

    enum class MemoryErrorType {
        MemoryOutOfBounds,
        Unknown
    };

    enum class ConnectionErrorType {
        InvalidConnection,
        ConnectionTimeout,
        Unknown
    };

    enum class ProgramErrorType {
        ProgramUnverified,
        ProgramParamInvalid,
        ProgramArgInvalid,
        ProgramTooBig,
        ProgramOffsetUnaligned,
        ProgramSizeUnaligned,
        Unknown
    };

    enum class DeviceDataErrorType { DeviceDataError };

    enum class CriticalBIOSErrorType { CriticalBIOSError };

    // BIOSArgInvalid removed, log is client side only now so EF only has timeout (01) and invalid command (02)
    enum class BIOSErrorBIOSType {
        BIOSTimeout,
        BIOSCmdInvalid,
        Unknown
    };

    using SubType = std::variant<
        MessageErrorType, SelfTestErrorType, TelemetryErrorType, MemoryErrorType,
        ConnectionErrorType, ProgramErrorType, DeviceDataErrorType, CriticalBIOSErrorType,
        BIOSErrorBIOSType, std::monostate
    >;

    struct BiosError {
        BiosErrorType type;
        SubType sub;
        uint8_t family;
        uint8_t code;   // 0x00 for the single byte 0xEE
    };

    // only meaningful at a frame boundary, raw data (dumps, words, strings) can contain these bytes too
    inline constexpr bool is_error_family(uint8_t byte) {
        using namespace bios_protocol;
        return byte == ERR_MESSAGE || byte == ERR_SELF_TEST || byte == ERR_TELEMETRY
            || byte == ERR_MEMORY || byte == ERR_CONNNECT || byte == ERR_PROGRAM
            || byte == ERR_DEVICE_DATA || byte == ERR_CRITICAL || byte == ERR_BIOS;
    }

    // every error is family + sub-code, except 0xEE
    inline constexpr bool is_single_byte(uint8_t family) { return family == bios_protocol::ERR_CRITICAL; }

    inline BiosError decode(uint8_t family, uint8_t code) {
        using namespace bios_protocol;
        switch (family) {
            case ERR_MESSAGE: {
                auto sub{MessageErrorType::Unknown};
                switch (code) {
                    case ERR_GET_MSG_TOO_BIG:       sub = MessageErrorType::GetMsgTooBig; break;
                    case ERR_PUT_MSG_TOO_BIG:       sub = MessageErrorType::PutMsgTooBig; break;
                    case ERR_GET_MSG_UNVERIFIED:    sub = MessageErrorType::GetMsgUnverified; break;
                    default: break;
                }
                return { BiosErrorType::BIOSErrorMessage, sub, family, code };
            }
            case ERR_SELF_TEST:
                return { BiosErrorType::BIOSErrorSelfTest, SelfTestErrorType::SelfTestFail, family, code };
            case ERR_TELEMETRY: {
                auto sub{TelemetryErrorType::Unknown};
                switch (code) {
                    case ERR_META_UNVERIFIED:       sub = TelemetryErrorType::TelemetryUnverified; break;
                    case ERR_META_PARAM_INVALID:    sub = TelemetryErrorType::TelemetryParamInvalid; break;
                    case ERR_META_ARG_INVALID:      sub = TelemetryErrorType::TelemetryArgInvalid; break;
                    default: break;
                }
                return { BiosErrorType::BIOSErrorTelemetry, sub, family, code };
            }
            case ERR_MEMORY: {
                const auto sub = code == ERR_MEM_OUT_OF_BOUNDS ? MemoryErrorType::MemoryOutOfBounds : MemoryErrorType::Unknown;
                return { BiosErrorType::BIOSErrorMemory, sub, family, code };
            }
            case ERR_CONNNECT: {
                auto sub{ConnectionErrorType::Unknown};
                switch (code) {
                    case ERR_CONNECTION_INVALID:    sub = ConnectionErrorType::InvalidConnection; break;
                    case ERR_CONNECTION_TIMEOUT:    sub = ConnectionErrorType::ConnectionTimeout; break;
                    default: break;
                }
                return { BiosErrorType::BIOSErrorConnect, sub, family, code };
            }
            case ERR_PROGRAM: {
                auto sub{ProgramErrorType::Unknown};
                switch (code) {
                    case ERR_PRG_UNVERIFIED:        sub = ProgramErrorType::ProgramUnverified; break;
                    case ERR_PRG_PARAM_INVALID:     sub = ProgramErrorType::ProgramParamInvalid; break;
                    case ERR_PRG_ARG_INVALID:       sub = ProgramErrorType::ProgramArgInvalid; break;
                    case ERR_PRG_TOO_BIG:           sub = ProgramErrorType::ProgramTooBig; break;
                    case ERR_PRG_OFST_UNALIGN:      sub = ProgramErrorType::ProgramOffsetUnaligned; break;
                    case ERR_PRG_SIZE_UNALIGN:      sub = ProgramErrorType::ProgramSizeUnaligned; break;
                    default: break;
                }
                return { BiosErrorType::BIOSErrorProgram, sub, family, code };
            }
            case ERR_DEVICE_DATA:
                return { BiosErrorType::BIOSErrorDeviceData, DeviceDataErrorType::DeviceDataError, family, code };
            case ERR_CRITICAL:
                return { BiosErrorType::BIOSErrorCritical, CriticalBIOSErrorType::CriticalBIOSError, family, code };
            case ERR_BIOS: {
                auto sub{BIOSErrorBIOSType::Unknown};
                switch (code) {
                    case ERR_BIOS_TIMEOUT:          sub = BIOSErrorBIOSType::BIOSTimeout; break;
                    case ERR_BIOS_INV_CMD:          sub = BIOSErrorBIOSType::BIOSCmdInvalid; break;
                    default: break;
                }
                return { BiosErrorType::BIOSErrorBIOS, sub, family, code };
            }
            default:
                return { BiosErrorType::BIOSErrorUnknown, std::monostate{}, family, code };
        }
    }

    // key into messages.toml for the error text
    inline std::string_view message_key(const BiosError& err) {
        return std::visit(overload{
            [](MessageErrorType t) -> std::string_view {
                switch (t) {
                    case MessageErrorType::GetMsgTooBig:        return "bios_error.msg_get_too_big";
                    case MessageErrorType::PutMsgTooBig:        return "bios_error.msg_put_too_big";
                    case MessageErrorType::GetMsgUnverified:    return "bios_error.msg_unverified";
                    case MessageErrorType::Unknown:             break;
                }
                return "bios_error.unknown";
            },
            [](SelfTestErrorType) -> std::string_view { return "bios_error.self_test"; },
            [](TelemetryErrorType t) -> std::string_view {
                switch (t) {
                    case TelemetryErrorType::TelemetryUnverified:   return "bios_error.tele_unverified";
                    case TelemetryErrorType::TelemetryParamInvalid: return "bios_error.tele_param";
                    case TelemetryErrorType::TelemetryArgInvalid:   return "bios_error.tele_arg";
                    case TelemetryErrorType::Unknown:               break;
                }
                return "bios_error.unknown";
            },
            [](MemoryErrorType t) -> std::string_view {
                return t == MemoryErrorType::MemoryOutOfBounds ? "bios_error.mem_bounds" : "bios_error.unknown";
            },
            [](ConnectionErrorType t) -> std::string_view {
                switch (t) {
                    case ConnectionErrorType::InvalidConnection:    return "bios_error.conn_invalid";
                    case ConnectionErrorType::ConnectionTimeout:    return "bios_error.conn_timeout";
                    case ConnectionErrorType::Unknown:              break;
                }
                return "bios_error.unknown";
            },
            [](ProgramErrorType t) -> std::string_view {
                switch (t) {
                    case ProgramErrorType::ProgramUnverified:       return "bios_error.prg_unverified";
                    case ProgramErrorType::ProgramParamInvalid:     return "bios_error.prg_param";
                    case ProgramErrorType::ProgramArgInvalid:       return "bios_error.prg_arg";
                    case ProgramErrorType::ProgramTooBig:           return "bios_error.prg_too_big";
                    case ProgramErrorType::ProgramOffsetUnaligned:  return "bios_error.prg_offset_unaligned";
                    case ProgramErrorType::ProgramSizeUnaligned:    return "bios_error.prg_size_unaligned";
                    case ProgramErrorType::Unknown:                 break;
                }
                return "bios_error.unknown";
            },
            [](DeviceDataErrorType) -> std::string_view { return "bios_error.device_data"; },
            [](CriticalBIOSErrorType) -> std::string_view { return "bios_error.critical"; },
            [](BIOSErrorBIOSType t) -> std::string_view {
                switch (t) {
                    case BIOSErrorBIOSType::BIOSTimeout:    return "bios_error.bios_timeout";
                    case BIOSErrorBIOSType::BIOSCmdInvalid: return "bios_error.bios_cmd_invalid";
                    case BIOSErrorBIOSType::Unknown:        break;
                }
                return "bios_error.unknown";
            },
            [](std::monostate) -> std::string_view { return "bios_error.unknown"; },
        }, err.sub);
    }

}
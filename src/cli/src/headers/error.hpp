#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <variant>

#include "overload.hpp"

namespace error {

    // syntax level, caught by the command parser
    enum class ParseError {
        UnterminatedQuote,
        UnterminatedBracket,
        CommandSyntax,
        InvalidNumber,
        NumberOutOfRange,
        InvalidBool,
        InvalidToggle,
        InvalidProfile,
        InvalidInfoParam,
        InvalidTelemetryParam,
        InvalidByteList,
        InvalidHostPort,
        InvalidSeconds,
        ConflictingFlags,
        TooManyArgs,
    };

    // command analyzer, caught before anything is sent to the BIOS ('responsible host')
    enum class SemanticError {
        NotConnected,
        NoTransport,
        TransportAlreadyOpen,
        SimOnly,
        FpgaOnly,
        NotIdle,
        ProgramRunning,
        LimitedState,
        RawQueuePending,
        SwitchNotAllowed,
        FileNotFound,
        FileReadFailed,
        FileBadExtension,
        HexBadToken,
        HexMixedWidth,
        ProgramEmpty,
        OffsetUnaligned,
        OffsetOutOfRange,
        ProgramTooBig,
        NoValidProgram,
        DumpSizeZero,
        DumpOutOfBounds,
        EchoEmpty,
        EchoTooLong,
        IntervalZero,
        BytesEmpty,
        NoSerialPort,
        ConfigUnknownKey,
        ConfigBadValue,
        ConfigWrongProfile,
    };

    // tcp / serial / reset side channel
    enum class TransportError {
        ResolveFailed,
        ConnectFailed,
        SocketError,
        WriteFailed,
        ReadFailed,
        PeerClosed,
        TxStalled,
        SerialOpenFailed,
        SerialConfigFailed,
        SerialIoFailed,
        SerialScanFailed,
        ResetChannelFailed,
        ResetRejected,
    };

    class Error {

        public:

            using ErrorKind = std::variant<ParseError, SemanticError, TransportError>;

            ErrorKind error;
            std::string detail;     // fills the {} in the message text, can be empty

            Error(ErrorKind kind, std::string det = {}) :
                error{kind},
                detail{std::move(det)}
            { }

            std::string_view message_key() const;

    };

    // key into messages.toml
    inline std::string_view Error::message_key() const {
        return std::visit(overload{
            [](ParseError err) -> std::string_view {
                switch (err) {
                    case ParseError::UnterminatedQuote:     return "parse_error.unterminated_quote";
                    case ParseError::UnterminatedBracket:   return "parse_error.unterminated_bracket";
                    case ParseError::CommandSyntax:         return "parse_error.syntax";
                    case ParseError::InvalidNumber:         return "parse_error.invalid_number";
                    case ParseError::NumberOutOfRange:      return "parse_error.number_range";
                    case ParseError::InvalidBool:           return "parse_error.invalid_bool";
                    case ParseError::InvalidToggle:         return "parse_error.invalid_toggle";
                    case ParseError::InvalidProfile:        return "parse_error.invalid_profile";
                    case ParseError::InvalidInfoParam:      return "parse_error.invalid_info";
                    case ParseError::InvalidTelemetryParam: return "parse_error.invalid_telemetry";
                    case ParseError::InvalidByteList:       return "parse_error.invalid_bytes";
                    case ParseError::InvalidHostPort:       return "parse_error.invalid_hostport";
                    case ParseError::InvalidSeconds:        return "parse_error.invalid_seconds";
                    case ParseError::ConflictingFlags:      return "parse_error.conflicting_flags";
                    case ParseError::TooManyArgs:           return "parse_error.too_many_args";
                }
                return "parse_error.unknown";
            },
            [](SemanticError err) -> std::string_view {
                switch (err) {
                    case SemanticError::NotConnected:           return "sema_error.not_connected";
                    case SemanticError::NoTransport:            return "sema_error.no_transport";
                    case SemanticError::TransportAlreadyOpen:   return "sema_error.transport_open";
                    case SemanticError::SimOnly:                return "sema_error.sim_only";
                    case SemanticError::FpgaOnly:               return "sema_error.fpga_only";
                    case SemanticError::NotIdle:                return "sema_error.not_idle";
                    case SemanticError::ProgramRunning:         return "sema_error.program_running";
                    case SemanticError::LimitedState:           return "sema_error.limited_state";
                    case SemanticError::RawQueuePending:        return "sema_error.raw_pending";
                    case SemanticError::SwitchNotAllowed:       return "sema_error.switch_not_allowed";
                    case SemanticError::FileNotFound:           return "sema_error.file_not_found";
                    case SemanticError::FileReadFailed:         return "sema_error.file_read";
                    case SemanticError::FileBadExtension:       return "sema_error.file_extension";
                    case SemanticError::HexBadToken:            return "sema_error.hex_token";
                    case SemanticError::HexMixedWidth:          return "sema_error.hex_mixed";
                    case SemanticError::ProgramEmpty:           return "sema_error.program_empty";
                    case SemanticError::OffsetUnaligned:        return "sema_error.offset_unaligned";
                    case SemanticError::OffsetOutOfRange:       return "sema_error.offset_range";
                    case SemanticError::ProgramTooBig:          return "sema_error.program_too_big";
                    case SemanticError::NoValidProgram:         return "sema_error.no_program";
                    case SemanticError::DumpSizeZero:           return "sema_error.dump_zero";
                    case SemanticError::DumpOutOfBounds:        return "sema_error.dump_bounds";
                    case SemanticError::EchoEmpty:              return "sema_error.echo_empty";
                    case SemanticError::EchoTooLong:            return "sema_error.echo_long";
                    case SemanticError::IntervalZero:           return "sema_error.interval_zero";
                    case SemanticError::BytesEmpty:             return "sema_error.bytes_empty";
                    case SemanticError::NoSerialPort:           return "sema_error.no_serial_port";
                    case SemanticError::ConfigUnknownKey:       return "sema_error.config_key";
                    case SemanticError::ConfigBadValue:         return "sema_error.config_value";
                    case SemanticError::ConfigWrongProfile:     return "sema_error.config_profile";
                }
                return "sema_error.unknown";
            },
            [](TransportError err) -> std::string_view {
                switch (err) {
                    case TransportError::ResolveFailed:         return "transport_error.resolve";
                    case TransportError::ConnectFailed:         return "transport_error.connect";
                    case TransportError::SocketError:           return "transport_error.socket";
                    case TransportError::WriteFailed:           return "transport_error.write";
                    case TransportError::ReadFailed:            return "transport_error.read";
                    case TransportError::PeerClosed:            return "transport_error.peer_closed";
                    case TransportError::TxStalled:             return "transport_error.tx_stalled";
                    case TransportError::SerialOpenFailed:      return "transport_error.serial_open";
                    case TransportError::SerialConfigFailed:    return "transport_error.serial_config";
                    case TransportError::SerialIoFailed:        return "transport_error.serial_io";
                    case TransportError::SerialScanFailed:      return "transport_error.serial_scan";
                    case TransportError::ResetChannelFailed:    return "transport_error.reset_channel";
                    case TransportError::ResetRejected:         return "transport_error.reset_rejected";
                }
                return "transport_error.unknown";
            },
        }, error);
    }

}
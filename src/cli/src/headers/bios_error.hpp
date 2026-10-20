#pragma once

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

    enum class BIOSErrorBIOSType {
        BIOSTimeout,
        BIOSArgInvalid,
        BIOSCmdInvalid,
        Unknown
    };

}
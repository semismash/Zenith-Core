// AUTO-GENERATED from protocol.inc by gen_codes.py. DO NOT EDIT.
#pragma once
#include <cstdint>

namespace bios_protocol {

// TO BIOS
// MESSAGES
inline constexpr uint8_t TB_MSG_ECHO = 0x3A;
inline constexpr uint8_t TB_MSG_STR = 0x3D;
// SELF TEST
inline constexpr uint8_t TB_ST_INIT = 0x5A;
// TELEMETRY
inline constexpr uint8_t TB_META_START = 0x7A;
inline constexpr uint8_t TB_META_BIOSTR = 0x70;  // bios telemetry
inline constexpr uint8_t TB_META_PRGTR = 0x71;  // program telemetry
inline constexpr uint8_t TB_META_PRGRST = 0x72;  // program telemetry reset
inline constexpr uint8_t TB_META_RESET = 0x73;  // instant reset
    inline constexpr uint8_t META_ARG_OFF = 0x00;
    inline constexpr uint8_t META_ARG_ON = 0x01;
inline constexpr uint8_t TB_META_DISP = 0x7D;  // telemetry status display request (status command)
// MEMORY
inline constexpr uint8_t TB_MEM_DUMP = 0x8A;
// CONNECTION
inline constexpr uint8_t TB_NET_SYN = 0xAA;
inline constexpr uint8_t TB_NET_ACK = 0xAC;
// PROGRAM RUNTIME
inline constexpr uint8_t TB_PRG_LOAD = 0xCA;
    inline constexpr uint8_t PRG_RUNNOW = 0xC0;
    inline constexpr uint8_t PRG_VERIFY = 0xC1;
    inline constexpr uint8_t PRG_OFFSET = 0xC2;
    inline constexpr uint8_t PRG_T_MODE = 0xC3;
    inline constexpr uint8_t PRG_T_RST = 0xC4;
    inline constexpr uint8_t PRG_REGDISP = 0xC5;
inline constexpr uint8_t TB_PRG_VERIFY = 0xCB;  // different from the verify argument, this is for the actual command itself
inline constexpr uint8_t TB_PRG_RUN = 0xCC;
// DEVICE DATA
inline constexpr uint8_t TB_DD_DATA = 0xDA;
// BIOS DATA MONITORING
inline constexpr uint8_t TB_BIOS_DATA = 0xFA;

// FROM BIOS
inline constexpr uint8_t FB_MSG_ECHO = 0x3A;
inline constexpr uint8_t FB_MSG_STR = 0x3D;
inline constexpr uint8_t FB_MSG_FLSH = 0x3F;
// SELF TEST
inline constexpr uint8_t FB_ST_TESTBYTE = 0x50;
inline constexpr uint8_t FB_ST_RESULTS = 0x5D;
    inline constexpr uint8_t ST_PARAM_TEST_0 = 0x00;
    inline constexpr uint8_t ST_PARAM_TEST_1 = 0x01;
    inline constexpr uint8_t ST_PARAM_TEST_2 = 0x02;
    inline constexpr uint8_t ST_PARAM_TEST_3 = 0x03;
    inline constexpr uint8_t ST_PARAM_TEST_4 = 0x04;
    inline constexpr uint8_t ST_PARAM_TEST_5 = 0x05;
inline constexpr uint8_t FB_ST_PASS = 0x5C;
inline constexpr uint8_t FB_ST_FAIL = 0x5E;
inline constexpr uint8_t FB_ST_FINISH = 0x5F;
// TELEMETRY
inline constexpr uint8_t FB_META_START = 0x7A;
inline constexpr uint8_t FB_META_REGDP = 0x70;
inline constexpr uint8_t FB_META_PARAM = 0x71;
    inline constexpr uint8_t META_PARAM_CLKCYC = 0x00;
    inline constexpr uint8_t META_PARAM_INSCNT = 0x01;
    inline constexpr uint8_t META_PARAM_STLCNT = 0x02;
    inline constexpr uint8_t META_PARAM_LSECNT = 0x03;
    inline constexpr uint8_t META_PARAM_BRFCNT = 0x04;
inline constexpr uint8_t FB_META_DISP = 0x7D;  // telemetry status display guard byte
inline constexpr uint8_t FB_REG_DISP = 0x75;  // GPR dump guard byte (sent before x1 and after x31)
inline constexpr uint8_t FB_META_FNSH = 0x7F;
// MEMORY
inline constexpr uint8_t FB_MEM_DUMP = 0x8A;
// CONNECTION
inline constexpr uint8_t FB_NET_SYNACK = 0xAB;
// PROGRAM RUNTIME
inline constexpr uint8_t FB_PRG_LOAD = 0xCA;
inline constexpr uint8_t FB_PRG_VERIFY = 0xCB;
inline constexpr uint8_t FB_PRG_RUN = 0xCC;
// DEVICE DATA
inline constexpr uint8_t FB_DD_DISP = 0xDA;
inline constexpr uint8_t FB_DD_PARAM = 0xD1;
    inline constexpr uint8_t DD_PARAM_BIOS = 0x00;
    inline constexpr uint8_t DD_PARAM_ARCH = 0x01;
    inline constexpr uint8_t DD_PARAM_REGCNT = 0x02;
    inline constexpr uint8_t DD_PARAM_CLKSPD = 0x03;
    inline constexpr uint8_t DD_PARAM_BAUDTK = 0x04;
    inline constexpr uint8_t DD_PARAM_RAMOFS = 0x05;
    inline constexpr uint8_t DD_PARAM_RAMSZ = 0x06;
    inline constexpr uint8_t DD_PARAM_PROGOFS = 0x07;
    inline constexpr uint8_t DD_PARAM_PROGSZ = 0x08;
    inline constexpr uint8_t DD_PARAM_ROMOFS = 0x09;
    inline constexpr uint8_t DD_PARAM_ROMSZ = 0x0A;
// BIOS STATE MONITORING
inline constexpr uint8_t FB_BIOSST_LOG = 0xFA;
    inline constexpr uint8_t BIOSST_LOG_OFF = 0x00;
    inline constexpr uint8_t BIOSST_LOG_ON = 0x01;
inline constexpr uint8_t FB_BIOSST_UPDT = 0xF0;
    inline constexpr uint8_t BIOSST_IDLE = 0x00;
    inline constexpr uint8_t BIOSST_MSG = 0x03;
    inline constexpr uint8_t BIOSST_ST = 0x05;
    inline constexpr uint8_t BIOSST_META = 0x07;
    inline constexpr uint8_t BIOSST_MEM = 0x08;
    inline constexpr uint8_t BIOSST_NET = 0x0A;
    inline constexpr uint8_t BIOSST_PGLD = 0x0C;
    inline constexpr uint8_t BIOSST_PGEX = 0x1C;
    inline constexpr uint8_t BIOSST_DD = 0x0D;
    inline constexpr uint8_t BIOSST_ERR = 0x0E;
    inline constexpr uint8_t BIOSST_LOG_ST = 0x0F;
    inline constexpr uint8_t BIOSST_STFIDL = 0x50;  // limited POST-fail idle state (connection only)

// BIOS ERRORS (INTERNAL AND EXTERNAL)
inline constexpr uint8_t ERR_MESSAGE = 0xE3;
    inline constexpr uint8_t ERR_GET_MSG_TOO_BIG = 0x01;
    inline constexpr uint8_t ERR_PUT_MSG_TOO_BIG = 0x02;
    inline constexpr uint8_t ERR_GET_MSG_UNVERIFIED = 0x03;
inline constexpr uint8_t ERR_SELF_TEST = 0xE5;
inline constexpr uint8_t ERR_TELEMETRY = 0xE7;
    inline constexpr uint8_t ERR_META_UNVERIFIED = 0x01;
    inline constexpr uint8_t ERR_META_PARAM_INVALID = 0x02;
    inline constexpr uint8_t ERR_META_ARG_INVALID = 0x03;
inline constexpr uint8_t ERR_MEMORY = 0xE8;
    inline constexpr uint8_t ERR_MEM_OUT_OF_BOUNDS = 0x01;
inline constexpr uint8_t ERR_CONNNECT = 0xEA;
    inline constexpr uint8_t ERR_CONNECTION_INVALID = 0x01;
    inline constexpr uint8_t ERR_CONNECTION_TIMEOUT = 0x02;
inline constexpr uint8_t ERR_PROGRAM = 0xEC;
    inline constexpr uint8_t ERR_PRG_UNVERIFIED = 0x01;
    inline constexpr uint8_t ERR_PRG_PARAM_INVALID = 0x02;
    inline constexpr uint8_t ERR_PRG_ARG_INVALID = 0x03;
    inline constexpr uint8_t ERR_PRG_TOO_BIG = 0x04;
inline constexpr uint8_t ERR_DEVICE_DATA = 0xED;
inline constexpr uint8_t ERR_CRITICAL = 0xEE;
inline constexpr uint8_t ERR_BIOS = 0xEF;
    inline constexpr uint8_t ERR_BIOS_TIMEOUT = 0x01;
    inline constexpr uint8_t ERR_BIOS_ARG_INVALID = 0x02;

} // namespace bios_protocol

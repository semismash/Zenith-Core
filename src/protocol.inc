# TO BIOS
# MESSAGES
.equ TB_MSG_ECHO,    0x3A
.equ TB_MSG_STR,     0x3D
# SELF TEST
.equ TB_ST_INIT,     0x5A
# TELEMETRY
.equ TB_META_START,  0x7A
.equ TB_META_BIOSTR, 0x70   # bios telemetry
.equ TB_META_PRGTR,  0x71   # program telemetry
.equ TB_META_PRGRST, 0x72   # program telemetry reset
.equ TB_META_RESET,  0x73   # instant reset
    .equ META_ARG_OFF,  0x00
    .equ META_ARG_ON,   0x01
# MEMORY
.equ TB_MEM_DUMP,    0x8A
# CONNECTION
.equ TB_NET_SYN,     0xAA
.equ TB_NET_ACK,     0xAC
# PROGRAM RUNTIME
.equ TB_PRG_LOAD,    0xCA
    .equ PRG_RUNNOW,    0xC0
    .equ PRG_VERIFY,    0xC1
    .equ PRG_OFFSET,    0xC2
    .equ PRG_T_MODE,    0xC3
    .equ PRG_T_RST,     0xC4
    .equ PRG_REGDISP,   0xC5
.equ TB_PRG_VERIFY,  0xCB   # different from the verify argument, this is for the actual command itself
.equ TB_PRG_RUN,     0xCC
# DEVICE DATA
.equ TB_DD_DATA,     0xDA
# BIOS DATA MONITORING
.equ TB_BIOS_DATA,   0xFA

# FROM BIOS
.equ FB_MSG_ECHO,    0x3A
.equ FB_MSG_STR,     0x3D
.equ FB_MSG_FLSH,    0x3F
# SELF TEST
.equ FB_ST_TESTBYTE, 0x50
.equ FB_ST_RESULTS,  0x5D
    .equ ST_PARAM_TEST_0,    0x00
    .equ ST_PARAM_TEST_1,    0x01
    .equ ST_PARAM_TEST_2,    0x02
    .equ ST_PARAM_TEST_3,    0x03
    .equ ST_PARAM_TEST_4,    0x04
    .equ ST_PARAM_TEST_5,    0x05
.equ FB_ST_PASS,     0x5C
.equ FB_ST_FAIL,     0x5E
.equ FB_ST_FINISH,   0x5F
# TELEMETRY
.equ FB_META_START,  0x7A
.equ FB_META_REGDP,  0x70
.equ FB_META_PARAM,  0x71
    .equ META_PARAM_CLKCYC,  0x00
    .equ META_PARAM_INSCNT,  0x01
    .equ META_PARAM_STLCNT,  0x02
    .equ META_PARAM_LSECNT,  0x03
    .equ META_PARAM_BRFCNT,  0x04
.equ FB_META_FNSH,   0x7F
# MEMORY
.equ FB_MEM_DUMP,    0x8A
# CONNECTION
.equ FB_NET_SYNACK,  0xAB
# PROGRAM RUNTIME
.equ FB_PRG_LOAD,    0xCA
.equ FB_PRG_VERIFY,  0xCB
.equ FB_PRG_RUN,     0xCC
# DEVICE DATA
.equ FB_DD_DISP,     0xDA
.equ FB_DD_PARAM,    0xD1
    .equ DD_PARAM_BIOS,      0x00
    .equ DD_PARAM_ARCH,      0x01
    .equ DD_PARAM_REGCNT,    0x02
    .equ DD_PARAM_CLKSPD,    0x03
    .equ DD_PARAM_BAUDTK,    0x04
    .equ DD_PARAM_RAMOFS,    0x05
    .equ DD_PARAM_RAMSZ,     0x06
    .equ DD_PARAM_PROGOFS,   0x07
    .equ DD_PARAM_PROGSZ,    0x08
    .equ DD_PARAM_ROMOFS,    0x09
    .equ DD_PARAM_ROMSZ,     0x0A
# BIOS STATE MONITORING
.equ FB_BIOSST_LOG,  0xFA
    .equ BIOSST_LOG_OFF, 0x00
    .equ BIOSST_LOG_ON,  0x01
.equ FB_BIOSST_UPDT, 0xF0
    .equ BIOSST_IDLE,    0x00
    .equ BIOSST_MSG,     0x03
    .equ BIOSST_ST,      0x05
    .equ BIOSST_META,    0x07
    .equ BIOSST_MEM,     0x08
    .equ BIOSST_NET,     0x0A
    .equ BIOSST_PGLD,    0x0C
    .equ BIOSST_PGEX,    0x1C
    .equ BIOSST_DD,      0x0D
    .equ BIOSST_ERR,     0x0E
    .equ BIOSST_LOG_ST,  0x0F

# BIOS ERRORS (INTERNAL AND EXTERNAL)
.equ ERR_MESSAGE,        0xE3
    .equ ERR_GET_MSG_TOO_BIG,       0x01
    .equ ERR_PUT_MSG_TOO_BIG,       0x02
    .equ ERR_GET_MSG_UNVERIFIED,    0x03
.equ ERR_SELF_TEST,      0xE5
.equ ERR_TELEMETRY,      0xE7
    .equ ERR_META_UNVERIFIED,       0x01
    .equ ERR_META_PARAM_INVALID,    0x02
    .equ ERR_META_ARG_INVALID,      0x03
.equ ERR_MEMORY,         0xE8
    .equ ERR_MEM_OUT_OF_BOUNDS,     0x01
.equ ERR_CONNNECT,       0xEA
    .equ ERR_CONNECTION_INVALID,    0x01
    .equ ERR_CONNECTION_TIMEOUT,    0x02
.equ ERR_PROGRAM,        0xEC
    .equ ERR_PRG_UNVERIFIED,        0x01
    .equ ERR_PRG_PARAM_INVALID,     0x02
    .equ ERR_PRG_ARG_INVALID,       0x03
    .equ ERR_PRG_TOO_BIG,           0x04
.equ ERR_DEVICE_DATA,    0xED
.equ ERR_CRITICAL,       0xEE   
.equ ERR_BIOS,           0xEF
    .equ ERR_BIOS_TIMEOUT,          0x01
    .equ ERR_BIOS_ARG_INVALID,      0x02

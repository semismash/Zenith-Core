# BIOS specific constant declarations
.equ CPU_CLOCK_HZ,      10000000                    # core clock, the timeouts and the H3 cooldown are derived from it (same value as dd_clk)
.equ UART_BAUD_RATE,    9600                        # UART baud rate, used to size the cooldown window in byte-times (same value as dd_baud)
.equ UART_POLL_CYCLES,  10                          # PLACEHOLDER (review later): clock cycles one pass of the uart_rx wait loop takes; measure in sim and adjust
.equ DEFAULT_TIMEOUT_CYCLE, (0x4000000 / UART_POLL_CYCLES) # uart_rx counts loop passes, not cycles, so divide the cycle budget by cycles-per-pass # 67 million cycle safety window (6.7s at 10MHz)
.equ UART_STATUS,       0x80000000                  # 0x8000_0000
.equ UART_RXD_OFFSET,   0x4                         # 0x8000_0004
.equ UART_TXD_OFFSET,   0x8                         # 0x8000_0008
.equ PROGRAM_START,     0x2000                      # RAM/program space now starts after the 8 KiB ROM # program entry point
.equ RAM_SIZE,          0x20000                     # 128 KiB RAM (matches size of RAM)
.equ PROGRAM_TOP,       0x21000                     # changed to 0x20000 # program top address, everything above that is reserved by BIOS
.equ RAM_TOP,           PROGRAM_START + RAM_SIZE    # 0x22000 # PROGRAM_START + RAM_SIZE, top of stack grows down from here, (0x21000)

.equ ROM_START,         0x0
.equ ROM_SIZE,          0x2000                      # 8 KiB ROM (was 0x1000)

# Telemetry
.equ ADDR_META_CONTROL,     0x80001000
.equ ADDR_META_CONTROL_RD,  0x80001001              # read only mirror of above quantity
.equ ADDR_META_INSTR,       0x80001004
.equ ADDR_META_STALL,       0x80001008
.equ ADDR_META_L_USE,       0x8000100C
.equ ADDR_META_BR_FLUSH,    0x80001010

.equ BIOS_STACK_SIZE,   64                          # 64 bytes allocated for BIOS
.equ CONNECTION_TIMEOUT_CYCLES, (0x8F00000 / UART_POLL_CYCLES) # connection_timeout form
.equ MSG_ECHO_BUF,      0x21800                     # was 0x20800 # dedicated 256-byte destination buffer for msg_echo's gets() call, separate from the PROGRAM_TOP+0x0-0xF register-save scratch
.equ REG_DUMP_BUF,      0x21900                     # was 0x20900 # 124-byte (31 word) scratch buffer for jump_back_reg_disp's x1-x31 dump, placed right after MSG_ECHO_BUF
.equ MSG_ECHO_BUF_SIZE, 256                         # size of MSG_ECHO_BUF, gets() rejects anything longer
.equ DRAIN_QUIET_BYTES, 5                           # cooldown after an error: RX must stay quiet this many byte-times
.equ DRAIN_QUIET_ITER,  ((DRAIN_QUIET_BYTES * 10 * (CPU_CLOCK_HZ / UART_BAUD_RATE)) / UART_POLL_CYCLES) # same window in loop passes (10 bits per byte)
.equ PRG_TAIL_BYTES,    8                           # every loaded program gets a 2-word lui+jalr jump-back tail
.equ PRG_VALID_BIT,     0x00002000                  # Ns10 bit 13: valid program load

.include "protocol.inc"     # <---- all da protocol codez in here :3

# <-------- DISCLAIMER: Most of this code is human written. However, certain final-stage parts of the code were written and debugged using AI. All debugged code was thoroughly human reviewed. ---------->

# REGISTER USAGE:
# a0 - callee return value 1
# a1 - callee return value 2
# a0-a7 - function arguments
    # a4 - UART timeout custom
    # a5 - Timeout handler (0 = default, 1 = connection)
    # a6 - BIOS state update
    # a7 - UART idle indicator (if uart not receiving anything since its in idle state or not or not)
# t0-t6 - temporary function-specific variables
    # t6 - Reserved as the link register for the rx/tx macros (uart_rx/uart_tx), don't rely on it surviving a rx/tx call
# s0-s11 - global/high-lifetime variables
    # s1 - UART status (RX_DATA/TX_DATA are now addressed as fixed offsets from this, see uart_rx/uart_tx)
    # NOTE: s2 and s3 removed - previously used for rx and tx functions but no longer required
    # s2 / s3 - program_load candidate offset / size, only copied into s11 / s9 once a load fully completes
    # s9 - Loaded Program Size
    # s10 - BIOS Status Register
        # [7:0]: BIOS Status Byte
        # [8]: BIOS Connection Valid
        # [9]: BIOS Status Flush (State logging)
        # [10]: BIOS Telemetry Enable
        # [11]: Program Telemetry Enable
        # [12]: Program Telemetry Reset
        # [13]: Valid Program Load (set only by a fully completed program_load; cleared on reset, at the start of a load's data phase, and by a self test)
        # vvv These bits are not automatically reset upon forced reset
        # [16]: Prior Connection (first time connecting, or has been connected before)
        # [17]: Self Test Passed
        # [18-23]: Tests pass bitmask
    # s11 - Program Start Offset

# MEMORY LAYOUT:
# 8 KiB ROM # 0x00000000 - 0x00000FFF: BIOS ROM
# 0x00001000 - 0x0001FFFF: PROGRAM SPACE (PROGRAM STACK DEFAULT: 0x00020000)
# 0x00020000 - 0x00020FBF: BIOS DATA SPACE
# 0x00020FC0 - 0x00021000: BIOS STACK (allocate 64 bytes (16 words) space for BIOS stack)

# write and then verify x1-x31 (used by self-test)
.macro test_reg reg, idx
    li      \reg, ((\idx << 6) | \idx)
.endm

.macro check_reg reg, idx
    li      t6, ((\idx << 6) | \idx)      # t6 as a scratch reg, checked seperately later on
    bne     \reg, t6, selftest_reg_fail
.endm

# art_rx/uart_tx are now entered through these two macros instead of `call`
# t6 is used as a dedicated link register here (and throughout the program in general
# as uart_rx and uart_tx are leaf funcitons, programs can safely call it witout pushing to stack first, temporarily saving in t6
.macro rx
    jal     t6, uart_rx
.endm
.macro tx
    jal     t6, uart_tx
.endm

# replaced push_addr and pop_addr w/ fn_enter and fn_leave
# prevents the inner call from overwrting ra, which the callee function needs to return to its caller
# generally only ever reached by a branch from idle dispatch table, so no ra of its own to protect, hence just jumps back to idle/update when done
.macro fn_enter
    addi    sp, sp, -4
    sw      ra, 0(sp)
.endm
.macro fn_leave
    lw      ra, 0(sp)
    addi    sp, sp, 4
    ret
.endm

.global _start

.section .rodata
.align 2

# BIOS Messages
bios_start_msg_len: # length of below string + 0x00 for null term
    .word   26
bios_start_msg:
    .string "BIOS Loaded Successfully!"
    .align  2       # make sure to align correctly to 2 byte boundaries so program_start can utilize it correctly

# Memory Layouts
program_start:      # 0x2000
    .word   PROGRAM_START
ram_size:           # 0x20000
    .word   RAM_SIZE
ram_top:            # 0x22000
    .word   RAM_TOP
program_top:        # 0x21000
    .word   PROGRAM_TOP
program_size:
    .word   PROGRAM_TOP - PROGRAM_START
bios_stack_top:     # 0x22000
    .word   RAM_TOP
program_stack_top:  # 0x21000
    .word   PROGRAM_TOP
bios_data_top:      # 0x21FC0
    .word   RAM_TOP - BIOS_STACK_SIZE
bios_mem_size:
    .word   RAM_TOP - BIOS_STACK_SIZE - PROGRAM_TOP

# Device Data
dd_name_len:
    .word   23
dd_name:    # device bios name
    .string "Zenith Core BIOS v.1.0"
    .align  2
dd_arch_len:
    .word   24
dd_arch:    # device arch
    .string "RISC-V | RV32I | 32-bit"
    .align  2
dd_regc:    # GPR count
    .word   32
dd_clk:     # configured clock speed
    .word   10000000    # MHz
dd_baud:    # configured UART baud tick rate
    .word   9600        # MHz

# Other
connection_timeout:
    .word   0x8F00000   # ~150 million cycles (~15 seconds delayed @ 10MHz)

.section .text

_start:

    addi    s8, x0, 0   # clear s8 register (upon boot)

self_test:  # cpu starts over here, with POST, also comes over here if triggered manually cia CLI

# Test 1: Registers
selftest_regs:

    # 1: write unique pattern in each register
    test_reg x1,  1
    test_reg x2,  2
    test_reg x3,  3
    test_reg x4,  4
    test_reg x5,  5
    test_reg x6,  6
    test_reg x7,  7
    test_reg x8,  8
    test_reg x9,  9
    test_reg x10, 10
    test_reg x11, 11
    test_reg x12, 12
    test_reg x13, 13
    test_reg x14, 14
    test_reg x15, 15
    # test first 14 regs (i'm doing this cuz we are using s8 (x24) as our self-test status register)
    check_reg x1,  1
    check_reg x2,  2
    check_reg x3,  3
    check_reg x4,  4
    check_reg x5,  5
    check_reg x6,  6
    check_reg x7,  7
    check_reg x8,  8
    check_reg x9,  9
    check_reg x10, 10
    check_reg x11, 11
    check_reg x12, 12
    check_reg x13, 13
    check_reg x14, 14
    check_reg x15, 15

    mv      x1, s8      # temporarily move s8 into x1 to prevent overwriting by the upcoming test

    # check next 15 regs (x16-x30)
    test_reg x16, 16
    test_reg x17, 17
    test_reg x18, 18
    test_reg x19, 19
    test_reg x20, 20
    test_reg x21, 21
    test_reg x22, 22
    test_reg x23, 23
    test_reg x24, 24
    test_reg x25, 25
    test_reg x26, 26
    test_reg x27, 27
    test_reg x28, 28
    test_reg x29, 29
    test_reg x30, 30

    mv      t1, x24         # save x24 (s8) current pattern before restoring below
    mv      s8, x1          # move back into x1 (thank you, x1! :D)

    # check remaining 15 regs
    check_reg x16, 16
    check_reg x17, 17
    check_reg x18, 18
    check_reg x19, 19
    check_reg x20, 20
    check_reg x21, 21
    check_reg x22, 22
    check_reg x23, 23
    li      t6, ((24 << 6) | 24)   # check x24 saved pattern in t1 instead of x24 itself (since we moved s8 into t1 earlier)
    bne     t1, t6, selftest_reg_fail
    check_reg x25, 25
    check_reg x26, 26
    check_reg x27, 27
    check_reg x28, 28
    check_reg x29, 29
    check_reg x30, 30

    # test t6 register using x30 (already verified)
    li      x31, ((31 << 6) | 31)
    li      x30, ((31 << 6) | 31)
    bne     x31, x30, selftest_reg_fail

    # check if x0 is hardwired to zero
    add     x30, x0, x0
    bnez    x30, selftest_reg_fail

    # s8 will be the status register to keep track of the number of passed tests from now on
    # byte 0 = bitmask keeping track of passed tests; byte 1 = number of passed tests
    ori     s8, s8, 0x01        # pass   (set bit 1)
    addi    s8, s8, 0x100       # increase the counter in byte 1

selftest_reg_fail:

    # tests will be done sequentially, and a fail in one test will cause a fail in the entire self test, with each bit tracking the failed tests
    # (corresponding bit corresponding to that test)

# Test 2: ALU Operations
selftest_alu:
    # add / sub
    li      t0, 5
    li      t1, 3
    add     t2, t0, t1
    li      t3, 8
    bne     t2, t3, selftest_alu_fail

    li      t0, 0x7FFFFFFF
    li      t1, 1
    add     t2, t0, t1
    li      t3, 0x80000000
    bne     t2, t3, selftest_alu_fail

    # and / or / xor
    li      t0, 0xF0F0F0F0
    li      t1, 0x0F0F0F0F
    and     t2, t0, t1
    bnez    t2, selftest_alu_fail          # F0F0F0F0 & 0F0F0F0F = 0

    or      t2, t0, t1
    li      t3, 0xFFFFFFFF
    bne     t2, t3, selftest_alu_fail

    xor     t2, t0, t1
    bne     t2, t3, selftest_alu_fail      # same bits, no overlap -> all 1s

    # shifts: 0x80000001 exercises both bit 31 and bit 0
    li      t0, 0x80000001
    srli    t2, t0, 4
    li      t3, 0x08000000
    bne     t2, t3, selftest_alu_fail      # logical: zero-fill from top

    srai    t2, t0, 4
    li      t3, 0xF8000000
    bne     t2, t3, selftest_alu_fail      # arithmetic: sign-extend from top

    slli    t2, t0, 4
    li      t3, 0x00000010
    bne     t2, t3, selftest_alu_fail

    # slt / sltu
    li      t0, -1          # 0xFFFFFFFF
    li      t1, 1
    slt     t2, t0, t1
    li      t3, 1
    bne     t2, t3, selftest_alu_fail      # signed: -1 < 1 -> true

    sltu    t2, t0, t1
    bnez    t2, selftest_alu_fail          # unsigned: 0xFFFFFFFF < 1 -> false

    ori     s8, s8, 0x02        # pass   (set bit 1)
    addi    s8, s8, 0x100       # increase the counter in byte 1

selftest_alu_fail:

# TEST 3: CONTROL FLOW
selftest_ctrl:
    # beq taken / not-taken
    li      t0, 5
    li      t1, 5
    li      t3, 0
    beq     t0, t1, 1f
    j       selftest_ctrl_fail
1:  li      t3, 1
    li      t4, 1
    bne     t3, t4, selftest_ctrl_fail

    li      t0, 5
    li      t1, 6
    li      t3, 0
    beq     t0, t1, selftest_ctrl_fail      # should NOT be taken
    li      t3, 1
    li      t4, 1
    bne     t3, t4, selftest_ctrl_fail

    # blt / bge
    li      t0, 3
    li      t1, 7
    blt     t0, t1, 2f
    j       selftest_ctrl_fail
2:  li      t0, 7
    li      t1, 3
    blt     t0, t1, selftest_ctrl_fail      # should NOT be taken
    bge     t0, t1, 3f
    j       selftest_ctrl_fail
3:

    # jal: verify link register holds correct return address
    jal     ra, selftest_jal_target
    j       selftest_jal_check
selftest_jal_target:
    jr      ra
selftest_jal_check:

    # jalr: verify via register-held target
    la      t0, selftest_jalr_target
    jalr    ra, t0, 0
    j       selftest_ctrl_pass
selftest_jalr_target:
    jr      ra

selftest_ctrl_pass:
    ori     s8, s8, 0x04        # pass (set bit 2)
    addi    s8, s8, 0x100       # increase the counter in byte 1

selftest_ctrl_fail:

# TEST 4: MEMORY
# PROGRAM_START, +0x7000, +0xF000 and PROGRAM_TOP - 4, derived from the constants # addresses spanning program space: 0x1000, 0x8000, 0x10000, 0x1FFFC (word-aligned top)
selftest_mem:
    li      t0, PROGRAM_START
    li      t1, 0xA1A1A1A1
    sw      t1, 0(t0)
    lw      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    li      t0, PROGRAM_START + 0x7000
    li      t1, 0xB2B2B2B2
    sw      t1, 0(t0)
    lw      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    li      t0, PROGRAM_START + 0xF000
    li      t1, 0xC3C3C3C3
    sw      t1, 0(t0)
    lw      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    li      t0, PROGRAM_TOP - 4    # last word of program space
    li      t1, 0xD4D4D4D4
    sw      t1, 0(t0)
    lw      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    # byte access
    li      t0, PROGRAM_START
    li      t1, 0x5A
    sb      t1, 0(t0)
    lb      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    # halfword access
    li      t0, PROGRAM_START + 4
    li      t1, 0x1234
    sh      t1, 0(t0)
    lh      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    ori     s8, s8, 0x08        # pass (set bit 3)
    addi    s8, s8, 0x100       # increase the counter in byte 1

selftest_mem_fail:

# TEST 5: STACK
selftest_sp:
    li      sp, RAM_TOP         # BIOS stack top (per memory layout)

    li      t0, 0x11111111
    li      t1, 0x22222222
    li      t2, 0x33333333

    addi    sp, sp, -4
    sw      t0, 0(sp)
    addi    sp, sp, -4
    sw      t1, 0(sp)
    addi    sp, sp, -4
    sw      t2, 0(sp)

    lw      t3, 0(sp)
    bne     t3, t2, selftest_sp_fail
    addi    sp, sp, 4

    lw      t3, 0(sp)
    bne     t3, t1, selftest_sp_fail
    addi    sp, sp, 4

    lw      t3, 0(sp)
    bne     t3, t0, selftest_sp_fail
    addi    sp, sp, 4

    li      t4, RAM_TOP
    bne     sp, t4, selftest_sp_fail   # sp should be back where it started

    ori     s8, s8, 0x10        # pass (set bit 4)
    addi    s8, s8, 0x100       # increase the counter in byte 1

selftest_sp_fail:

# 6: UART test
selftest_uart:
    la      s1, UART_STATUS         
    li      a0, FB_ST_TESTBYTE  # arbitrary known test byte
    tx                          
    
    ori     s8, s8, 0x20        # pass (set bit 5)
    addi    s8, s8, 0x100       # increase the counter in byte 1

st_evaluate:
    li      t5, 0               
    andi    t0, s8, 0xFF        # mask out lowest byte to get bitmask of passed and failed tests
    li      t1, 0x0000FF00      # get number of passed tests by masking byte 1
    and     t1, s8, t1
    srli    t1, t1, 8
    li      t2, 0x00FF0000      # get whether test was POST or requested by master device by masking byte 2
    and     t2, s8, t2
    srli    t2, t2, 16

    addi    t3, t1, -6          # check if equal to 6 tests or not
    snez    t3, t3              # set as one if all tests passed, else set as zero
    li      t4, 0x00020000      # mask bit 17
    bnez    t3, 1f              
    or      t5, t5, t4          # update t5 (here t5 maps to the upper bits of s10, to be shifted later) bit 17 (self test passed) to true     
    j       2f
1:
    xori    t4, t4, -1
    and     t5, t5, t4          # update t5 bit 17 (self test failed) to false
2:
    slli    t4, t0, 18          # set 0-5 bits of bitmask in t0 to corresponding 18-23 bits in t5 register
    lui     t3, 0xFC0           
    and     t4, t4, t3
    xori    t3, t3, -1
    and     t5, t5, t3
    or      t5, t5, t4

    mv      s5, t0              # move bitmask into s5 register to survive function branch
    mv      s6, t5              # move t5 status register into s6 (only contains upper bits)
    bnez    t2, req_self_test_res       # go back to req self test if the indicator bit was high (i am high) 

    mv      s10, t5             # update s10 to t5 (we can do this because it means it is a POST initialization, since it didnt take prev branch)

reset:
    # initialize BIOS constants (UART mainly)
    la      s1, UART_STATUS         # s1 - UART STATUS
    addi    s9, x0, 0               # s9 - Program size register
    li      t1, 0xFFFF0000              
    and     s10, s10, t1                
    addi    s11, x0, 0              # s11 - Program offset register

    li      sp, RAM_TOP             # la loaded the ADDRESS of the bios_stack_top word, not its value # initialize stack
    addi    a4, x0, 0               # clear a4 register to prevent interference with UART rx timer (see uart_rx: label below)

    li      t0, 0x00020000          # mask for self-test-pass bit (17), andi can't take an immediate this large, build the mask with li + and instead
    and     t0, s10, t0             # check self-test-passed bit POST failures must drop into the limited connection-only idle state
    beqz    t0, st_fail_idle

update:
    call    sync_bios_telemetry     # sync hardware meta_enable to BIOS's own telemetry setting before idling

idle:
    li      sp, RAM_TOP             # re-heal stack every time BIOS returns to idle
    li      a4, 0                   # a4/a5 were only cleared after a successful rx; a program returning with e.g. a4 = 1 made the BIOS deaf
    li      a5, 0                   # default timeout handler
    li      a6, BIOSST_IDLE         
    call    update_state            # update state to idle
1:
    addi    a7, x0, 1               # load as idle = 1 so uart_rx doesn't transmit timeout error upon timeout
    rx                              # call uart rx in idle to receive command
    mv      t0, a0                  # move result to t0 scratch reg
    addi    a7, x0, 0               # reset back to normal if byte received
    
    # conditional switch table for all different intiialization bytes
    li      t1, TB_PRG_RUN          # program run
    beq     t0, t1, program_run
    li      t1, TB_MSG_ECHO         # check msg echo byte
    beq     t0, t1, msg_echo
    li      t1, TB_ST_INIT          # check self test init
    beq     t0, t1, req_self_test
    li      t1, TB_META_START       # check telemetry display innit
    beq     t0, t1, telemetry
    li      t1, TB_META_DISP        # check telemetry status display request
    beq     t0, t1, telemetry_status
    li      t1, TB_MEM_DUMP         # memory dump
    beq     t0, t1, memdump         
    li      t1, TB_NET_SYN          # connection attempt
    beq     t0, t1, connect
    li      t1, TB_PRG_LOAD         # program load
    beq     t0, t1, program_load
    li      t1, TB_PRG_VERIFY       # program verification
    beq     t0, t1, program_verify
    li      t1, TB_DD_DATA          # check device data request
    beq     t0, t1, device_data
    li      t1, TB_BIOS_DATA        # check if BIOS data monitoring is turned on
    beq     t0, t1, bios_log

    li      a0, ERR_BIOS            # unknown command byte -> EF 03
    li      a1, ERR_BIOS_INV_CMD
    j       error_handler

# BIOS UTILITY

msg_echo:
    li      a6, BIOSST_MSG
    call    update_state        # update state  
    
    li      a1, MSG_ECHO_BUF    # destination buffer address to store string
    call    gets                # get input string of byte size a long with size
    mv      s7, a0          

    li      a0, FB_MSG_ECHO     # send transmission byte starting message display attempt
    tx 

    mv      a0, s7
    call    puts                # print string via uart using puts

    li      a0, FB_MSG_FLSH
    tx                          # transmit flush message towards the en
    
    j       idle            

req_self_test:
    li      a6, BIOSST_ST       # was BIOSST_MSG (logged 0x03 instead of 0x05)
    call    update_state        # update state

    # move existing BIOS status registers into known BIOS memory locations unaffected by registers
    li      t0, PROGRAM_TOP
    sw      s9, 4(t0)  
    sw      s10, 8(t0)
    sw      s11, 12(t0)

    li      s8, 0x00010000  # byte 2 = 0x01 lets the BIOS know that its a requested re-self test and not a regular one
    j       self_test

req_self_test_res:
    li      t0, PROGRAM_TOP
    lw      s9, 4(t0)  
    lw      s10, 8(t0)
    lw      s11, 12(t0)

    li      s1, UART_STATUS

    li      t0, 0x00FF0000              # update s10 bits 16-23 to the new values of 16-23 (achived from s5 bitmask we stored)
    and     t0, s6, t0      
    li      t1, 0xFF00DFFF              # clear bit 13, the memory test overwrites program space, so any loaded program is no longer valid
    and     s10, s10, t1
    or      s10, s10, t0

    call    display_self_test_results   # display logic moved into a shared, callable routine (also used by connect for the first reconnect after a self test)
    j       idle_or_stfail              # a failed requested self test now drops into the limited st_fail_idle (pass -> normal idle, M8)

display_self_test_results:              # shared self-test results display (startup banner + pass/fail + per-test results); reads live from s10 bits 16-23 so it's valid for any caller, not just right after st_evaluate
    fn_enter                            # protect ra, since this calls puts internally

    la      t0, bios_start_msg_len      # load string length into register from memory
    lw      a0, 0(t0)               
    la      a1, bios_start_msg          # load offset pointer
    call    puts                        # print the BIOS startup banner
    li      a0, FB_MSG_FLSH             # explicit flush byte to close the startup message framing
    tx                              

    li      t0, 0x00020000              # mask for the self-test-passed bit; andi can't take an immediate this large
    and     t0, s10, t0                 # self-test-passed bit (17), read straight from s10 instead of the local st_evaluate bitmask
    beqz    t0, 1f
    li      a0, FB_ST_PASS
    tx
    j       2f
1:
    li      a0, FB_ST_FAIL
    tx
2:
    srli    t0, s10, 18            # per-test bitmask now comes from s10 bits 18-23 (shifted down), rather than s5, which isn't valid once called later from connect
    andi    t0, t0, 0x3F           # keep only the 6 test bits
    li      t2, ST_PARAM_TEST_0
    li      t3, 6           # loop count (6 for 6 tests)
    li      t4, 0           # loop counter

    li      a0, FB_ST_RESULTS
    tx
3:
    mv      a0, t2          
    tx
    srl     t1, t0, t4      # shift the mask to the right each time, to go through test cases
    andi    t1, t1, 1       # get first bit only after shifting
    snez    a0, t1          # set to pass or fail
    tx
    addi    t2, t2, 1       # shift testcase number first
    addi    t4, t4, 1       # increment loop counter
    bne     t3, t4, 3b      # go back to loop as long as loop counter doesnt hit 6 yet (t3)

    li      a0, FB_ST_FINISH
    tx

    fn_leave                # return to caller (req_self_test_res or connect)

telemetry:  # while writing this function, one half of me was sleepy and the other half of me was depressed, pls don't judge
    li      a6, BIOSST_META
    call    update_state    # update state

    li      t4, 4           # for four possible arguments (bios tele, prog tele, inst telereset, prog telereset)
    li      t3, 0           # set to 1 once a 0x73 reset is seen, so `7A 73 7A` is not treated as a bare `7A 7A` display request
1:  
    rx                      # get byte
    li      t0, TB_META_START
    beq     a0, t0, 12f     # jump if start i.e. stop byte is received (same byte again for verification)
    beqz    t4, 13f         # jump to error if args left = zero (safety bound, incase stop byte is not received again)

    li      t0, TB_META_BIOSTR
    beq     a0, t0, 3f      # BIOS telemetry tracking
    li      t0, TB_META_PRGTR
    beq     a0, t0, 4f      # program telemetry tracking
    li      t0, TB_META_PRGRST
    beq     a0, t0, 5f      # program telemetry reset
    li      t0, TB_META_RESET
    beq     a0, t0, 7f      # instant reset telemetry now
    j       2f              # invalid param
3:
    li      t1, 10          # 10 is s10 bit number for option bios telemetry tarcking
    j       6f
4:
    li      t1, 11          # 11 is s10 bit number for option program telemetry tarcking
    j       6f
5:
    li      t1, 12          # 12 is s10 bit number for option program telemetry reset
    j       6f
6:
    li      t0, 1
    sll     t0, t0, t1      # shift the '1' to the amount set by the previous label to mask said bit
    rx                      # receive argument byte
    li      t2, META_ARG_ON
    beq     a0, t2, 8f      # if ON
    li      t2, META_ARG_OFF
    beq     a0, t2, 9f      # if OFF
    # ^^ the above on and off branch logic will likely be merged with slt insturctions in the future to remove jump overhead
    
    j       10f
8:
    or      s10, s10, t0    # set respective bit in s10 using mask
    j       11f     
9:
    xori    t0, t0, -1      # invert bitmask
    and     s10, s10, t0    # reset respective bit in s10 using mask
11:
    addi    t4, t4, -1      # reduce count per arg
    j       1b
7:
    li      t3, 1           # this command contained a parameter (0x73), it is not a display request
    # META_CONTROL is write-only in hardware, so this reads back through the ADDR_META_CONTROL_RD mirror
    # port (temporary fix, see mmio_interface.sv), while still writing to the normal ADDR_META_CONTROL
    # address. Two separate addresses: t0 = write, t1 = read.
    li      t0, ADDR_META_CONTROL      # meta control byte address (write)
    li      t1, ADDR_META_CONTROL_RD   # meta control byte address (read mirror)
    lbu     t2, 0(t1)               # get current meta control status
    nop                             # load use stall
    ori     t2, t2, 0x01            # LSB is reset, assert high
    sb      t2, 0(t0)               # store it
    andi    t2, t2, 0xFE            # one's complement to reset that bit
    sb      t2, 0(t0)               # store status with reset bit to finish reset assertion
    
    j       1b                      # loop back for next argument
12:
    bnez    t3, 14f                 # 0x73 was sent: just apply, no settings reply
    addi    t1, t4, -4              # if arguments left was still 4 (immediately guard byte was send, meaning that user requested display of current telemetry settings)
    bnez    t1, 14f

    li   a0, 0x70                   # bit 10
    tx
    
    li      t1, 0x00000400          # mask bit 10
    and     a0, s10, t1
    snez a0, a0                     # set a0 to 1 if bit is on, 0 if off
    tx

    li   a0, 0x71                   # bit 11
    tx
    
    li      t1, 0x00000800          # mask bit 11
    and     a0, s10, t1
    snez a0, a0                     # set a0 to 1 if bit is on, 0 if off
    tx

    li   a0, 0x72                   # bit 12
    tx
    
    li      t1, 0x00001000          # mask bit 12
    and     a0, s10, t1
    snez a0, a0                     # set a0 to 1 if bit is on, 0 if off
    tx
  
    j       idle
14:
    j       update                  # update new settings properly
2:
    li      a0, ERR_TELEMETRY
    li      a1, ERR_META_PARAM_INVALID
    j       error_handler
10:
    li      a0, ERR_TELEMETRY
    li      a1, ERR_META_ARG_INVALID
    j       error_handler
13: 
    li      a0, ERR_TELEMETRY
    li      a1, ERR_META_UNVERIFIED
    j       error_handler           # holy shit it's exactly 100 lines long :o (well almost, got changed after debugging :/)

telemetry_status:    # implements the `status --telemetry` display; replies with each live counter value read straight from its MMIO address
    li      a6, BIOSST_META         # reuse the telemetry display state code
    call    update_state            # update state
    li      t0, ADDR_META_CONTROL   # freeze the counters (w/ enable=0) so all four values below come from the same instant
    sb      zero, 0(t0)

    li      a0, FB_META_DISP        # opening guard byte
    tx

    li      a0, META_PARAM_INSCNT   # instruction count
    tx
    li      t0, ADDR_META_INSTR
    lw      a0, 0(t0)
    call    send_word

    li      a0, META_PARAM_STLCNT   # stall count
    tx
    li      t0, ADDR_META_STALL
    lw      a0, 0(t0)
    call    send_word

    li      a0, META_PARAM_LSECNT   # load-use stall count
    tx
    li      t0, ADDR_META_L_USE
    lw      a0, 0(t0)
    call    send_word

    li      a0, META_PARAM_BRFCNT   # branch-flush count
    tx
    li      t0, ADDR_META_BR_FLUSH
    lw      a0, 0(t0)
    call    send_word

    li      a0, FB_META_DISP        # closing guard byte
    tx
    call    sync_bios_telemetry     # unfreeze, restore meta_enable from s10 bit 10
    j       idle                    # return to idle

memdump:
    li      a6, BIOSST_MEM
    call    update_state    # update state

    call    get_word        # get size word
    mv      s7, a0          # save size in s7 register to save function call

    call    get_word        # get offset word
    mv      a1, a0          # move offset to a1 to argument for next func
    mv      a0, s7          # restore size to a0 for argument

    call    mem_print       # call mem diplay function (a0 = size, a1 = offset)

    j       idle

connect:
    li      a6, BIOSST_NET
    call    update_state                # update state

    li      a0, FB_NET_SYNACK           # send back SYN-ACK byte to verify connection
    tx                          
    li      a4, CONNECTION_TIMEOUT_CYCLES
    li      a5, 1
    rx                                  # verify ACK byte
    li      t0, TB_NET_ACK
    bne     a0, t0, 1f                  # if ACK is verified, connect successfully and update status, otherwise, jump to error_handler
    ori     s10, s10, 0x00000100        # set connection bit to 1

    li      t0, 0x00010000              # mask for the prior-connection bit; andi can't take an immediate this large
    and     t0, s10, t0                 # check prior-connection bit (16), if set, results were already shown since the last self test
    bnez    t0, 2f                      # skip the startup display if already shown
    call    display_self_test_results   # show BIOS startup message + pass/fail + per-test results once per new self test
    li      t0, 0x00010000              # mark prior-connection bit, so it won't repeat until the next self test
    or      s10, s10, t0                
2:
    j       idle_or_stfail              # resume full idle if the last self test passed, else stay in the limited POST-fail idle
1:
    li      t0, 0xFFFFFEFF           
    and     s10, s10, t0                # set connection bit (8th bit) to 0
    li      a0, ERR_CONNNECT
    li      a1, ERR_CONNECTION_INVALID
    j       error_handler

program_load:   # here, the s4 register is used like a temporary status register for this function or some shit idk
    # s4 status register = [4 (reg disp), 3 (telereset), 2 (telemode), 1 (verify), 0 (run)]
    li      a6, BIOSST_PGLD     
    call    update_state        # update state

    li      s4, 0               
    li      s2, PROGRAM_START   # default program start offset into s11 program offset register; candidate offset in s2; s11 is only updated once the load fully completes 
    li      t4, 6               # 6 possible arguments (run, verify, offset, telemetry mode, telemetry reset, register display)
1:  
    li      t0, TB_PRG_LOAD     # if arguments loaded... or not (recheck using the same verification byte again)
    rx                          
    beq     a0, t0, 2f
    beqz    t4, 11f             # jump to error (arguments exhausted, no verification guard byte received)

    li      t0, PRG_RUNNOW      # parameter = run after load
    beq     a0, t0, 3f
    li      t0, PRG_VERIFY      # parameter = verify after load
    beq     a0, t0, 4f
    li      t0, PRG_OFFSET      # parameter = offset
    beq     a0, t0, 5f
    li      t0, PRG_T_MODE      # parameter = telemetry mode
    beq     a0, t0, 6f
    li      t0, PRG_T_RST       # parameter = telemetry reset
    beq     a0, t0, 7f
    li      t0, PRG_REGDISP     # parameter = register display after program completion
    beq     a0, t0, 8f

    j       9f                  # unrecognized parameter
3:
    ori     s4, s4, 0x01        # set bit zero (run)
    j       15f
4:
    ori     s4, s4, 0x02        # set bit one (verify)
    j       15f
5:
    mv      s5, t4              # technically not required as get_word never uses t4, probably will remove it later on
    call    get_word
    mv      t4, s5
    mv      s2, a0              # move program load offset into offset register (s11 is the program offset register, programs are loaded and run here); candidate offset, committed to s11 at the end
    j       15f
6:
    li      t1, 2               # bit two (telemetry mode) -> utilizes shifting (see label 12 below)
    j       12f
7:
    li      t1, 3               # bit three (telemetry reset)
    j       12f
8:
    li      t1, 4               # bit four (register display)
    j       12f
12:
    li      t0, 1
    sll     t0, t0, t1          # shift 1 the respective value to the left
    rx                          # uart_rx -> rx macro
    li      t2, 0
    beq     a0, t2, 13f         # if FALSE (0x00)
    li      t2, 1
    beq     a0, t2, 14f         # if TRUE (0x01)
    j       10f                 # invalid argument otherwise
13:
    xori    t0, t0, -1
    and     s4, s4, t0          # reset the corresponding bit
    j       15f
14:
    or      s4, s4, t0          # TRUE must set the bit
15:
    addi    t4, t4, -1          # decrement count
    j       1b                  # go back in tloop

2:
    call    get_word            # program get size
    
    mv      s3, a0                      # candidate size in s3, committed to s9 at the end
    li      t0, PROGRAM_START           # dedicated program-space check, all compares unsigned so nothing can wrap
    bltu    s2, t0, 9f                  # offset below program space -> EC 02
    li      t0, PROGRAM_TOP             
    bgeu    s2, t0, 9f                  # offset at/above PROGRAM_TOP -> EC 02
    andi    t1, s2, 0x3                 
    bnez    t1, 25f                     # unaligned offset -> EC 05
    beqz    s3, 9f                      # zero size -> EC 02
    andi    t1, s3, 0x3                 
    bnez    t1, 26f                     # unaligned size -> EC 06
    sub     t1, t0, s2                  # room = PROGRAM_TOP - offset (> 0 here)
    li      t2, PRG_TAIL_BYTES          
    bltu    t1, t2, 17f                 # not even room for the 8-byte tail -> EC 04
    sub     t1, t1, t2                  # room left for the program itself
    bltu    t1, s3, 17f                 # offset + size + 8 > PROGRAM_TOP -> EC 04 (last tail word at most PROGRAM_TOP - 4)
    li      t0, ~PRG_VALID_BIT          # memory is about to be overwritten: clear bit 13 until the load completes
    and     s10, s10, t0                
    mv      t1, s2                      # Nwrite pointer = candidate offset
    mv      t0, s3                      # receive count = candidate size
16:
    rx                          
    sb      a0, 0(t1)           # store byte in memory
    addi    t1, t1, 1           # increment pointer (pointer goes upwards, wheeee!)
    addi    t0, t0, -1          # decerment byte count
    bnez    t0, 16b             # go back if not yet zero

    # now, da fun begins >:D (use our s4 status register to apply its settings here)
    # move size bacak into t0
    srli    t2, s4, 4           # reg display bit
    beqz    t2, 18f
    la      t2, tail_regdisp    # copy the tail stub that jumps to jump_back_reg_disp
    j       19f                 # if reg disp turned on, jump back to different address after executing (its in BIOS, for displaying reg values specifically)
18:
    la      t2, tail_run        # copy the tail stub that jumps to jump_back # if reg disp is turned off, then just go back to start of bios as normal
    # ^^^ jump_back and jump_back_reg_disp are labels that are to be implemented labels, the latter is supposed to display the contents of all 31 GPRs after program completion
    # after jumping back, the BIOS is supposed the status registers back in correctly and go back to idle state after all is done
19:
    # removed the 18-line runtime `jal` encoder (sub t3, t2, t1 ... or t5, t5, t4) and `sw t5, 0(t1)`; replaced by copying a pre-assembled lui+jalr stub
    lw      t3, 0(t2)                   # stub word 1: lui t6, %hi(target)  (reads ROM as data)
    lw      t4, 4(t2)                   # stub word 2: jalr zero, %lo(target)(t6)
    sw      t3, 0(t1)                   # t1 = offset + size: right after the last program byte (word aligned, M6)
    sw      t4, 4(t1)
    mv      s11, s2                     # commit offset only now that the program and its tail are in place
    mv      s9, s3                      # commit size
    li      t3, PRG_VALID_BIT 
    or      s10, s10, t3                # set bit 13: valid program load
    li      a0, FB_PRG_LOAD             # load-complete byte (0xCA), sent before any verify read-back
    tx

    srli    t2, s4, 2           # program telemetry enable bit
    andi    t2, t2, 0x01        # mask out bit
    beqz    t2, 20f
    li      t3, 0x00000800               
    or      s10, s10, t3        # set 11th bit of bios status register (program telemetry enable)
    j       21f
20:
    li      t3, 0xFFFFF7FF               
    and     s10, s10, t3        # also corrected to bit 11 (was clearing bit 10)
21:
    
    srli    t2, s4, 3           # program telemetry reset bit
    andi    t2, t2, 0x01        # mask out bit
    beqz    t2, 22f
    li      t3, 0x00001000               
    or      s10, s10, t3        # set 12th bit of bios status register (program telemetry reset) 
    j       23f
22:
    li      t3, 0xFFFFEFFF               
    and     s10, s10, t3        # also corrected to bit 12 (was clearing bit 11)
23:

    srli    t2, s4, 1           # program verify bit
    andi    t2, t2, 0x01        # mask out bit
    beqz    t2, 24f             # if not set, skip verification
    li      a0, FB_PRG_VERIFY   # send uart tx flag bit for verification (read back)
    tx                          
    mv      a0, s9              # move size back from s9 into a0 as argument for next func
    mv      a1, s11             # move offset from s11 back into a1
    call    mem_print
24:
    andi    t2, s4, 0x01        # program run bit (mask out)
    bnez    t2, program_run     # if not set, then skip, otherwise jump to run

    j       update              # go back to update state

9:
    li      a0, ERR_PROGRAM
    li      a1, ERR_PRG_PARAM_INVALID
    j       error_handler
10:
    li      a0, ERR_PROGRAM
    li      a1, ERR_PRG_ARG_INVALID
    j       error_handler
11:
    li      a0, ERR_PROGRAM
    li      a1, ERR_PRG_PARAM_INVALID
    j       error_handler
17:
    li      a0, ERR_PROGRAM
    li      a1, ERR_PRG_TOO_BIG
    j       error_handler
25:
    li      a0, ERR_PROGRAM
    li      a1, ERR_PRG_OFST_UNALIGN
    j       error_handler
26:
    li      a0, ERR_PROGRAM
    li      a1, ERR_PRG_SIZE_UNALIGN
    j       error_handler

program_verify:
    li      a6, BIOSST_MEM
    call    update_state    # update state
    li      t0, PRG_VALID_BIT
    and     t0, s10, t0
    beqz    t0, program_unverified      # no fully loaded program; avoids a size-0 dump

    mv      a0, s9          # move size back from s9 into a0 as argument
    mv      a1, s11         # move offset from s11 back into a1
    call    mem_print

    j       idle

device_data:

    li      a6, BIOSST_DD
    call    update_state    # update state

    li      a0, FB_DD_DISP  # device data display, send init byte
    tx                      

    li      a0, DD_PARAM_BIOS       # BIOS info
    tx
    la      t0, dd_name_len         # load string length into register from memory
    lw      a0, 0(t0)               
    la      a1, dd_name             # load offset pointer
    call    puts                    # call puts to transmit info

    li      a0, DD_PARAM_ARCH       # architecture info
    tx
    la      t0, dd_arch_len         # load string length into register from memory
    lw      a0, 0(t0)               
    la      a1, dd_arch             # load offset pointer
    call    puts                    # call puts to transmit info

    li      a0, DD_PARAM_REGCNT     # register count
    tx
    la      t0, dd_regc             # load string length into register from memory
    lw      a0, 0(t0)               
    call    send_word               # send as int word (yes ik regc is tiny number but it deals with words for quantities for consistency)

    li      a0, DD_PARAM_CLKSPD     # condigured clock speed
    tx
    la      t0, dd_clk              
    lw      a0, 0(t0)               
    call    send_word               # send as word

    li      a0, DD_PARAM_BAUDTK     # configured baud tick
    tx
    la      t0, dd_baud             
    lw      a0, 0(t0)               
    call    send_word               # send as word
    
    li      a0, DD_PARAM_RAMOFS     # ram offset
    tx
    la      t0, program_start       
    lw      a0, 0(t0)               
    call    send_word               # send as word

    li      a0, DD_PARAM_RAMSZ      # ram size
    tx
    la      t0, ram_size            
    lw      a0, 0(t0)               
    call    send_word               # send as word

    li      a0, DD_PARAM_PROGOFS    # program offset (same as ram offset)
    tx
    la      t0, program_start       
    lw      a0, 0(t0)               
    call    send_word               # send as word

    li      a0, DD_PARAM_PROGSZ     # program size
    tx
    la      t0, program_size        
    lw      a0, 0(t0)               
    call    send_word               # send as word 

    li      a0, DD_PARAM_ROMOFS     # rom offset
    tx
    li      a0, ROM_START           # ROM_START/ROM_SIZE are plain .equ constants, not data labels -- li is correct here, unchanged
    call    send_word               # send as word

    li      a0, DD_PARAM_ROMSZ      # rom size
    tx
    li      a0, ROM_SIZE
    call    send_word               # send as word

    j       idle

bios_log:
    li      a6, BIOSST_LOG_ST
    call    update_state    # update state

    rx                      # get byte indicating on (0x01) or off (0x00) for tracking
    beqz    a0, 1f          # jump to switch off logic
    addi    a0, a0, -1      # subtract 1 to check if equal to zero
    beqz    a0, 2f          # jump to switch on logic
    li      a0, ERR_BIOS
    li      a1, ERR_BIOS_ARG_INVALID    # invalid option (didnt select from 0x00 or 0x01)
    j       error_handler
1:
    li      t0, 0xFFFFFDFF           
    and     s10, s10, t0             # mask to reset 9th bit (bios state update)
    li      a0, FB_BIOSST_LOG        # acknowledgement sent to master device
    tx                               
    li      a0, BIOSST_LOG_OFF
    tx                               
    j       idle
2:
    ori     s10, s10, 0x00000200     # mask to set 9th bit (bios state update)
    li      a0, FB_BIOSST_LOG        # acknowledgement sent to master device
    tx                               
    li      a0, BIOSST_LOG_ON
    tx                               
    j       idle

program_run:
    li      a6, BIOSST_PGEX
    call    update_state    # update state
    li      t0, PRG_VALID_BIT
    and     t0, s10, t0
    beqz    t0, program_unverified      # nothing (or only part of a program) loaded -> EC 01

    # load status registers into BIOS memoryduring program execution, so they can be retreived back after jump back
    # WARNING: since there is no memory segmentation, the program instructions can directly overwrite BIOS allocated memory, and there are no inbuilt protection guards against it
    li      t2, PROGRAM_TOP          
    sw      s9, 4(t2)                
    sw      s10, 8(t2)               # overwrite them, not load (which was clobbering s11 right before the `jr s11`
    sw      s11, 12(t2)              # below, i.e. program_run could never actually have jumped anywhere valid)

    srli    t0, s10, 11     # program telemetry enable
    andi    t0, t0, 0x01    # mask out other bits
    srli    t1, s10, 12     # program telemetry reset
    andi    t1, t1, 0x01    # mask out other bits
    li      t2, ADDR_META_CONTROL      # meta control byte address (write)
    li      t4, ADDR_META_CONTROL_RD   # meta control byte address (read mirror) -- META_CONTROL itself is write-only in hardware, see mmio_interface.sv note
    lbu     t3, 0(t4)       # load the control bits for telemetry rn

    beqz    t0, 1f          # for enable bit (jump if not set)
    ori     t3, t3, 0x02
    j       2f
1:
    andi    t3, t3, 0xFD
2:
    sb      t3, 0(t2)       # write enable bit to to META_CONTROL

    beqz    t1, 3f          # for reset bit (jump if not set)
    ori     t3, t3, 0x01    # set the reset bit (set reset bit to one to assert a reset)
    sb      t3, 0(t2)       # assert reset bit to hardware as pulse
    andi    t3, t3, 0xFE    # reset the reset bit (basically, set reset bit to zero again)
    sb      t3, 0(t2)       # deassert reset bit

3:
    li      sp, PROGRAM_TOP             # now 0x21000 # set up stack pointer at top of the program space (0x20000)
    add     ra, s11, s9                 # ra = the tail's lui, so a program ending in `ret` also returns to the BIOS
    jr      s11                         # jump to program start offset
program_unverified:                     # shared by program_run and program_verify
    li      a0, ERR_PROGRAM 
    li      a1, ERR_PRG_UNVERIFIED
    j       error_handler

# <---------- NOTE: The below two functions were initially written with the help of AI, but were thoroughly reviewed a human. ---------->
jump_back:    #  default post-execution return target (no register display); restores BIOS's own s9/s10/s11, reinitializes s1 and sp, then returns to idle
    li      t0, PROGRAM_TOP          #  these were saved here by program_run before execution began
    lw      s9, 4(t0)                #  restore program size register
    lw      s10, 8(t0)               #  restore BIOS status register
    lw      s11, 12(t0)              #  restore program offset register

    la      s1, UART_STATUS          #  reinitialize UART status pointer (the program may have repurposed s1 for its own use)
    li      sp, RAM_TOP              #  re-heal BIOS stack
    call    sync_bios_telemetry      #  push the restored (BIOS-side) telemetry enable setting out to hardware now that the program has ended, instead of leaving the program's setting active

    j       idle                     #  return to full idle (program execution is only ever reachable once a self test has passed, so plain idle is correct here)

jump_back_reg_disp:    #  post-execution return target when register display was requested; dumps x1-x31 (the program's live values) over UART, then does the same teardown as jump_back
    li      t6, REG_DUMP_BUF         #  use x31 (t6) itself as the dump buffer base pointer, since it's the one register whose own live value can't be captured this way
    sw      ra,  0(t6)               #  x1
    sw      sp,  4(t6)               #  x2
    sw      gp,  8(t6)               #  x3
    sw      tp,  12(t6)              #  x4
    sw      t0,  16(t6)              #  x5
    sw      t1,  20(t6)              #  x6
    sw      t2,  24(t6)              #  x7
    sw      s0,  28(t6)              #  x8
    sw      s1,  32(t6)              #  x9
    sw      a0,  36(t6)              #  x10
    sw      a1,  40(t6)              #  x11
    sw      a2,  44(t6)              #  x12
    sw      a3,  48(t6)              #  x13
    sw      a4,  52(t6)              #  x14
    sw      a5,  56(t6)              #  x15
    sw      a6,  60(t6)              #  x16
    sw      a7,  64(t6)              #  x17
    sw      s2,  68(t6)              #  x18
    sw      s3,  72(t6)              #  x19
    sw      s4,  76(t6)              #  x20
    sw      s5,  80(t6)              #  x21
    sw      s6,  84(t6)              #  x22
    sw      s7,  88(t6)              #  x23
    sw      s8,  92(t6)              #  x24
    sw      s9,  96(t6)              #  x25 (program's live value, captured before it's restored below)
    sw      s10, 100(t6)             #  x26 (program's live value, captured before it's restored below)
    sw      s11, 104(t6)             #  x27 (program's live value, captured before it's restored below)
    sw      t3,  108(t6)             #  x28
    sw      t4,  112(t6)             #  x29
    sw      t5,  116(t6)             #  x30
    sw      zero, 120(t6)            #  x31 (t6) was used as the dump base pointer above, so its original value is lost; reported as 0

    li      t0, PROGRAM_TOP          #  now safe to restore BIOS's own status registers (same as jump_back)
    lw      s9, 4(t0)                #  restore program size register
    lw      s10, 8(t0)               #  restore BIOS status register
    lw      s11, 12(t0)              #  restore program offset register

    la      s1, UART_STATUS          #  reinitialize UART status pointer
    li      sp, RAM_TOP              #  load the value, not the address of the rodata word #  re-heal BIOS stack
    call    sync_bios_telemetry      #  push the restored telemetry enable setting out to hardware

    li      t2, REG_DUMP_BUF         #  send pointer; t6 can't be reused here since the tx/rx macros clobber it as their own link register on every call
    li      a0, FB_REG_DISP          #  opening guard byte
    tx
    li      t4, 1                    #  register index counter, x1 first
1:
    mv      a0, t4                   #  send the register index byte
    tx
    lw      a0, 0(t2)                #  load that register's saved value
    call    send_word                #  send it as 4 little-endian bytes
    addi    t2, t2, 4                #  advance buffer pointer
    addi    t4, t4, 1                #  next register index
    li      t5, 32                   #  loop until index 32 (i.e. after sending x31)
    bne     t4, t5, 1b               #  ...
    li      a0, FB_REG_DISP          #  closing guard byte
    tx

    j       idle                     #  return to full idle

# <<<----- Code snippet below added after human suggested review and feature, made and optimized using AI, never knew this syntax to begin with lmao----->>>
# jump-back tail templates: program_load copies one of these 2-word pairs right after every loaded program.
# they are never executed from here. norelax keeps the linker from shrinking/removing the lui (which would break the 2-word copy).
# t6 is used because the register dump already reports x31 as 0 (it is the dump's base pointer).
    .option push
    .option norelax
    .balign 4
tail_run:
    lui     t6, %hi(jump_back)
    jalr    zero, %lo(jump_back)(t6)
tail_regdisp:
    lui     t6, %hi(jump_back_reg_disp)
    jalr    zero, %lo(jump_back_reg_disp)(t6)
    .option pop

# HELPERS

# NOTE: push_addr/pop_addr removed, see the developer's note near _start and the rx/tx marco definitions
# further up. uart_rx/uart_tx are now leaf functions entered via the rx/tx macros (t6 as link
# register, not ra), so every function that calls them keeps its own ra intact.

uart_rx:    # in: a4 = custom timeout (0 = default), a7 = 1 to suppress the timeout error in idle | out: a0 = byte | clobbers t5, t6
    li      t5, DEFAULT_TIMEOUT_CYCLE
    beqz    a4, 1f          # a4 is custom timeout parameter, if its already zeroed out, then use default (jump to 1 directly)
    mv      t5, a4
1:
    lbu     a0, 0(s1)       # load UART status byte
    addi    t5, t5, -1      # decrement timeout checker
    beqz    t5, timeout_handler
    andi    a0, a0, 0x01    # mask only bit 1 (RX VALID)
    beqz    a0, 1b          # loop back while uart status is 0 (not yet valid)
    lbu     a0, 4(s1)       # load data byte once status is nonzero (valid byte ready)
    li      a4, 0           # clear a4 to default value again, a4 must be explicitly set when its to be called
    li      a5, 0
    jr      t6 

uart_tx:    # NOTE: no need for safety checker here, as its BIOS side, cannot timeout ideally | in: a0 = byte | clobbers t5
1:
    lbu     t5, 0(s1)       # load UART status byte
    andi    t5, t5, 0x02    # mask only bit 2 (TX BUSY)
    bnez    t5, 1b          # wait till valid (until tx_busy != 1)
    sb      a0, 8(s1)       # send data via UART channel once no longer busy
    jr      t6              

# BIOS Functions

send_word: # sent in little endian order, return the original word too
    li      t0, 4           # 4 bytes per word
    mv      t1, a0          # temporarily store original word
1:  
    tx                      # send lower byte
    srli    t1, t1, 8       # shift right one byte
    mv      a0, t1          # refresh a0 with the next byte to send
    addi    t0, t0, -1      # subtract once from loop variable
    bnez    t0, 1b          # go back if not yet zero (loop 4 times)
    ret

get_word:   # little endian 4 byte word
    addi    t0, x0, 4       # loop 4 times for 4 bytes
    addi    t1, x0, 0       # initialize shift counter to 0 bits
    li      t3, 0
1:  
    rx
    sll     t2, a0, t1      # shift new byte left by current shift counter (0 -> 8 -> 16 -> 24)
    or      t3, t3, t2      # merge the shifted byte into final reg
    addi    t1, t1, 8       # increment shift counter by 8 bits for the next byte
    addi    t0, t0, -1      # decrement shift loop counter
    bnez    t0, 1b          # go back if not yet 0

    mv      a0, t3          # move from temp register to return register
    ret

update_state:
    andi    a6, a6, 0xFF    # mask out lower byte of status update, in case
    li      t0, 0xFFFFFF00
    and     s10, s10, t0
    or      s10, s10, a6    # load lower byte of a6 into s10 to update status
    andi    t1, s10, 0x00000200     # mask out 9th bit (status flush)
    beqz    t1, 1f          # if zero, then skip status flushing directly and return
    mv      t1, a0          # save existing return value (prevent return value loss from before)
    li      a0, FB_BIOSST_UPDT
    tx                      # update push update bios state 
    mv      a0, a6          # push updated state as byte
    tx
    mv      a0, t1
1:
    ret

mem_print:
    fn_enter                
    mv      t2, a0          # keep the size in t2, check_size clobbers t0/t1 # size

    call    check_size
    beqz    a0, 2f          # if size overflow
    mv      t0, t2          # size
    mv      t1, a1          # offset (as a1 is untouched by check_size)
1:  
    lbu     a0, 0(t1)       # load byte from memory
    tx                      # send via uart tx
    addi    t0, t0, -1      # subtract 1 from size to reduce count
    addi    t1, t1, 1       # incremement offset pointer
    bnez    t0, 1b

    fn_leave
2:
    li      a0, ERR_MEMORY
    li      a1, ERR_MEM_OUT_OF_BOUNDS
    j       error_handler

gets:
    fn_enter                # calls check_size internally via call, to not overwrite ra and asve it instead
    rx                      
    li      t0, TB_MSG_STR  # verify it is a string first
    bne     a0, t0, 3f      # jump to error handler if bytes not equal

    call    get_word
    mv      s4, a0          # string size, move into s4 temporarily to survive check_size
    li      t0, MSG_ECHO_BUF_SIZE
    bltu    t0, a0, 2f      # longer than the 256-byte echo buffer -> E3 01
    call    check_size
    beqz    a0, 2f          # if message size too high, respective error  
    mv      t1, s4          # move size into t1
    mv      t0, a1          # move pointer into t0, a1 returns the offset pointer to be used by a potential puts later
1:
    rx                      
    sb      a0, 0(t0)       # store to pointer
    addi    t0, t0, 1       # incrememnt pointer
    addi    t1, t1, -1      # decrement counter
    bnez    t1, 1b          # loop as long as counter is not zero

    mv      a0, s4          # return size (saved in s4 earlier)
    fn_leave                
2:
    li      a0, ERR_MESSAGE             # load a0 for error handler type indicator
    li      a1, ERR_GET_MSG_TOO_BIG     # load a1 for error handler exact type
    j       error_handler
3: 
    li      a0, ERR_MESSAGE
    li      a1, ERR_GET_MSG_UNVERIFIED  # unverified get message
    j       error_handler

puts:
    fn_enter                # calls check_size internally via call, to not overwrite ra
    mv      s4, a0          # string size 
    call    check_size
    beqz    a0, 2f          # if message size is too high (as returned by check_size), raise error
    mv      t1, s4          # move size into t1
    mv      t0, a1          # move pointer into t0

    li      a0, FB_MSG_STR  # only start trasmitting the string after verifying tramissibility
    tx                       # start with transmitting 0x3D prefix string byte

    mv      t2, s4           # send the 4-byte little-endian length next (puts was never actually sending it,
    li      t3, 4            # per the confirmed protocol: 0x3D, then 4-byte length, then N bytes)
3:  mv      a0, t2
    tx                        # send next length byte
    srli    t2, t2, 8         # shift to the next byte
    addi    t3, t3, -1
    bnez    t3, 3b
1:
    lb      a0, 0(t0)       # load byte from pointer to register
    tx                      # send via tx
    addi    t0, t0, 1       # increment pointer
    addi    t1, t1, -1      # decrement counter
    bnez    t1, 1b          # loop as long as counter is not zero

    fn_leave                
2:
    li      a0, ERR_MESSAGE
    li      a1, ERR_PUT_MSG_TOO_BIG
    j       error_handler

check_size:
    li      t0, RAM_TOP - BIOS_STACK_SIZE   # top address for BIOS data (end of stack)
    bgeu    a1, t0, 1f                      # unsigned: offset at/above the top (also catches huge 'negative' offsets)
    beqz    a0, 1f                          # zero size is never valid
    sub     t1, t0, a1                      # subtract offset pointer address from top address to get remaining size

    sltu    a0, t1, a0                      # (compare addresses) if message size too high, return result as 0 (fail), else return as 1
    xori    a0, a0, 1                       # 1 = fits; size == remaining (i.e. ends exactly at 0x21FBF) is now allowed
2:
    ret                                 
1:
    li      a0, 0
    j       2b                          # error raised if offset is higher than allocated memory top

sync_bios_telemetry:   # pushes s10 bit 10 (BIOS telemetry enable) out to hardware meta_enable
    srli    t0, s10, 10
    andi    t0, t0, 0x01
    li      t1, ADDR_META_CONTROL
    li      t2, ADDR_META_CONTROL_RD
    lbu     t3, 0(t2)
    beqz    t0, 1f
    ori     t3, t3, 0x02
    j       2f
1:
    andi    t3, t3, 0xFD
2:
    sb      t3, 0(t1)
    ret


# HANDLERS
timeout_handler:    # uses a5 for checking handler type
    bnez    a7, 2f                              # if it was in idle state, skip transmitting timeout errors
    beqz    a5, 1f                              # if zero, use default handler
    addi    t1, a5, -1                          # check for if 1
    beqz    t1, connection_timeout_handler      # if 1, use connection timeout handler
    j       critical_error                      # must match a handler, critical error otherwise
1:
    li      a0, ERR_BIOS                # bios timeout error type
    tx
    li      a0, ERR_BIOS_TIMEOUT        # bios timeout error code
    tx
    j       rx_cooldown                 # mid-command timeout (allows byte drain and gives host time to adjust accordingly, safety mechanic)
2:
    j       idle_or_stfail              # resume whichever idle state is currently appropriate (normal idle, or the limited POST-fail idle if the last self test failed)
# ^^^ DEVELOPERS NOTE: this current implementation is used as there are no RX/TX FIFOs that allow staging multiple bytes at once
# said feature will be added in the near future as an upgrade

connection_timeout_handler:     # specifically for connection timeout
    li      a0, ERR_CONNNECT            # error type
    tx 
    li      a0, ERR_CONNECTION_TIMEOUT  # error codes
    tx
    li      t0, 0xFFFFFEFF
    and     s10, s10, t0                # ACK timed out: clear the connection bit, like the invalid-ACK path
    j       rx_cooldown                 # cooldown, then rx_cooldown resumes the right idle state #  resume whichever idle state is currently appropriate (only ever reached via connect's own rx, so this correctly returns to st_fail_idle if that's where connect was called from)

error_handler:
    tx                          # call tx with error type in a0
    mv      a0, a1              # move a1 (error code) to a0 for calling tx agagin
    tx                          # call tx with error code, now in a0
    j       rx_cooldown         # jump back to whichever idle state is currently appropriate, instead of always full idle (needed since connect's failure path can be reached from st_fail_idle too), also drain the stream before idling to prevent unrecognized bytes from interfering and being detected as a command

critical_error:     # generally meant for BIOS-side errors
    li      a0, ERR_CRITICAL    # load 0xEE for ciritcal error transmission to master device
    tx                          
    j       reset

# post-error cooldown -> waits for tx to finish the error bytes, then reads and discards every rx byte until
# the line has been quiet for DRAIN_QUIET_BYTES byte-times (each received byte restarts the window). Transmits nothing.
rx_cooldown:
1:
    lbu     t5, 0(s1)
    andi    t5, t5, 0x02                # tx busy
    bnez    t5, 1b                      # let last error byte leave the wire first
    li      t5, DRAIN_QUIET_ITER
2:
    lbu     t0, 0(s1)
    andi    t0, t0, 0x01                # rx valid
    beqz    t0, 3f
    lbu     t0, 4(s1)                   # read (and so ack) the byte, then drop it
    li      t5, DRAIN_QUIET_ITER        # a byte arrived: restart the quiet window
3:
    addi    t5, t5, -1
    bnez    t5, 2b
    j       idle_or_stfail              # quiet long enough

idle_or_stfail:    #  shared return point for code reachable from both the normal idle and the limited POST-fail idle (error_handler, connection_timeout_handler, timeout_handler, connect); resumes whichever is appropriate based on the last self-test outcome
    li      t0, 0x00020000          # mask for self-test-passed bit; andi can't take an immediate this large
    and     t0, s10, t0             # self-test-passed bit (17)
    beqz    t0, st_fail_idle        # last self test failed -> stay in the limited state
    j       idle                    # otherwise resume full idle as before

st_fail_idle:   # this is a specific limited state of the BIOS if it fails on POST, only functionality is connection
    li      sp, RAM_TOP             # heal stack each time this limited idle state is (re)entered, mirroring normal idle
    li      a4, 0                   # same reset of the rx timeout parameters as idle
    li      a5, 0
    li      a6, BIOSST_STFIDL       # update BIOS state to the limited POST-fail idle state
    call    update_state            # push state update to host
1:
    addi    a7, x0, 1               # suppress timeout error while waiting, same as normal idle
    rx                              # wait for a command byte
    addi    a7, x0, 0               # byte received: re-enable timeout errors (connect must report EA 02 on an ACK timeout)
    li      t1, TB_NET_SYN          # only a connection attempt is serviced in this state
    beq     a0, t1, connect         # hand off to the normal connect routine
    li      t1, TB_ST_INIT
    beq     a0, t1, req_self_test   # re-run the self test from here (debugging); a pass resumes normal idle
    #  ignore any other byte and keep waiting
    li      a0, ERR_BIOS            # anything else -> EF 03, then the H3 cooldown back into st_fail_idle
    li      a1, ERR_BIOS_INV_CMD
    j       error_handler
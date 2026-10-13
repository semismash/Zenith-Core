# BIOS specific constant declarations
.equ DEFAULT_TIMEOUT_CYCLE, 0x4000000                   # 67 million cycle safety window (6.7s at 10MHz)
.equ UART_STATUS,       0x80000000                  # 0x8000_0000
.equ UART_RXD_OFFSET,   0x4                         # 0x8000_0004
.equ UART_TXD_OFFSET,   0x8                         # 0x8000_0008
.equ PROGRAM_START,     0x1000                      # program entry point
.equ RAM_SIZE,          0x20000                     # 128 KiB RAM (matches size of RAM)
.equ PROGRAM_TOP,       0x20000                     # program top address, everything above that is reserved by BIOS
.equ RAM_TOP,           PROGRAM_START + RAM_SIZE    # PROGRAM_START + RAM_SIZE, top of stack grows down from here, (0x21000)

.equ ROM_START,         0x0
.equ ROM_SIZE,          0x1000

# Telemetry
.equ ADDR_META_CONTROL,     0x80001000
.equ ADDR_META_INSTR,       0x80001005
.equ ADDR_META_STALL,       0x80001008
.equ ADDR_META_L_USE,       0x8000100C
.equ ADDR_META_BR_FLUSH,    0x80001010

.equ BIOS_STACK_SIZE,   64                          # 64 bytes allocated for BIOS

.include "protocol.inc"     # <---- all da protocol codez in here :3

# REGISTER USAGE:
# a0 - callee return value 1
# a1 - callee return value 2
# a0-a7 - function arguments
    # a4 - UART timeout custom
    # a5 - Timeout handler (0 = default, 1 = connection)
    # a6 - BIOS state update
    # a7 - UART idle indicator (if uart not receiving anything since its in idle state or not or not)
# t0-t6 - temporary function-specific variables
# s0-s11 - global/high-lifetime variables
    # s1 - UART status
    # s2 - UART RX DATA
    # s3 - UART TX DATA
    # s9 - Loaded Program Size
    # s10 - BIOS Status Register
        # [7:0]: BIOS Status Byte
        # [8]: BIOS Connection Valid
        # [9]: BIOS Status Flush (State logging)
        # [10]: BIOS Telemetry Enable
        # [11]: Program Telemetry Enable
        # [12]: Program Telemetry Reset
        # vvv These bits are not automatically reset upon forced reset
        # [16]: Prior Connection (first time connecting, or has been connected before)
        # [17]: Self Test Passed
        # [18-23]: Tests pass bitmask
    # s11 - Program Start Offset

# MEMORY LAYOUT:
# 0x00000000 - 0x00000FFF: BIOS ROM
# 0x00001000 - 0x0001FFFF: PROGRAM SPACE (PROGRAM STACK DEFAULT: 0x00020000)
# 0x00020000 - 0x00020FBF: BIOS DATA SPACE
# 0x00020FC0 - 0x00021000: BIOS STACK (allocate 64 bytes (16 words) space for BIOS stack)

# write and then verify x1-x31 (used by self-test)
.macro test_reg reg, idx
    li      \reg, (0xDEAD0000 | \idx)
.endm

.macro check_reg reg, idx
    li      t6, (0xDEAD0000 | \idx)      # t6 as a scratch reg, checked seperately later on
    bne     \reg, t6, selftest_reg_fail
.endm

.global _start

.section .rodata
.align 2

# BIOS Messages
bios_start_msg_len: # length of below string + 0x00 for null term
    .word   26
bios_start_msg:
    .string "BIOS Loaded Successfully!"

# Memory Layouts
program_start:      # 0x1000
    .word   PROGRAM_START
ram_size:           # 0x20000
    .word   RAM_SIZE
ram_top:            # 0x21000
    .word   RAM_TOP
program_top:        # 0x20000
    .word   PROGRAM_TOP
program_size:
    .word   PROGRAM_TOP - PROGRAM_START
bios_stack_top:     # 0x21000
    .word   RAM_TOP
program_stack_top:  # 0x20000
    .word   PROGRAM_TOP
bios_data_top:      # 0x20FC0
    .word   RAM_TOP - BIOS_STACK_SIZE
bios_mem_size:
    .word   RAM_TOP - BIOS_STACK_SIZE - PROGRAM_TOP

# Device Data
dd_name_len:
    .word   23
dd_name:    # device bios name
    .string "Zenith Core BIOS v.1.0"
dd_arch_len:
    .word   24
dd_arch:    # device arch
    .string "RISC-V | RV32I | 32-bit"
dd_regc:    # GPR count
    .word   32
dd_clk:     # configured clock speed
    .word   10000000    # MHz
dd_baud:    # configured UART baud tick rate
    .word   9600        # MHz

# Program completion
jump_back:
    .word   0x67000000  # little endian words instruction for jalr x0, 0(x0)
jump_back_reg_disp:
    .word   0x67000000  # little endian words instruction for jalr x0, 0(x0) [SUBJECT TO CHANGE]

# Other
connection_timeout:
    .word   0x8F00000   # ~150 million cycles (~15 seconds delayed @ 10MHz)

.section .text

_start:

# ---------- DEVELOPER'S NOTE ----------
# the push_addr stack utility command is currently being used in a lot of places for utility, specifically for nested loops
# however there is a consideration of removing the command from many unnecessary places to improve performance and code density
# this is more of a developer specific reminder, but also one for those who see the codebase in this current commit
# --------------------------------------

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
    # check remaining 15 regs
    check_reg x16, 16
    check_reg x17, 17
    check_reg x18, 18
    check_reg x19, 19
    check_reg x20, 20
    check_reg x21, 21
    check_reg x22, 22
    check_reg x23, 23
    check_reg x24, 24
    check_reg x25, 25
    check_reg x26, 26
    check_reg x27, 27
    check_reg x28, 28
    check_reg x29, 29
    check_reg x30, 30

    mv      s8, x1  # move back into x1 (thank you, x1! :D)

    # test t6 register using x30 (already verified)
    li      x31, (0xDEAD0000 | 31)
    li      x30, (0xDEAD0000 | 31)
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
# addresses spanning program space: 0x1000, 0x8000, 0x10000, 0x1FFFC (word-aligned top)
selftest_mem:
    li      t0, 0x1000
    li      t1, 0xA1A1A1A1
    sw      t1, 0(t0)
    lw      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    li      t0, 0x8000
    li      t1, 0xB2B2B2B2
    sw      t1, 0(t0)
    lw      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    li      t0, 0x10000
    li      t1, 0xC3C3C3C3
    sw      t1, 0(t0)
    lw      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    li      t0, 0x1FFFC
    li      t1, 0xD4D4D4D4
    sw      t1, 0(t0)
    lw      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    # byte access
    li      t0, 0x1000
    li      t1, 0x5A
    sb      t1, 0(t0)
    lb      t2, 0(t0)
    bne     t1, t2, selftest_mem_fail

    # halfword access
    li      t0, 0x1004
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
    li      a0, FB_ST_TESTBYTE      # arbitrary known test byte
    call    uart_tx                 # if uart_tx returns at all (doesn't hang), transmit path is considered functional
    
    ori     s8, s8, 0x20        # pass (set bit 5)
    addi    s8, s8, 0x100       # increase the counter in byte 1

st_evaluate:
    andi    t0, s8, 16          # mask out lowest byte to get bitmask of passed and failed tests
    li      t1, 0x0000FF00      # get number of passed tests by masking byte 1
    and     t1, s8, t1
    srli    t1, t1, 8
    li      t2, 0x00FF0000      # get whether test was POST or requested by master device by masking byte 2
    and     t2, s8, t2
    srli    t2, t2, 16

    addi    t3, t1, -6          # check if equal to 6 tests or not
    snez    t3, t3              # set as one if all tests passed, else set as zero
    li      t4, 0x00020000      # mask bit 17
    beqz    t3, 1f              # tests passed
    or      t5, t5, t4          # update t5 (here t5 maps to the upper bits of s10, to be shifted later) bit 17 (self test passed) to true     
    j       2f
1:
    xori    t4, t4, -1
    and     t5, t5, t4          # update t5 bit 17 (self test failed) to false
2:
    slli    t4, t0, 18          # set 0-5 bits of bitmask in t0 to corresponding 18-23 bits in t5 register
    lui     t3, 0xFC
    and     t4, t4, t3
    xori    t3, t3, -1
    and     t5, t5, t3
    or      t5, t5, t4

    mv      s5, t0              # move bitmask into s5 register to survive function branch
    mv      s6, t5              # move t5 status register into s6 (only contains upper bits)
    beqz    t2, req_self_test_res       # go back to req self test if the indicator bit was high (i am high)

    mv      s10, t5             # update s10 to t5 (we can do this because it means it is a POST initialization, since it didnt take prev branch)

setup:

reset:
    # initialize BIOS constants (UART mainly)
    la      s1, UART_STATUS             # s1 - UART STATUS
    addi    s2, s1, UART_RXD_OFFSET     # s2 - UART RX DATA
    addi    s3, s1, UART_TXD_OFFSET     # s3 - UART TX DATA
    addi    s9, x0, 0                   # s9 - Program size register
    addi    s10, s10, 0                 # s10 - BIOS status register
    li      t1, 4
    slli    t1, t1, 12
    xori    t1, t1, -1
    and     s10, s10, t1                # bits 12-15 (set to zero)
    addi    s11, x0, 0                  # s11 - Program offset register

    la      sp, bios_stack_top      # initialize stack
    addi    a4, x0, 0               # clear a4 register to prevent interference with UART rx timer (see uart_rx: label below)

update:

idle:
    li      a5, BIOSST_IDLE
    call    push_addr
    call    update_state            # update state to idle
1:
    addi    a7, x0, 1               # load as idle = 1 so uart_rx doesn't transmit timeout error upon timeout
    call    uart_rx                 # call uart rx in idle to receive command
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
    li      t1, TB_MEM_DUMP         # memory dump
    beq     t0, t1, memory
    li      t1, TB_NET_ACK          # connection attempt
    beq     t0, t1, connect
    li      t1, TB_PRG_LOAD         # program load
    beq     t0, t1, program_load
    li      t1, TB_PRG_VERIFY       # program verification
    beq     t0, t1, program_verify
    li      t1, TB_DD_DATA          # check device data request
    beq     t0, t1, device_data
    li      t1, TB_BIOS_DATA        # check if BIOS data monitoring is turned on
    beq     t0, t1, bios_log

    j       1b                    # loop around if no valid command bytes, no error 

# BIOS UTILITY

msg_echo:
    li      a6, BIOSST_MSG
    call    push_addr
    call    update_state    # update state
    
    call    push_addr       # push address to stack
    call    gets            # get input string of byte size a long with size

    li      a0, FB_MSG_ECHO # send transmission byte starting message display attempt
    call    uart_tx  

    call    push_addr       # push address to stack again
    call    puts            # print string via uart using puts

    li      a0, FB_MSG_FLSH
    call    uart_tx         # transmit flush message towards the end
    
    j       idle            // slash slash comment cuz funny

req_self_test:
    li      a6, BIOSST_MSG
    call    push_addr
    call    update_state    # update state

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
    addi    s2, UART_RXD_OFFSET
    addi    s3, UART_TXD_OFFSET

    mv      t0, s5          # move mask back from branch
    li      t0, 0x00FF0000  # update s10 bits 16-23 to the new values of 16-23 (achived from s5 bitmask we stored)
    and     t0, s5, t0
    li      t1, 0xFF00FFFF
    and     s10, s10, t1
    or      s10, s10, t0

    lui     t1, 0x20
    xori    t1, t1, -1
    and     t0, t0, t1      # get 17th bit to see if test passed or failed (ik this is inefficient, ill fix it later, im just so mentally tired man)
    
    bnez    t0, 1f          # if t0 is 0 after that, means test failed, so jump then
    li      a0, FB_ST_PASS
    call    uart_tx
    j       2f
1:
    li      a0, FB_ST_FAIL
    call    uart_tx
2:

    # give results of each test
    li      t2, ST_PARAM_TEST_0
    li      t3, t0, 6       # loop count (6 for 6 tests)
    addi    t4, x0, x0      # loop counter

    li      a0, FB_ST_RESULTS
    call    uart_tx
3:
    addi    t2, t2, 1       # shift testcase number first
    mv      t2, a0
    call    uart_tx
    srl     t1, t0, t4      # shift the mask to the right each time, to go through test cases
    andi    t1, t1, 1       # get first bit only after shifting
    snez    a0, t1          # set to pass or fail
    call    uart_tx
    bne     t3, t4, 3b      # go back to loop as long as loop counter doesnt hit 6 yet (t3)

    li      a0, FB_ST_FINISH
    call    uart_tx
    j       idle

telemetry:  # while writing this function, one half of me was sleepy and the other half of me was depressed, pls don't judge
    li      a6, BIOSST_META
    call    push_addr
    call    update_state    # update state

    li      t4, 4           # for four possible arguments (bios tele, prog tele, inst telereset, prog telereset)
1:  
    call    uart_rx         # get byte
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
    beqz    a0, t0, 7f      # instant reset telemetry now
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
    call    uart_rx         # receive argument byte
    li      t2, META_ARG_ON
    beq     t0, t2, 8f      # if ON
    li      t2, META_ARG_OFF
    beq     t0, t2, 9f      # if OFF
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
    li      t0, ADDR_META_CONTROL   # meta control byte address
    lbu     t2, 0(t0)               # get current meta control status
    nop                             # load use stall
    ori     t2, t2, 0x01            # LSB is reset, assert high
    sb      t2, 0(t0)               # store it
    andi    t2, t2, 0xFE            # one's complement to reset that bit
    sb      t2, 0(t0)               # store status with reset bit to finish reset assertion
    
    j       1b                      # loop back for next argument
12:
    addi    t1, t1, -4              # if arguments left was still 4 (immediately guard byte was send, meaning that user requested display of current telemetry settings)
    bnez    t1, 14f

    li   a0, 0x70                   # bit 10
    call uart_tx
    
    andi a0, s10, 0x00000100        # mask bit 10 
    snez a0, a0                     # set a0 to 1 if bit is on, 0 if off
    call uart_tx

    li   a0, 0x71                   # bit 11
    call uart_tx
    
    andi a0, s10, 0x00000200        # mask bit 11 
    snez a0, a0                     # set a0 to 1 if bit is on, 0 if off
    call uart_tx

    li   a0, 0x72                   # bit 12
    call uart_tx
    
    andi a0, s10, 0x00000400        # mask bit 12 
    snez a0, a0                     # set a0 to 1 if bit is on, 0 if off
    call uart_tx
  
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
    j       error_handler   # holy shit it's exactly 100 lines long :o

memdump:
    li      a6, BIOSST_MEM
    call    push_addr
    call    update_state    # update state

    call    push_addr       
    call    get_word        # get size word
    mv      a0, t0          

    call    push_addr
    call    get_word        # get offset word
    mv      a0, t1

    mv      t0, a0          # move to respective argument positions
    mv      t1, a1          # for the mem display function

    call    push_addr
    call    mem_print       # call mem diplay function (a0 = size, a1 = offset)

    j       idle

connect:
    li      a6, BIOSST_NET
    call    push_addr
    call    update_state        # update state

    li      a0, FB_NET_SYNACK   # send back SYN-ACK byte to verify connection
    call    uart_tx
    li      a4, connection_timeout
    li      a5, 1
    call    uart_rx             # verify ACK byte
    li      t0, TB_NET_ACK
    bne     a0, t0, 1f          # if ACK is verified, connect successfully and update status, otherwise, jump to error_handler
    ori     s10, s10, 0x00000100     # set connection bit to 1
    j       idle
1:
    andi    s10, s10, 0xFFFFFEFF     # set connection bit (8th bit) to 0
    li      a0, ERR_CONNNECT
    li      a1, ERR_CONNECTION_INVALID
    j       error_handler

program_load:   # here, the s4 register is used like a temporary status register for this function or some shit idk
    # s4 status register = [4 (reg disp), 3 (telereset), 2 (telemode), 1 (verify), 0 (run)]
    li      a6, program_load
    call    push_addr
    call    update_state        # update state    

    li      s11, PROGRAM_START  # default program start offset into s11 program offset register
    li      t4, 6               # 6 possible arguments (run, verify, offset, telemetry mode, telemetry reset, register display)
1:  
    li      t0, TB_PRG_LOAD     # if arguments loaded... or not (recheck using the same verification byte again)
    call    uart_rx
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
    call    push_addr           # but still safety to move out from temp reg before calling func
    call    get_word            
    mv      t4, s5
    mv      s11, a0             # move program load offset into offset register (s11 is the program offset register, programs are loaded and run here)
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
    call    uart_rx
    li      t2, 0
    beq     a0, t2, 13f         # if FALSE (0x00)
    li      t2, 1
    beq     a0, t2, 14f         # if TRUE (0x01)
    j       10f                 # invalid argument otherwise
13:
    or      s4, s4, t0          # set the corresponding bit
    j       15f
14:
    xori    t0, t0, -1
    and     s4, s4, t0          # reset the corresponding bit
15:
    addi    t4, t4, -1          # decrement count
    j       1f                  # go back in tloop

2:
    call    push_addr           # program get size
    call    get_word
    
    mv      a1, s11             # move offset into a1 as arg
    mv      s9, a0              # move into s9 program size register first
    mv      t0, a0              # move to t0 as check_size consumes a0
    addi    a0, a0, 4           # add 4 (1 word) to a0 for size measurement, need one extra word at the end for a jump instruction back to bios after program execution
    call    push_addr           # check program size
    call    check_size
    beq     a0, 17f             # size is too big, fail to load program

    mv      t1, s11             # move offset pointer to t11 for use
    mv      t2, t0              # load program size again (for later use for mem dumps and shi), as t0 gets consumed right after this
16:
    call    uart_loop
    sb      a0, 0(t1)           # store byte in memory
    addi    t1, t1, 1           # increment pointer (pointer goes upwards, wheeee!)
    addi    t0, t0, -1          # decerment byte count
    bnez    t0, 16b             # go back if not yet zero

    # now, da fun begins >:D (use our s4 status register to apply its settings here)
    mv      t0, t2              # move size bacak into t0
    srli    t2, s4, 4           # reg display bit
    beqz    t2, 18f
    li      t2, jump_back_reg_disp
    j       19f                 # if reg disp turned on, jump back to different address after executing (its in BIOS, for displaying reg values specifically)
18:
    li      t2, jump_back       # if reg disp is turned off, then just go back to start of bios as normal
19:
    sb      t2, 0(t1)           # finish loading program finally

    srli    t2, s4, 2           # program telemetry enable bit
    andi    t2, t2, 0x01        # mask out bit
    beqz    t2, 20f
    ori     s10, s10, 0x00000400        # set 10th bit of bios status register (program telemetry enable)
    j       21f
20:
    andi    s10, s10, 0xFFFFFBFF        # reset 10th bit of bios status register (program telemetry enable)
21:
    
    srli    t2, s4, 3           # program telemetry reset bit
    andi    t2, t2, 0x01        # mask out bit
    beqz    t2, 22f
    ori     s10, s10, 0x00000800        # set 11th bit of bios status register (program telemetry reset)
    j       23f
22:
    andi    s10, s10, 0xFFFFF7FF        # reset 11th bit of bios status register (program telemetry reset)
23:

    srli    t2, s4, 1           # program verify bit
    andi    t2, t2, 0x01        # mask out bit
    beqz    t2, 24f             # if not set, skip verification
    li      a0, FB_PRG_VERIFY   # send uart tx flag bit for verification (read back)
    call    uart_tx
    mv      a0, s9              # move size back from s9 into a0 as argument for next func
    mv      a1, s11             # move offset from s11 back into a1
    call    push_addr
    call    mem_print
24:
    andi    t2, s4, 0x01        # program run bit (mask out)
    bnez    t2, program_run     # if not set, then skip, otherwise jump to run

    j       update              # go back to update state

9:
    li      a0, ERR_PROGRAM
    li      a0, ERR_PRG_PARAM_INVALID
    j       error_handler
10:
    li      a0, ERR_PROGRAM
    li      a0, ERR_PRG_ARG_INVALID
    j       error_handler
11:
    li      a0, ERR_PROGRAM
    li      a0, ERR_PRG_PARAM_INVALID
    j       error_handler
17:
    li      a0, ERR_PROGRAM
    li      a0, ERR_PRG_TOO_BIG
    j       error_handler

program_verify:
    li      a6, BIOSST_MEM
    call    push_addr
    call    update_state    # update state

    mv      a0, s9          # move size back from s9 into a0 as argument
    mv      a1, s11         # move offset from s11 back into a1
    call    push_addr
    call    mem_print

    j       idle

device_data:

    li      a6, BIOSST_DD
    call    push_addr
    call    update_state    # update state

    li      a0, FB_DD_DISP  # device data display, send init byte
    call    uart_rx
    
    li      a0, DD_PARAM_BIOS       # BIOS info
    call    uart_rx
    li      a0, dd_name_len         # load string size
    la      a1, dd_name             # load offset pointer
    call    push_addr
    call    gets

    li      a0, DD_PARAM_ARCH       # architecture info
    call    uart_rx
    li      a0, dd_arch_len         # load string size
    la      a1, dd_arch             # load offset pointer
    call    push_addr
    call    gets

    li      a0, DD_PARAM_REGCNT     # register count
    call    uart_rx
    li      a0, dd_regc
    call    push_addr
    call    send_word               # send as int word (yes ik regc is tiny number but it deals with words for quantities for consistency)

    li      a0, DD_PARAM_CLKSPD     # condigured clock speed
    call    uart_rx
    li      a0, dd_clk
    call    push_addr
    call    send_word               # send as word

    li      a0, DD_PARAM_BAUDTK     # configured baud tick
    call    uart_rx
    li      a0, dd_baud
    call    push_addr
    call    send_word               # send as word
    
    li      a0, DD_PARAM_RAMOFS     # ram offset
    call    uart_rx
    li      a0, program_start
    call    push_addr
    call    send_word               # send as word

    li      a0, DD_PARAM_RAMSZ      # ram size
    call    uart_rx
    li      a0, ram_size
    call    push_addr
    call    send_word               # send as word

    li      a0, DD_PARAM_PROGOFS    # program offset (same as ram offset)
    call    uart_rx
    li      a0, program_start
    call    push_addr
    call    send_word               # send as word

    li      a0, DD_PARAM_PROGSZ     # program size
    call    uart_rx
    li      a0, program_size
    call    push_addr
    call    send_word               # send as word

    li      a0, DD_PARAM_ROMOFS     # rom offset
    call    uart_rx
    li      a0, ROM_START
    call    push_addr
    call    send_word               # send as word

    li      a0, DD_PARAM_ROMSZ     # rom size
    call    uart_rx
    li      a0, ROM_SIZE
    call    push_addr
    call    send_word               # send as word

    j       idle

bios_log:
    li      a6, BIOSST_LOG_ST
    call    push_addr
    call    update_state    # update state

    call    uart_rx         # get byte indicating on (0x01) or off (0x00) for tracking
    beqz    a0, 1f          # jump to switch off logic
    addi    a0, a0, -1      # subtract 1 to check if equal to zero
    beqz    a0, 2f          # jump to switch on logic
    li      a0, ERR_BIOS
    li      a1, ERR_BIOS_ARG_INVALID    # invalid option (didnt select from 0x00 or 0x01)
    j       error_handler
1:
    andi    s10, 0xFFFFFDFF # mask to reset 9th bit (bios state update)
    li      a0, BIOSST_LOG          # acknowledgement sent to master device
    call    uart_rx
    li      a0, BIOSST_LOG_OFF
    call    uart_rx
    j       idle
2:
    ori     s10, 0x00000200 # mask to set 9th bit (bios state update)
    li      a0, BIOSST_LOG          # acknowledgement sent to master device
    call    uart_rx
    li      a0, BIOSST_LOG_ON
    call    uart_rx
    j       idle

program_run:
    li      a6, BIOSST_PGEX
    call    push_addr
    call    update_state    # update state

    srli    t0, s10, 10     # program telemetry enable
    andi    t0, t0, 0x01    # mask out other bits
    srli    t1, s10, 11     # program telemetry reset
    andi    t1, t1, 0x01    # mask out other bits
    li      t2, ADDR_META_CONTROL
    lbu     t3, 0(t2)       # load the control bits for telemetry rn

    beqz    t0, 1f          # for enable bit (jump if not set)
    ori     t3, t3, 0x02
    j       2f
1:
    andi    t3, t3, 0xFD
2:

    beqz    t0, 3f          # for reset bit (jump if not set)
    ori     t3, t3, 0x01    # set the reset bit (set reset bit to one to assert a reset)
    nop                     # one cycle stability
    andi    t3, t3, 0xFE    # reset the reset bit (basically, set reset bit to zero again)

3:
    li      sp, PROGRAM_TOP # set up stack pointer at top of the program space (0x20000)
    jr      s11             # jump to program start offset

# HELPERS

push_addr:  # push address to stack, always to be used before a call instruction to be used correctly
    addi    t0, ra, 4       # add 4 bytes to caller address (skip two instructions ahead of caller, saved ra + 1 extra for skipping next call)
    addi    sp, sp, -4      # decrement stack pointer
    sw      t0, 0(sp)       # save address of stack pointer to stack
    ret

pop_addr:
    mv      t0, ra          # move current ra to t0
    lw      ra, 0(sp)       # fetch top item from stack
    addi    sp, sp, 4       # increment stack to decrease size
    jr      t0              # jump to the previous ra value (return from original function call)

uart_rx:    # UART polling loops (no interrupts yet :/), only sends lower byte, doesnt modify a0 at all
    li      t1, DEFAULT_TIMEOUT_CYCLE
    beqz    a4, 1f          # a4 is custom timeout parameter, if its already zeroed out, then use default (jump to 1 directly)
    li      t1, a4          # load custom timeout if doesn't skip
1:
    lbu     t0, 0(s1)       # load UART status byte
    addi    t1, t1, -1      # decrement timeout checker
    beqz    t1, timeout_handler
    andi    t0, t0, 0x01    # mask only bit 1 (RX VALID)
    beqz    t0, 1b          # loop back while uart status is 0 (not yet valid)
    lbu     a0, 0(s2)       # load data byte once status is nonzero (valid byte ready)
    addi    a4, x0, 0       # clear a4 to default value again, a4 must be explicitly set when its to be called
    ret

uart_tx:    # NOTE: no need for safety checker here, as its BIOS side, cannot timeout ideally
1:
    lbu     t0, 0(s1)       # load UART status byte
    andi    t0, t0, 0x02    # mask only bit 2 (TX BUSY)
    bnez    t0, 1b          # wait till valid (until tx_busy != 1)
    sb      a0, 0(s3)       # send data via UART channel once no longer busy
    ret

# BIOS Functions

send_word:  # sent in little endian order, return the original word too
    li      t0, 4           # 4 bytes per word
    mv      t1, a0          # temporarily store original word
1:  
    call    uart_rx         # send lower byte
    srli    a0, a0, 8       # shift right one byte
    addi    t0, t0, -1      # subtract once from loop variable
    bnez    t0, 1b          # go back if not yet zero (loop 4 times)
    mv      a0, t1          # move word back to a0 to return for reuse
    call    pop_addr
    ret

get_word:   # little endian 4 byte word
    addi    t0, x0, 4       # loop 4 times for 4 bytes
    addi    t1, x0, 0       # initialize shift counter to 0 bits
1:  
    call    uart_rx
    sll     t2, a0, t1      # shift new byte left by current shift counter (0 -> 8 -> 16 -> 24)
    or      t3, t3, t2      # merge the shifted byte into final reg
    addi    t1, t1, 8       # increment shift counter by 8 bits for the next byte
    addi    t0, t0, -1      # decrement shift loop counter
    bnez    t0, 1b          # go back if not yet 0

    mv      a0, t3          # move from temp register to return register
    call    pop_addr        # pop stack saved address
    ret

update_state:
    andi    a6, a6, 0xFF    # mask out lower byte of status update, in case
    andi    s10, s10, 0xFF  # clear lower bytes of status register
    or      s10, s0, a6     # load lower byte of a6 into s10 to update status
    andi    t1, s10, 0x00000200     # mask out 9th bit (status flush)
    beqz    t1, 1f          # if zero, then skip status flushing directly and return
    mv      t1, a0          # save existing return value (prevent return value loss from before)
    li      a0, FB_BIOSST_UPDT
    call    uart_tx         # update push update bios state
    mv      a0, a6          # push updated state as byte
    call    uart_tx       
1:
    call    pop_addr
    ret

mem_print:
    mv      t0, a0          # size
    mv      t1, a1          # offset
    call    push_addr
    call    check_size
    beqz    a0, 2f          # if size overflow
1:  
    lbu     a0, 0(t1)       # load byte from memory
    call    uart_tx         # send via uart tx
    addi    t0, t0, -1      # subtract 1 from size to reduce count
    addi    t1, t1, 1       # incremement offset pointer
    bnez    t0, 1b

    call    pop_addr    
    ret
2:
    li      a0, ERR_MEMORY
    li      a1, ERR_MEM_OUT_OF_BOUNDS
    j       error_handler

gets:
    call    uart_rx
    li      t0, TB_MSG_STR  # verify it is a string first
    bne     a0, t0, 3f      # jump to error handler if bytes not equal

    call    push_addr
    call    get_word
    mv      s4, a0          # string size, move into s4 temporarily to survive check_size
    call    push_addr
    call    check_size
    beqz    a0, 2f          # if message size too high, respective error  
    mv      t1, s4          # move size into t1
    mv      t0, a1          # move pointer into t0, a1 returns the offset pointer to be used by a potential puts later
1:
    call    uart_rx
    sb      a0, 0(t0)       # store to pointer
    addi    t0, t0, 1       # incrememnt pointer
    addi    t1, t1, -1      # decrement counter
    bnez    t1, 1b          # loop as long as counter is not zero

    mv      a0, s4          # return size (saved in s4 earlier)
    call    pop_addr
    ret
2:
    li      a0, ERR_MESSAGE             # load a0 for error handler type indicator
    li      a1, ERR_GET_MSG_TOO_BIG     # load a1 for error handler exact type
    j       error_handler
3: 
    li      a0, ERR_MESSAGE
    li      a1, ERR_GET_MSG_UNVERIFIED  # unverified get message
    j       error_handler

puts:
    mv      s4, a0          # string size 
    call    push_addr
    call    check_size
    beqz    a0, 2f          # if message size is too high (as returned by check_size), raise error
    mv      t1, s4          # move size into t1
    mv      t0, a1          # move pointer into t0

    li      a0, FB_MSG_STR  # only start trasmitting the string after verifying tramissibility
    call    uart_tx         # start with transmitting 0x3D prefix string byte
1:
    lb      a0, 0(t0)       # load byte from pointer to register
    call    uart_tx         # send via tx
    addi    t0, t0, 1       # increment pointer
    addi    t1, t1, -1      # decrement counter
    bnez    t1, 1b          # loop as long as counter is not zero

    call    pop_addr
    ret
2:
    li      a0, ERR_MESSAGE
    li      a1, ERR_OUT_MSG_TOO_BIG
    j       error_handler

check_size:
    li      t0, bios_data_top           # top address for BIOS data (end of stack)
    sub     t1, t0, a1                  # subtract offset pointer address from top address to get remaining size
    bltz    t1, 1f                      # ensure that pointer is not greater than max allowed address
    slt     a0, a0, t1                  # (compare addresses) if message size too high, return result as 0 (fail), else return as 1
2:
    call    pop_addr
    ret
1:
    li      a0, 0
    j       2b                          # error raised if offset is higher than allocated memory top


# HANDLERS
timeout_handler:    # uses a5 for checking handler type
    bnez    a7, 2f                              # if it was in idle state, skip transmitting timeout errors
    beqz    a5, 1f                              # if zero, use default handler
    addi    t1, a5, -1                          # check for if 1
    beqz    t1, connection_timeout_handler      # if 1, use connection timeout handler
    j       critical_error                      # must match a handler, critical error otherwise
1:
    li      a0, ERR_BIOS                # bios timeout error type
    call    uart_tx
    li      a0, ERR_BIOS_TIMEOUT        # bios timeout error code
    call    uart_tx
2:
    j       idle
# ^^^ DEVELOPERS NOTE: this current implementation is used as there are no RX/TX FIFOs that allow staging multiple bytes at once
# said feature will be added in the near future as an upgrade

connection_timeout_handler:     # specifically for connection timeout
    li      a0, ERR_BIOS        # error type
    call    uart_tx
    li      a0, ERR_CONNNECT    # error code
    call    uart_tx
    j       idle

error_handler:
    call    uart_tx     # call tx with error type in a0
    mv      a0, a1      # move a1 (error code) to a0 for calling tx agagin
    call    uart_tx     # call tx with error code, now in a0
    j       idle        # jump back to idle state after error handling

critical_error:     # generally meant for BIOS-side errors
    li      a0, ERR_CRITICAL    # load 0xEE for ciritcal error transmission to master device
    call    uart_tx
    j reset

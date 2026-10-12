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
# t0-t6 - temporary function-specific variables
# s0-s11 - global/high-lifetime variables
    # s1 - UART status
    # s2 - UART RX DATA
    # s3 - UART TX DATA
    # s10 - BIOS Status Register
        # [7:0]: BIOS Status Byte
        # [8]: BIOS Connection Valid
        # [9]: BIOS Status Flush (State logging)
        # [10]: BIOS Telemetry Enable
        # [11]: Program Telemetry Enable
        # [12]: Program Telemetry Reset
    # s11 - Program Start Offset

# MEMORY LAYOUT:
# 0x00000000 - 0x00000FFF: BIOS ROM
# 0x00001000 - 0x0001FFFF: PROGRAM SPACE (PROGRAM STACK DEFAULT: 0x00020000)
# 0x00020000 - 0x00020FBF: BIOS DATA SPACE
# 0x00020FC0 - 0x00021000: BIOS STACK (allocate 64 bytes (16 words) space for BIOS stack)

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

# BIOS UTILITY
reset:
    # initialize BIOS constants (UART mainly)
    la      s1, UART_STATUS             # s1 - UART STATUS
    addi    s2, s1, UART_RXD_OFFSET     # s2 - UART RX DATA
    addi    s3, s1, UART_TXD_OFFSET     # s3 - UART TX DATA

    la      sp, bios_stack_top      # initialize stack
    addi    a4, x0, 0               # clear a4 register to prevent interference with UART rx timer (see uart_rx: label below)

idle:
    li      a5, BIOSST_IDLE
    call    push_addr
    call    update_state            # update state to idle

    call    uart_rx                 # call uart rx in idle to receive command
    mv      t0, a0                  # move result to t0 scratch reg
    
    # conditional switch table for all different intiialization bytes
    li      t1, TB_MSG_ECHO         # check msg echo byte
    beq     t0, t1, msg_echo
    li      t1, TB_ST_INIT          # check self test init
    beq     t0, t1, self_test
    li      t1, TB_META_START       # check telemetry display innit
    beq     t0, t1, telemetry
    li      t1, TB_MEM_DUMP         # memory dump
    beq     t0, t1, memory
    li      t1, TB_NET_ACK          # connection attempt
    beq     t0, t1, connect
    li      t1, TB_DD_DATA          # check device data request
    beq     t0, t1, device_data
    li      t1, TB_BIOS_DATA        # check if BIOS data monitoring is turned on
    beq     t0, t1, bios_log

    j       idle                    # loop around if no valid command bytes, no error 

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

self_test:

telemetry:
    li      a6, BIOSST_META
    call    push_addr
    call    update_state    # update state

    li      t1, 4           # for four possible arguments (bios tele, prog tele, inst telereset, prog telereset)
1:
    call    uart_rx         # get byte
    li      t0, TB_META_BIOSTR
    beq     a0, t0, 3f      # BIOS telemetry tracking
    li      t0, TB_META_PRGTR
    beq     a0, t0, 4f      # program telemetry tracking
    li      t0, TB_META_PRGRST
    beq     a0, t0, 5f      # program telemetry reset
    li      t0, TB_META_RESET
    beqz    a0, t0, 7f      # instant reset telemetry now
    j       2f              # invalid argument
3:
    li      t1, 10          # 10 is s10 bit number for option bios telemetry tarcking
    j       6f
4:
    li      t1, 11          # 11 is s10 bit number for option bios telemetry tarcking
    j       6f
5:
    li      t1, 12          # 12 is s10 bit number for option bios telemetry tarcking
    j       6f
6:
    li      t0, 1
    slli    t0, t0, t1      # shift the '1' to the amount set by the previous label to mask said bit
    call    
7:
    li      t0, ADDR_META_CONTROL   # meta control byte address
    lbu     t1, 0(t0)               # get current meta control status
    nop                             # load use stall
    mv      t2, t1                  # save status in t1
    ori     t1, t1, 0x01            # LSB is reset, assert high
    sb      t1, 0(t0)               # store it
    nop                             # nop for stability (may be removed later)
    sb      t2, 0(t0)               # store original status back again to finish reset assertion
    
    j       1b
2:
    li      a0, ERR_TELEMETRY
    li      a1, ERR_META_ARG_INVALID
    j       error_handler

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
    call    pop_addr
    ret
1:
    j       critical_error              # critical error raised if offset is higher than allocated memory top


# HANDLERS
timeout_handler:    # uses a5 for checking handler type
    beqz    a5, 1f                              # if zero, use default handler
    addi    t1, a5, -1                          # check for if 1
    beqz    t1, connection_timeout_handler      # if 1, use connection timeout handler
    j       critical_error                      # must match a handler, critical error otherwise
1:
    li      a0, ERR_BIOS                # bios timeout error type
    call    uart_tx
    li      a0, ERR_BIOS_TIMEOUT        # bios timeout error code
    call    uart_tx
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

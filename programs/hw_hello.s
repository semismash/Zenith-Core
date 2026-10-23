# hw_hello - CPU bring-up test for the board: no stack, no RAM, no BIOS, no loads except the UART status.
# Prints  ABCDEFGHIJKLMNOPQRSTUVWXYZ<CR><LF>  over the UART, forever. Uses fetch from ROM, ALU, branches, one MMIO load
# (status) and one MMIO store (tx data) - if this prints correctly, the core, the ROM initialisation and the UART MMIO work
# on the real board.
#
#   make rom-asm PROG=hw_hello
#   make fpga FPGA_ROM=build/programs/hw_hello.rom.hex FPGA_NAME=hw_hello
#   make fpga-program FPGA_NAME=hw_hello
        .text
        .global _start
_start:
        lui     t0, 0x80000             # t0 = 0x80000000: UART status at +0 (bit 1 = tx busy), tx data at +8
again:
        li      t2, 65                  # 'A'
letter:
1:      lbu     t1, 0(t0)
        andi    t1, t1, 2
        bnez    t1, 1b                  # wait until the transmitter is idle
        sb      t2, 8(t0)               # send the letter
        addi    t2, t2, 1
        li      t3, 91                  # one past 'Z'
        bne     t2, t3, letter
2:      lbu     t1, 0(t0)
        andi    t1, t1, 2
        bnez    t1, 2b
        li      t4, 13                  # CR
        sb      t4, 8(t0)
3:      lbu     t1, 0(t0)
        andi    t1, t1, 2
        bnez    t1, 3b
        li      t4, 10                  # LF
        sb      t4, 8(t0)
        j       again

# Bootloader test 1: register values (use with the register display option)
# Load at the default offset 0x2000 (assemble with TEXT_BASE=0x2000 AUTO_STOP=0), no ebreak: the BIOS appends a
# jump-back tail after the last instruction, so the program just runs off its end.
#
# Expected register dump afterwards (the other registers still hold BIOS values, do not check them):
#   x5  t0 = 0x00001234     x6  t1 = 0x0000beef     x7  t2 = 0x0000d123
#   x10 a0 = 0x12345678     x11 a1 = 0x23456780     x12 a2 = 0x317131f8     x13 a3 = 0x12344444
#   x14 a4 = 0x00000037     x15 a5 = 0x00000000
#   x28 t3 = 0x00010000     x29 t4 = 0xcafef00d     x30 t5 = 0xcafef00d
#   x2  sp = 0x00021000 (the BIOS sets it before the jump)
#   x1  ra = 0x2000 + program size (the address of the jump-back tail)
#   x31 t6 always reads 0 in the dump (the BIOS uses it as the dump pointer)
# and memory at 0x10000 = 0xcafef00d (check with a memory dump)
        .text
        .global _start
_start:
        li      t0, 0x1234
        li      t1, 0xBEEF
        add     t2, t0, t1              # 0xd123

        li      a0, 0x12345678
        slli    a1, a0, 4               # 0x23456780
        xor     a2, a0, a1              # 0x317131f8
        sub     a3, a0, t0              # 0x12344444

        li      a4, 0                   # sum 1..10 with a loop and a backward branch
        li      a5, 10
1:      add     a4, a4, a5
        addi    a5, a5, -1
        bnez    a5, 1b                  # a4 = 55 = 0x37, a5 = 0

        li      t3, 0x10000             # store + load through RAM
        li      t4, 0xCAFEF00D
        sw      t4, 0(t3)
        lw      t5, 0(t3)               # 0xcafef00d

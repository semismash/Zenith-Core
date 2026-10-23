# hw_post - POST-style CPU test for the board: no BIOS, no stack until the stack test, results printed over the UART.
# Runs the same kinds of operations the BIOS's own self test uses, but each stage reports separately:
#   R registers   A ALU   C control flow (branches, jal, jalr, la)   D data reads from the ROM   M RAM (word, byte, halfword)   S stack
# Output, repeated forever:   R:P A:P C:P D:P M:P S:P <CR><LF>      (P = pass, F = fail)
#
#   make rom-asm PROG=hw_post
#   make fpga FPGA_ROM=build/programs/hw_post.rom.hex FPGA_NAME=hw_post
#   make fpga-program FPGA_NAME=hw_post
# then read COM5 at 9600 8N1 (the board runs it right after programming, RESET restarts it).
        .text
        .global _start

# transmit the byte in register \r (waits for the UART first); needs s11 = 0x80000000, clobbers s10
        .macro putc r
1:      lbu     s10, 0(s11)
        andi    s10, s10, 2
        bnez    s10, 1b
        sb      \r, 8(s11)
        .endm

# prints  <letter>:<P or F><space>  from s0 (0 = pass); \code is the ASCII code of the letter
        .macro pf code
        li      t0, \code
        putc    t0
        li      t0, 58                  # ':'
        putc    t0
        li      t0, 80                  # 'P'
        beqz    s0, 2f
        li      t0, 70                  # 'F'
2:      putc    t0
        li      t0, 32                  # ' '
        putc    t0
        .endm

_start:
# ------------------------------------------------------------------------------------------ R: registers
# phase A: x1..x15 get the pattern N*65, checked with x16 as the scratch register

        li      x1, 65
        li      x2, 130
        li      x3, 195
        li      x4, 260
        li      x5, 325
        li      x6, 390
        li      x7, 455
        li      x8, 520
        li      x9, 585
        li      x10, 650
        li      x11, 715
        li      x12, 780
        li      x13, 845
        li      x14, 910
        li      x15, 975
        li      x16, 65
        bne     x1, x16, reg_fail
        li      x16, 130
        bne     x2, x16, reg_fail
        li      x16, 195
        bne     x3, x16, reg_fail
        li      x16, 260
        bne     x4, x16, reg_fail
        li      x16, 325
        bne     x5, x16, reg_fail
        li      x16, 390
        bne     x6, x16, reg_fail
        li      x16, 455
        bne     x7, x16, reg_fail
        li      x16, 520
        bne     x8, x16, reg_fail
        li      x16, 585
        bne     x9, x16, reg_fail
        li      x16, 650
        bne     x10, x16, reg_fail
        li      x16, 715
        bne     x11, x16, reg_fail
        li      x16, 780
        bne     x12, x16, reg_fail
        li      x16, 845
        bne     x13, x16, reg_fail
        li      x16, 910
        bne     x14, x16, reg_fail
        li      x16, 975
        bne     x15, x16, reg_fail
# phase B: x16..x31, checked with x1 as the scratch register (x1 was verified in phase A)
        li      x16, 1040
        li      x17, 1105
        li      x18, 1170
        li      x19, 1235
        li      x20, 1300
        li      x21, 1365
        li      x22, 1430
        li      x23, 1495
        li      x24, 1560
        li      x25, 1625
        li      x26, 1690
        li      x27, 1755
        li      x28, 1820
        li      x29, 1885
        li      x30, 1950
        li      x31, 2015
        li      x1, 1040
        bne     x16, x1, reg_fail
        li      x1, 1105
        bne     x17, x1, reg_fail
        li      x1, 1170
        bne     x18, x1, reg_fail
        li      x1, 1235
        bne     x19, x1, reg_fail
        li      x1, 1300
        bne     x20, x1, reg_fail
        li      x1, 1365
        bne     x21, x1, reg_fail
        li      x1, 1430
        bne     x22, x1, reg_fail
        li      x1, 1495
        bne     x23, x1, reg_fail
        li      x1, 1560
        bne     x24, x1, reg_fail
        li      x1, 1625
        bne     x25, x1, reg_fail
        li      x1, 1690
        bne     x26, x1, reg_fail
        li      x1, 1755
        bne     x27, x1, reg_fail
        li      x1, 1820
        bne     x28, x1, reg_fail
        li      x1, 1885
        bne     x29, x1, reg_fail
        li      x1, 1950
        bne     x30, x1, reg_fail
        li      x1, 2015
        bne     x31, x1, reg_fail
# x0 must ignore writes
        addi    x0, x0, 5
        bnez    x0, reg_fail
        li      s0, 0
        j       reg_done
reg_fail:
        li      s0, 1
reg_done:
        lui     s11, 0x80000            # UART base, the register test clobbered everything
        pf      82                      # 'R'

# ------------------------------------------------------------------------------------------ A: ALU
        li      s0, 1                   # assume fail, cleared at the end of the stage
        li      t0, 5
        li      t1, 3
        add     t2, t0, t1
        li      t3, 8
        bne     t2, t3, alu_done
        li      t0, 0x7FFFFFFF
        li      t1, 1
        add     t2, t0, t1
        li      t3, 0x80000000
        bne     t2, t3, alu_done
        li      t0, 0xF0F0F0F0
        li      t1, 0x0F0F0F0F
        and     t2, t0, t1
        bnez    t2, alu_done
        or      t2, t0, t1
        li      t3, 0xFFFFFFFF
        bne     t2, t3, alu_done
        xor     t2, t0, t1
        bne     t2, t3, alu_done
        li      t0, 0x80000001
        srli    t2, t0, 4
        li      t3, 0x08000000
        bne     t2, t3, alu_done
        srai    t2, t0, 4
        li      t3, 0xF8000000
        bne     t2, t3, alu_done
        slli    t2, t0, 4
        li      t3, 0x00000010
        bne     t2, t3, alu_done
        li      t0, -1
        li      t1, 1
        slt     t2, t0, t1
        li      t3, 1
        bne     t2, t3, alu_done
        sltu    t2, t0, t1
        bnez    t2, alu_done
        sub     t2, t1, t0              # 1 - (-1) = 2
        li      t3, 2
        bne     t2, t3, alu_done
        li      s0, 0
alu_done:
        pf      65                      # 'A'

# ------------------------------------------------------------------------------------------ C: control flow
        li      s0, 1
        li      t0, 5
        li      t1, 5
        beq     t0, t1, 1f
        j       ctl_done
1:      li      t1, 6
        beq     t0, t1, ctl_done        # must not be taken
        li      t0, 3
        li      t1, 7
        blt     t0, t1, 2f
        j       ctl_done
2:      li      t0, 7
        li      t1, 3
        blt     t0, t1, ctl_done        # must not be taken
        bge     t0, t1, 3f
        j       ctl_done
3:      jal     ra, ctl_jal_target
        j       ctl_jal_check
ctl_jal_target:
        jr      ra
ctl_jal_check:
        la      t0, ctl_jalr_target
        jalr    ra, t0, 0
        j       ctl_pass
ctl_jalr_target:
        jr      ra
ctl_pass:
        li      s0, 0
ctl_done:
        pf      67                      # 'C'

# ------------------------------------------------------------------------------------------ D: data reads from the ROM
        li      s0, 1
        la      t0, rom_const
        lw      t1, 0(t0)
        li      t2, 0x12345678
        bne     t1, t2, rom_done
        lbu     t1, 0(t0)               # little endian: byte 0 = 0x78
        li      t2, 0x78
        bne     t1, t2, rom_done
        lhu     t1, 2(t0)               # halfword at +2 = 0x1234
        li      t2, 0x1234
        bne     t1, t2, rom_done
        li      s0, 0
rom_done:
        pf      68                      # 'D'

# ------------------------------------------------------------------------------------------ M: RAM (0x2000 .. 0x21FFF)
        li      s0, 1
        li      t0, 0x2000
        li      t1, 0xA1A1A1A1
        sw      t1, 0(t0)
        lw      t2, 0(t0)
        bne     t1, t2, mem_done
        li      t0, 0x9000
        li      t1, 0xB2B2B2B2
        sw      t1, 0(t0)
        lw      t2, 0(t0)
        bne     t1, t2, mem_done
        li      t0, 0x11000
        li      t1, 0xC3C3C3C3
        sw      t1, 0(t0)
        lw      t2, 0(t0)
        bne     t1, t2, mem_done
        li      t0, 0x20FFC
        li      t1, 0xD4D4D4D4
        sw      t1, 0(t0)
        lw      t2, 0(t0)
        bne     t1, t2, mem_done
        li      t0, 0x2000
        li      t1, 0x5A
        sb      t1, 0(t0)
        lb      t2, 0(t0)
        bne     t1, t2, mem_done
        li      t0, 0x2004
        li      t1, 0x1234
        sh      t1, 0(t0)
        lh      t2, 0(t0)
        bne     t1, t2, mem_done
        li      t0, 0x2000              # the byte store must not have touched its neighbours
        lw      t2, 0(t0)
        li      t1, 0xA1A1A15A
        bne     t1, t2, mem_done
        li      s0, 0
mem_done:
        pf      77                      # 'M'

# ------------------------------------------------------------------------------------------ S: stack
        li      s0, 1
        li      sp, 0x22000
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
        bne     t3, t2, stk_done
        addi    sp, sp, 4
        lw      t3, 0(sp)
        bne     t3, t1, stk_done
        addi    sp, sp, 4
        lw      t3, 0(sp)
        bne     t3, t0, stk_done
        addi    sp, sp, 4
        li      t4, 0x22000
        bne     sp, t4, stk_done
        li      s0, 0
stk_done:
        pf      83                      # 'S'

        li      t0, 13                  # CR
        putc    t0
        li      t0, 10                  # LF
        putc    t0
        j       _start

rom_const:
        .word   0x12345678

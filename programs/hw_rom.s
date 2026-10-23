# hw_rom - tests the SECOND block RAM tile of the ROM (bytes 0x1000..0x1FFF), which the BIOS uses but the small test programs never touch.
# The ROM is 2048 words = two 1024-word block RAM tiles; this program executes code and reads data in both.
# Output, repeated forever:   L H D K <CR><LF>   as the letters  LHDK  (lowercase = that check failed)
#   L  code executes from the lower tile        H  code executes from the upper tile (a jump across the tile boundary)
#   D  a data read from the upper tile is right K  a data read from the lower tile is right
#
#   make rom-asm PROG=hw_rom
#   make fpga FPGA_ROM=build/programs/hw_rom.rom.hex FPGA_NAME=hw_rom
#   make fpga-program FPGA_NAME=hw_rom
        .text
        .global _start

        .macro putc r
1:      lbu     s10, 0(s11)
        andi    s10, s10, 2
        bnez    s10, 1b
        sb      \r, 8(s11)
        .endm

_start:
        lui     s11, 0x80000            # UART base
        li      t0, 76                  # 'L'
        putc    t0
        j       high_code
low_const:
        .word   0x0BADF00D

        .org    0x1100                  # byte 0x1100 = word 1088, inside the second tile

high_code:
        li      t0, 72                  # 'H'
        putc    t0
        la      t1, high_const
        lw      t2, 0(t1)               # data port, upper tile
        li      t3, 0xCAFEF00D
        li      t0, 68                  # 'D'
        beq     t2, t3, 1f
        li      t0, 100                 # 'd'
1:      putc    t0
        la      t1, low_const
        lw      t2, 0(t1)               # data port, lower tile
        li      t3, 0x0BADF00D
        li      t0, 75                  # 'K'
        beq     t2, t3, 2f
        li      t0, 107                 # 'k'
2:      putc    t0
        li      t0, 13                  # CR
        putc    t0
        li      t0, 10                  # LF
        putc    t0
        j       _start
high_const:
        .word   0xCAFEF00D

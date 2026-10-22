# Bootloader test 2: memory writes (check with a memory dump afterwards, no register display needed)
# Writes 16 words to 0x10100: 0x01010101, 0x02020202, ... 0x10101010
        .text
        .global _start
_start:
        li      t0, 0x10100             # destination
        li      t1, 0                   # running value
        li      t2, 0x01010101          # step
        li      t3, 16                  # word count
1:      add     t1, t1, t2
        sw      t1, 0(t0)
        addi    t0, t0, 4
        addi    t3, t3, -1
        bnez    t3, 1b

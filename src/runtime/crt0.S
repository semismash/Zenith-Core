/* Zenith Core - C startup, entered by the BIOS at the first byte of the loaded image.
 *
 * What the BIOS hands over: sp = 0x21000 (top of program space, 16-byte aligned) and ra = address of the 8-byte
 * jump-back tail it appended after the image. Returning through ra gives control back to the BIOS, which then sends
 * the "program done" state and, if requested, the register dump (a0 = main's return value shows up there).
 * Everything else, including s0-s11, still holds BIOS values: main() preserves the callee-saved ones by the C ABI.
 *
 * NOTE: no '#' comments in this file, it goes through the C preprocessor.
 */
        .section .text.start,"ax",@progbits
        .globl  _start
        .type   _start,@function
_start:
        addi    sp, sp, -16
        sw      ra, 12(sp)              /* the BIOS tail address */

        la      t0, __bss_start         /* zero .bss (linker script puts it clear of the BIOS tail) */
        la      t1, __bss_end
1:      bgeu    t0, t1, 2f
        sw      zero, 0(t0)
        addi    t0, t0, 4
        j       1b

2:      call    main                    /* a0 = return value */

        lw      ra, 12(sp)
        addi    sp, sp, 16
        ret
        .size   _start, . - _start

/* Zenith Core - linker script for programs loaded through the BIOS.
 *
 * The whole image (code + read-only data + initialised data) is loaded by the BIOS at PRG_BASE (default 0x2000) and
 * runs from there; program space is RAM, so .rodata and .data need no copying. .bss is not part of the image: crt0
 * zeroes it. It starts 8+ bytes after the end of the image because the BIOS writes its jump-back tail right there.
 *
 *   PRG_BASE / PRG_TOP can be overridden with  -Wl,--defsym=PRG_BASE=0x3000  (the makefile does that for TEXT_BASE=...)
 *   Programs are only valid at the address they were linked for, load them at that offset.
 */
OUTPUT_ARCH(riscv)
ENTRY(_start)

PRG_BASE_ADDR = DEFINED(PRG_BASE) ? PRG_BASE : 0x2000;
PRG_TOP_ADDR  = DEFINED(PRG_TOP)  ? PRG_TOP  : 0x21000;
MIN_STACK     = 0x400;                          /* refuse to link if less than 1 KiB is left for the stack */

SECTIONS
{
    . = PRG_BASE_ADDR;

    .text : ALIGN(4) {
        KEEP(*(.text.start))                    /* _start must be the very first instruction of the image */
        *(.text .text.*)
        . = ALIGN(4);
    }

    .rodata : ALIGN(4) {
        *(.rodata .rodata.* .srodata .srodata.*)
        . = ALIGN(4);
    }

    .data : ALIGN(4) {
        *(.data .data.* .sdata .sdata.*)
        . = ALIGN(4);
    }

    __image_end = .;                            /* image size is a multiple of 4, the BIOS requires that */

    . = ALIGN(__image_end + 8, 16);             /* keep clear of the BIOS jump-back tail */
    __bss_start = .;                            /* outside the section: still defined (and equal) if there is no .bss */
    .bss (NOLOAD) : {
        *(.sbss .sbss.* .bss .bss.* COMMON)
        . = ALIGN(4);
    }
    __bss_end = .;

    __stack_top = PRG_TOP_ADDR;

    /DISCARD/ : { *(.comment) *(.note*) *(.eh_frame*) }
}

ASSERT(__image_end + 8 <= PRG_TOP_ADDR, "program image does not fit into program space")
ASSERT(__bss_end + MIN_STACK <= PRG_TOP_ADDR, "image + .bss leave less than 1 KiB for the stack")

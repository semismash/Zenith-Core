/* Zenith Core BIOS linker script
 * Memory map (must match bios.s and rv32i.sv):
 *   0x00000000 - 0x00001FFF  ROM, 8 KiB: BIOS code + read-only data (fetchable and readable as data, not writable)
 *   0x00002000 - 0x00021FFF  RAM, 128 KiB: program space, BIOS data space and BIOS stack (laid out by bios.s itself)
 *   0x80000000 -             MMIO (handled by the LSU, never part of the image)
 * The BIOS keeps no initialised or zeroed variables (.data/.bss): its state lives in registers and at fixed
 * RAM addresses, so everything goes into ROM and nothing needs copying at boot.
 */
OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
    ROM (rx)  : ORIGIN = 0x00000000, LENGTH = 8K
    RAM (rwx) : ORIGIN = 0x00002000, LENGTH = 128K
}

SECTIONS
{
    /* reset vector: the CPU starts fetching at 0x0, which must be _start */
    .text 0x00000000 :
    {
        KEEP(*(.text.start))      /* optional: a .text.start section, if one is ever added, goes first */
        *(.text .text.*)
    } > ROM

    /* strings and constant words read by the BIOS through the ROM data port (also the R1 tail stubs live in .text) */
    .rodata : ALIGN(4)
    {
        *(.rodata .rodata.* .srodata .srodata.*)
    } > ROM

    /* the BIOS must not have writable data: nothing would copy it from ROM into RAM */
    .data (NOLOAD) : { *(.data .data.* .sdata .sdata.*) } > RAM
    .bss  (NOLOAD) : { *(.bss .bss.* .sbss .sbss.* COMMON) } > RAM

    /DISCARD/ : { *(.comment) *(.note .note.*) *(.eh_frame .eh_frame_hdr) }
}

ASSERT(_start == 0x00000000, "_start must be the first instruction at the reset vector (0x0)")
ASSERT(SIZEOF(.data) == 0, "BIOS has initialised .data, which would never be copied into RAM")
ASSERT(SIZEOF(.bss) == 0, "BIOS has .bss, which nothing zeroes")
/* the ROM region (8 KiB) overflowing is reported by the linker as "region `ROM' overflowed" */

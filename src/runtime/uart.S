/* Zenith Core - UART polling stubs, plain RV32I, C ABI (ilp32).
 *
 * Leaf functions: they use only a0-a1 and t0-t3, never touch the stack, s0-s11, gp or tp.
 *
 * UART MMIO (mmio_interface.sv / bios.s):
 *   0x80000000  status   bit 0 = rx_valid, bit 1 = tx_busy
 *   0x80000004  rx data  a read pops the byte
 *   0x80000008  tx data  write-only; a write while busy is silently ignored, so poll first
 *
 * NOTE: no '#' comments in this file, it goes through the C preprocessor.
 */

        .equ    UART_BASE,          0x80000000
        .equ    UART_RXD_OFF,       4
        .equ    UART_TXD_OFF,       8
        .equ    DEFAULT_TIMEOUT,    50000000

/* Cycles one FAILED poll of z_uart_rx takes on the current pipeline: 6 instructions (lbu, andi, bnez, bltu, sub, j)
 * + 1 load-use stall (lbu -> andi) + 2 for the taken j = 9. It is the unit the timeout is counted in. If the pipeline
 * changes (branch prediction!), measure again with the telemetry counters and adjust this one number. */
        .equ    Z_POLL_CYCLES,      9

        .text

/* int z_uart_rx(uint8_t *byte /a0/, uint32_t timeout /a1/)       returns 0 = got a byte, -1 = timed out */
        .section .text.z_uart_rx,"ax",@progbits
        .globl  z_uart_rx
        .type   z_uart_rx,@function
z_uart_rx:
        li      t0, UART_BASE
        li      t3, Z_POLL_CYCLES       /* cost of one failed poll, 0 means "never time out" */
        bnez    a1, 1f
        li      a1, DEFAULT_TIMEOUT     /* timeout 0 selects the default */
1:      li      t2, -1
        bne     a1, t2, 2f
        li      t3, 0                   /* 0xFFFFFFFF = forever: nothing is subtracted and a1 is never below 0 */
2:      lbu     t1, 0(t0)               /* status */
        andi    t1, t1, 1               /* rx_valid */
        bnez    t1, 4f
        bltu    a1, t3, 3f              /* remaining < cost of another poll: give up */
        sub     a1, a1, t3
        j       2b
3:      li      a0, -1
        ret
4:      lbu     t1, UART_RXD_OFF(t0)    /* the read pops the byte, so it happens exactly once */
        sb      t1, 0(a0)
        li      a0, 0
        ret
        .size   z_uart_rx, . - z_uart_rx

/* void z_uart_tx(uint8_t byte /a0/) */
        .section .text.z_uart_tx,"ax",@progbits
        .globl  z_uart_tx
        .type   z_uart_tx,@function
z_uart_tx:
        li      t0, UART_BASE
1:      lbu     t1, 0(t0)
        andi    t1, t1, 2               /* tx_busy */
        bnez    t1, 1b
        sb      a0, UART_TXD_OFF(t0)
        ret
        .size   z_uart_tx, . - z_uart_tx

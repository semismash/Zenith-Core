/* Zenith Core - C runtime header
 *
 *   #include "zenith.h"
 *
 * Two assembly stubs (uart.S) do the raw UART access, everything else is plain C on top of them (zenith.c):
 *
 *   int      z_uart_rx(uint8_t *byte, uint32_t timeout);     assembly, polling receive
 *   void     z_uart_tx(uint8_t byte);                         assembly, polling transmit
 *   int32_t  z_gets(char *buf, int32_t max_size, uint32_t timeout);   one framed message in    (zenith.c)
 *   int32_t  z_puts(const char *buf, uint32_t size);                  one framed message out   (zenith.c)
 *
 * Message frame, the same one the BIOS and the CLI speak (see protocol.inc):
 *
 *     0x3D | size (4 bytes, little endian) | size data bytes                (host -> program, read by z_gets)
 *     0x3D | size (4 bytes, little endian) | size data bytes | 0x3F         (program -> host, written by z_puts)
 *
 * The CLI ignores its protocol bytes (0xF0 state frames etc.) while a frame's payload is in flight, so a payload may
 * contain any byte value. The size field is the only length, there is no NUL handling anywhere: a terminating NUL is
 * data like any other byte and has to be counted in size if the sender wants it transmitted.
 * Raw z_uart_tx() bytes outside a frame ARE seen by the CLI as protocol bytes, use z_puts() for text.
 */
#ifndef ZENITH_H
#define ZENITH_H

#include <stddef.h>
#include <stdint.h>

/* ------------------------------------------------------------------------------------------------ constants */
#define Z_MSG_STR             0x3Du         /* frame start byte (FB_MSG_STR / TB_MSG_STR)          */
#define Z_MSG_FLSH            0x3Fu         /* frame end byte sent by z_puts (FB_MSG_FLSH)         */

#define Z_UART_DEFAULT_TIMEOUT 50000000u    /* timeout 0 means this many cycles (5 s at 10 MHz)     */
#define Z_UART_FOREVER         0xFFFFFFFFu  /* timeout value: never give up                          */

/* ------------------------------------------------------------------------------------------------ error codes
 * returned by z_gets() and z_puts(); anything >= 0 is success.
 *
 *   Z_E_TIMEOUT  -1  z_gets:  a byte did not arrive within `timeout` (header or payload, nothing more is read).
 *   Z_E_NOT_MSG  -2  z_gets:  the first byte was not 0x3D. That one byte HAS been consumed from the receiver.
 *   Z_E_SIZE     -3  z_gets:  announced size is larger than max_size (or does not fit an int32_t). The payload was
 *                             drained and discarded so the stream stays in sync. The drain never waits longer than
 *                             Z_UART_DEFAULT_TIMEOUT per byte; if it ran into that timeout the stream may be out of sync.
 *   Z_E_ARG      -4  z_gets:  buf is NULL or max_size <= 0.      z_puts: buf is NULL.   (nothing was read / sent)
 *   Z_E_ZERO     -5  z_gets:  the sender announced size 0 (only the 5 header bytes were consumed).
 *                    z_puts:  size == 0                           (nothing was sent)
 */
#define Z_E_TIMEOUT  (-1)
#define Z_E_NOT_MSG  (-2)
#define Z_E_SIZE     (-3)
#define Z_E_ARG      (-4)
#define Z_E_ZERO     (-5)

/* ------------------------------------------------------------------------------------------------ assembly stubs
 * int z_uart_rx(uint8_t *byte, uint32_t timeout)
 *     Polls the UART until a byte arrives, stores it in *byte and returns 0. Returns -1 if `timeout` ran out first
 *     (*byte untouched). `timeout` counts approximate CPU cycles of polling (one failed poll is Z_POLL_CYCLES, see
 *     uart.S): 0 selects Z_UART_DEFAULT_TIMEOUT, Z_UART_FOREVER never times out.
 *     The UART has no receive FIFO: a second byte that arrives before the first was read overwrites it, so a
 *     program has to call this at least once per byte time (about 10400 cycles at 9600 baud).
 *
 * void z_uart_tx(uint8_t byte)
 *     Waits until the transmitter is idle, then hands `byte` to it and returns. The byte may still be on the wire
 *     when this returns.
 */
int  z_uart_rx(uint8_t *byte, uint32_t timeout);
void z_uart_tx(uint8_t byte);

/* ------------------------------------------------------------------------------------------------ framed messages
 * implemented in zenith.c */

/* Sends buf[0..size-1] as one frame: 0x3D, size (4 bytes LE), the data, 0x3F. Returns 0, or Z_E_ARG / Z_E_ZERO. */
int32_t z_puts(const char *buf, uint32_t size);

/* z_puts for a string literal: Z_PUTS_LIT("hello\n") sends 6 bytes, no NUL */
#define Z_PUTS_LIT(s) z_puts((s), (uint32_t)(sizeof(s) - 1u))

/* Receives one frame into buf. `timeout` is passed to z_uart_rx for every single byte. Returns the number of data
 * bytes stored (1 .. max_size, nothing is ever appended, no NUL), or one of the negative codes above. */
int32_t z_gets(char *buf, int32_t max_size, uint32_t timeout);

/* ------------------------------------------------------------------------------------------------ libc subset
 * implemented in libc_min.c, GCC emits calls to some of these on its own (struct copies, initialisers) */
#ifndef ZENITH_NO_LIBC_PROTOS
void  *memcpy(void *dst, const void *src, size_t n);
void  *memmove(void *dst, const void *src, size_t n);
void  *memset(void *dst, int c, size_t n);
int    memcmp(const void *a, const void *b, size_t n);
size_t strlen(const char *s);
#endif

#endif /* ZENITH_H */
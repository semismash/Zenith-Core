/* Zenith Core - C runtime: framed message I/O on top of the UART stubs (uart.S).
 * Documentation, frame format and error codes are in zenith.h. */
#include "zenith.h"

/* ------------------------------------------------------------------------------------------------ z_puts */
int32_t z_puts(const char *buf, uint32_t size)
{
    if (buf == NULL) return Z_E_ARG;
    if (size == 0)   return Z_E_ZERO;

    z_uart_tx(Z_MSG_STR);
    for (int i = 0; i < 4; i++) z_uart_tx((uint8_t)(size >> (8 * i)));
    for (uint32_t i = 0; i < size; i++) z_uart_tx((uint8_t)buf[i]);
    z_uart_tx(Z_MSG_FLSH);
    return 0;
}

/* ------------------------------------------------------------------------------------------------ z_gets */
int32_t z_gets(char *buf, int32_t max_size, uint32_t timeout)
{
    if (buf == NULL || max_size <= 0) return Z_E_ARG;

    uint8_t b;
    if (z_uart_rx(&b, timeout) != 0) return Z_E_TIMEOUT;
    if (b != Z_MSG_STR) return Z_E_NOT_MSG;

    uint32_t size = 0;
    for (int i = 0; i < 4; i++) {
        if (z_uart_rx(&b, timeout) != 0) return Z_E_TIMEOUT;
        size |= (uint32_t)b << (8 * i);
    }
    if (size == 0) return Z_E_ZERO;

    if (size > (uint32_t)max_size) {
        /* swallow the payload so the next z_gets() starts on a frame boundary; never wait forever for it */
        uint32_t dt = (timeout == 0 || timeout > Z_UART_DEFAULT_TIMEOUT) ? Z_UART_DEFAULT_TIMEOUT : timeout;
        for (uint32_t i = 0; i < size; i++) {
            if (z_uart_rx(&b, dt) != 0) break;
        }
        return Z_E_SIZE;
    }

    for (uint32_t i = 0; i < size; i++) {
        if (z_uart_rx(&b, timeout) != 0) return Z_E_TIMEOUT;
        buf[i] = (char)b;
    }
    return (int32_t)size;
}
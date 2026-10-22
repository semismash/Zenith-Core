/* c_timeout - calibrates and tests the z_uart_rx timeout.
 *
 *   make cprog PROG=c_timeout
 *   CLI:  load build/programs/c_timeout.hex -v -r --register=true --telereset=true --telemode=true     (send NOTHING while it runs)
 *         status
 *
 * z_uart_rx waits for a byte that never comes, so it must return -1 after about 1,000,000 cycles: a0 (x10) in the
 * register dump is 0xFFFFFFFF, and `status` should report roughly 1,000,000 clock cycles (a few hundred more for the
 * setup and the BIOS glue). If the cycle count is clearly off, change Z_POLL_CYCLES in src/runtime/uart.S:
 *     new Z_POLL_CYCLES = old Z_POLL_CYCLES * 1,000,000 / measured cycles
 */
#include "zenith.h"

int main(void)
{
    uint8_t b = 0;
    return z_uart_rx(&b, 1000000u);
}

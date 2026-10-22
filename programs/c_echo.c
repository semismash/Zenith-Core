/* c_echo - receives framed messages with z_gets and sends each one back with z_puts.
 *
 *   make cprog PROG=c_echo
 *   CLI:  load build/programs/c_echo.hex -v -r        then send frames with sendbytes:
 *         3D 05 00 00 00 68 65 6C 6C 6F          ->  the program answers "echo: hello"
 *         3D 04 00 00 00 71 75 69 74             ->  "quit" ends the program
 *   Errors are reported as "z_gets error -N". It also ends after the first timeout (default 50M cycles = 5 s of
 *   simulated time without a byte) and returns the number of messages it received.
 */
#include "zenith.h"

static char in[256];
static char out[6 + 256];

int main(void)
{
    Z_PUTS_LIT("c_echo: ready, send a framed message (3D, 4-byte size, data); \"quit\" ends\n");

    int32_t count = 0;
    for (;;) {
        int32_t n = z_gets(in, (int32_t)sizeof in, 0);
        if (n < 0) {
            static char err[] = "z_gets error -0\n";
            err[14] = (char)('0' + (-n));
            z_puts(err, (uint32_t)(sizeof err - 1u));
            if (n == Z_E_TIMEOUT) break;
            continue;
        }
        count++;
        if (n == 4 && memcmp(in, "quit", 4) == 0) break;

        memcpy(out, "echo: ", 6);
        memcpy(out + 6, in, (size_t)n);
        z_puts(out, (uint32_t)n + 6u);
    }
    Z_PUTS_LIT("c_echo: done\n");
    return count;
}

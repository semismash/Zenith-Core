/* Host-side test of the runtime: z_gets / z_puts framing + error codes against a mock UART, the memory functions of
 * libc_min.c, and the logic of programs/c_demo.c. Runs natively (no RISC-V needed):  make runtime-selftest
 * The two assembly stubs themselves (uart.S) can only be tested on the core.
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* libc_min.c is compiled with its symbols renamed (-Dmemcpy=zmemcpy ...) so it can be tested next to the host libc */
void  *zmemcpy(void *, const void *, size_t);
void  *zmemmove(void *, const void *, size_t);
void  *zmemset(void *, int, size_t);
int    zmemcmp(const void *, const void *, size_t);
size_t zstrlen(const char *);

#include "zenith.h"

/* ---------------------------------------------------------------------------------- mock UART */
static uint8_t  rxq[1 << 16]; static size_t rx_len, rx_pos;
static uint8_t  txq[1 << 16]; static size_t tx_len;
static uint32_t last_timeout;

int z_uart_rx(uint8_t *byte, uint32_t timeout)
{
    last_timeout = timeout;
    if (rx_pos >= rx_len) return -1;                 /* nothing queued = the real thing would time out */
    *byte = rxq[rx_pos++];
    return 0;
}
void z_uart_tx(uint8_t byte) { txq[tx_len++] = byte; }

static void rx_reset(void) { rx_len = rx_pos = 0; }
static void rx_put(const void *p, size_t n) { memcpy(rxq + rx_len, p, n); rx_len += n; }
static void rx_frame(const void *data, uint32_t n)
{
    uint8_t h[5] = {0x3D, (uint8_t)n, (uint8_t)(n >> 8), (uint8_t)(n >> 16), (uint8_t)(n >> 24)};
    rx_put(h, 5); rx_put(data, n);
}
static void tx_reset(void) { tx_len = 0; }
/* the sent frames contain NUL bytes (size field), so strstr() cannot be used on them */
static int tx_has(const char *needle)
{
    size_t n = strlen(needle);
    for (size_t i = 0; i + n <= tx_len; i++) if (memcmp(txq + i, needle, n) == 0) return 1;
    return 0;
}

static int fails, checks;
#define CHECK(c, ...) do { checks++; if (!(c)) { fails++; printf("  FAIL line %d: ", __LINE__); printf(__VA_ARGS__); printf("\n"); } } while (0)

/* ---------------------------------------------------------------------------------- the demo, main renamed */
#define main c_demo_main
#include "c_demo.c"
#undef main
#define main c_echo_main
#include "c_echo.c"
#undef main

int main(void)
{
    char buf[64];

    /* ---- z_puts framing */
    tx_reset();
    CHECK(z_puts("Hi", 2) == 0, "z_puts ok");
    { const uint8_t want[] = {0x3D, 2, 0, 0, 0, 'H', 'i', 0x3F};
      CHECK(tx_len == sizeof want && memcmp(txq, want, sizeof want) == 0, "frame bytes (%zu)", tx_len); }
    tx_reset(); CHECK(z_puts("x", 0) == Z_E_ZERO && tx_len == 0, "zero size rejected, nothing sent");
    tx_reset(); CHECK(z_puts(NULL, 3) == Z_E_ARG && tx_len == 0, "NULL rejected, nothing sent");
    tx_reset(); CHECK(Z_PUTS_LIT("a\xF0z") == 0 && tx_len == 5 + 3 + 1 && txq[6] == 0xF0, "any byte value is payload (0xF0)");
    { char big[300]; memset(big, 'q', sizeof big); tx_reset(); z_puts(big, 300);
      CHECK(txq[1] == 0x2C && txq[2] == 0x01 && tx_len == 5 + 300 + 1, "size > 255 encoded little endian"); }

    /* ---- z_gets */
    rx_reset(); rx_frame("ABC", 3);
    CHECK(z_gets(buf, 8, 123) == 3 && memcmp(buf, "ABC", 3) == 0, "basic receive");
    CHECK(last_timeout == 123, "caller's timeout is passed to every byte");

    rx_reset(); rx_frame("AB", 2);
    memset(buf, 'x', sizeof buf);
    CHECK(z_gets(buf, 8, 0) == 2 && buf[2] == 'x', "shorter than max_size is fine, nothing appended");
    rx_reset(); rx_frame("12345678", 8);
    CHECK(z_gets(buf, 8, 0) == 8 && memcmp(buf, "12345678", 8) == 0, "exactly max_size is fine");

    rx_reset(); rx_frame("123456789", 9); rx_frame("ok", 2);
    CHECK(z_gets(buf, 8, 0) == Z_E_SIZE, "too big -> Z_E_SIZE");
    CHECK(z_gets(buf, 8, 0) == 2 && memcmp(buf, "ok", 2) == 0, "stream is in sync after the drain");

    rx_reset(); rx_put("\x55", 1); rx_frame("ok", 2);
    CHECK(z_gets(buf, 8, 0) == Z_E_NOT_MSG, "first byte is not 0x3D -> Z_E_NOT_MSG");
    CHECK(rx_pos == 1, "...and exactly that one byte was consumed");
    CHECK(z_gets(buf, 8, 0) == 2, "the following frame is received normally");

    rx_reset(); { uint8_t z[5] = {0x3D, 0, 0, 0, 0}; rx_put(z, 5); }
    CHECK(z_gets(buf, 8, 0) == Z_E_ZERO && rx_pos == 5, "announced size 0 -> Z_E_ZERO, header consumed");

    rx_reset();                                      CHECK(z_gets(buf, 8, 0) == Z_E_TIMEOUT, "timeout on the first byte");
    rx_reset(); { const uint8_t h[3] = {0x3D, 3, 0}; rx_put(h, 3); }
    CHECK(z_gets(buf, 8, 0) == Z_E_TIMEOUT, "timeout inside the size field");
    rx_reset(); { const uint8_t h[7] = {0x3D, 3, 0, 0, 0, 'A', 'B'}; rx_put(h, 7); }
    CHECK(z_gets(buf, 8, 0) == Z_E_TIMEOUT, "timeout inside the payload");

    CHECK(z_gets(NULL, 8, 0) == Z_E_ARG, "NULL buffer");
    CHECK(z_gets(buf, 0, 0) == Z_E_ARG && z_gets(buf, -5, 0) == Z_E_ARG, "max_size <= 0");

    rx_reset(); { const uint8_t h[5] = {0x3D, 0, 0, 0, 0x80}; rx_put(h, 5); }   /* announces 2 GiB: does not fit int32_t, nothing follows */
    CHECK(z_gets(buf, 8, 0) == Z_E_SIZE, "size >= 2^31 -> Z_E_SIZE");
    rx_reset(); { const uint8_t h[5] = {0x3D, 16, 0, 0, 0}; rx_put(h, 5); }   /* announces 16, nothing follows, caller wants to wait forever */
    CHECK(z_gets(buf, 8, Z_UART_FOREVER) == Z_E_SIZE && last_timeout == Z_UART_DEFAULT_TIMEOUT,
          "drain never waits forever (last rx timeout was %u)", last_timeout);
    rx_reset(); { const uint8_t h[5] = {0x3D, 16, 0, 0, 0}; rx_put(h, 5); }
    CHECK(z_gets(buf, 8, 777) == Z_E_SIZE && last_timeout == 777, "drain keeps a short caller timeout");

    /* round trip puts -> gets */
    tx_reset(); z_puts("round trip", 10);
    rx_reset(); rx_put(txq, tx_len - 1);             /* the trailing 0x3F is for the host, the receiver does not expect it */
    CHECK(z_gets(buf, 32, 0) == 10 && memcmp(buf, "round trip", 10) == 0, "z_puts frame is a valid z_gets frame");

    /* ---- libc_min.c */
    { uint8_t a[40], b[40];
      for (int i = 0; i < 40; i++) a[i] = (uint8_t)(i + 1);
      int ok = 1;
      for (int off = 0; off < 4 && ok; off++) for (int len = 0; len < 33 && ok; len++) {
          memset(b, 0xEE, sizeof b); zmemcpy(b + off, a + 1, (size_t)len);
          for (int i = 0; i < 40; i++) { uint8_t e = (i >= off && i < off + len) ? a[1 + i - off] : 0xEE; if (b[i] != e) ok = 0; } }
      CHECK(ok, "memcpy all small offsets/lengths");
      ok = 1;
      for (int off = 0; off < 4 && ok; off++) for (int len = 0; len < 33 && ok; len++) {
          memset(b, 0x11, sizeof b); zmemset(b + off, 0x5A, (size_t)len);
          for (int i = 0; i < 40; i++) { uint8_t e = (i >= off && i < off + len) ? 0x5A : 0x11; if (b[i] != e) ok = 0; } }
      CHECK(ok, "memset all small offsets/lengths");
      uint8_t m[32], ref[32];
      ok = 1;
      for (int s = 0; s < 8 && ok; s++) for (int d = 0; d < 8 && ok; d++) {
          for (int i = 0; i < 32; i++) m[i] = ref[i] = (uint8_t)i;
          memmove(ref + d, ref + s, 20); zmemmove(m + d, m + s, 20);
          if (memcmp(m, ref, 32)) ok = 0; }
      CHECK(ok, "memmove overlapping both directions");
      CHECK(zmemcmp("abc", "abd", 3) < 0 && zmemcmp("abd", "abc", 3) > 0 && zmemcmp("abc", "abc", 3) == 0 && zmemcmp("a", "b", 0) == 0, "memcmp");
      CHECK(zstrlen("") == 0 && zstrlen("hello") == 5, "strlen"); }

    /* ---- the demo program (logic only, on the host) */
    tx_reset();
    CHECK(c_demo_main() == 0, "c_demo reports no failures on the host");
    CHECK(tx_has("PASS"), "c_demo printed PASS");
    tx_reset(); report(0x000001A5u);
    CHECK(tx_len == 5 + 29 + 1 && memcmp(txq + 5, "c_demo: FAIL mask=0x000001A5\n", 29) == 0, "failure message is formatted correctly (%.*s)", (int)tx_len - 6, txq + 5);

    /* ---- the echo program end to end through the mock */
    tx_reset(); rx_reset();
    rx_frame("hello", 5); rx_frame("quit", 4);
    CHECK(c_echo_main() == 2, "c_echo handled 2 messages");
    CHECK(tx_has("echo: hello"), "c_echo answered \"echo: hello\"");
    tx_reset(); rx_reset();
    rx_put("\x01", 1); rx_frame("quit", 4);
    CHECK(c_echo_main() == 1 && tx_has("z_gets error -2"), "c_echo reports a bad first byte and carries on");

    printf("%d checks, %d failed\n%s\n", checks, fails, fails ? "RESULT: FAIL" : "RESULT: PASS");
    return fails ? 1 : 0;
}

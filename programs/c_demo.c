/* c_demo - first C program for the Zenith Core: self-checking, prints one status message.
 *
 *   make cprog PROG=c_demo
 *   CLI:  load build/programs/c_demo.hex -v -r --register=true
 *
 * Prints "c_demo: PASS" or "c_demo: FAIL mask=0x........" and returns the failure mask from main(), so a0 (x10) in the
 * register dump is 0 on success. Mask bits:
 *   0 crc32 of "123456789" == 0xCBF43926        1 sieve: 168 primes below 1000 (.bss zeroing, byte stores)
 *   2 recursive fib(20) == 6765 (call/return, stack)   3 32-bit multiply   4 32-bit divide/modulo, signed + unsigned
 *   5 64-bit multiply / shifts (libgcc)         6 byte/halfword loads and stores, sign extension
 *   7 initialised .data and .rodata             8 memcpy/memset on odd sizes
 */
#include "zenith.h"

/* ---- 0: crc32, bitwise (no table, no division) ---- */
static uint32_t crc32(const uint8_t *p, uint32_t n)
{
    uint32_t crc = 0xFFFFFFFFu;
    while (n--) {
        crc ^= *p++;
        for (int i = 0; i < 8; i++) crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
    }
    return ~crc;
}
static int test_crc(void)
{
    static const char s[] = "123456789";
    return crc32((const uint8_t *)s, 9) == 0xCBF43926u;
}

/* ---- 1: sieve of Eratosthenes, the array lives in .bss and must start zeroed ---- */
static uint8_t composite[1001];
static int test_sieve(void)
{
    uint32_t count = 0;
    for (uint32_t i = 2; i <= 1000; i++) {
        if (!composite[i]) {
            count++;
            for (uint32_t j = i * i; j <= 1000; j += i) composite[j] = 1;
        }
    }
    return count == 168;
}

/* ---- 2: recursion ---- */
static uint32_t fib(uint32_t n) { return n < 2 ? n : fib(n - 1) + fib(n - 2); }
static int test_fib(void) { return fib(20) == 6765u; }

/* ---- 3, 4, 5: libgcc arithmetic (volatile keeps the compiler from folding it at build time) ---- */
static int test_mul(void)
{
    volatile uint32_t a = 123456, b = 789;
    return a * b == 97406784u;
}
static int test_div(void)
{
    volatile uint32_t a = 123456, b = 789;
    volatile int32_t  n = -1000, d = 7;
    return (a / b == 156u) && (a % b == 372u) && (n / d == -142) && (n % d == -6);
}
static int test_mul64(void)
{
    volatile uint32_t x = 0xFFFFFFFFu, y = 0xFFFFFFFFu;
    volatile uint64_t one = 1;
    uint64_t m = (uint64_t)x * y;
    return (uint32_t)(m >> 32) == 0xFFFFFFFEu && (uint32_t)m == 1u && ((one << 40) >> 38) == 4u;
}

/* ---- 6: sub-word accesses ---- */
static volatile uint8_t  vb[8];
static volatile uint16_t vh[4];
static int test_subword(void)
{
    for (int i = 0; i < 8; i++) vb[i] = (uint8_t)(0xF0 + i);
    for (int i = 0; i < 4; i++) vh[i] = (uint16_t)(0x8000 + i);
    uint32_t sum = 0;
    for (int i = 0; i < 8; i++) sum += vb[i];                 /* lbu: neighbours must not be disturbed by sb */
    int32_t sb = (int8_t)vb[0];                                 /* lb sign extension  */
    int32_t sh = (int16_t)vh[0];                                /* lh sign extension  */
    uint32_t uh = vh[3];                                        /* lhu zero extension */
    return sum == 1948u && sb == -16 && sh == -32768 && uh == 0x8003u && vh[1] == 0x8001u;
}

/* ---- 7: initialised data (lives in the image) and read-only data ---- */
static uint32_t tbl[4] = {0x11111111u, 0x22222222u, 0x33333333u, 0x44444444u};
static const uint8_t rod[5] = {1, 2, 3, 4, 5};
static int test_data(void)
{
    tbl[2] += 1;
    uint32_t s = tbl[0] + tbl[1] + tbl[2] + tbl[3];
    uint32_t r = 0;
    for (int i = 0; i < 5; i++) r += rod[i];
    return s == 0xAAAAAAABu && r == 15u;
}

/* ---- 8: memcpy / memset with odd sizes and offsets ---- */
static uint8_t msrc[37], mdst[37];
static int test_mem(void)
{
    for (int i = 0; i < 37; i++) msrc[i] = (uint8_t)(i * 7 + 3);
    memset(mdst, 0xAA, sizeof mdst);
    memcpy(mdst + 1, msrc + 1, 35);
    if (mdst[0] != 0xAA || mdst[36] != 0xAA) return 0;
    for (int i = 1; i < 36; i++) if (mdst[i] != msrc[i]) return 0;
    return 1;
}

/* ---- report ---- */
static void put_hex32(char *out, uint32_t v)
{
    static const char d[] = "0123456789ABCDEF";
    for (int i = 0; i < 8; i++) out[i] = d[(v >> (28 - 4 * i)) & 0xF];
}

static void report(uint32_t fail)
{
    if (fail == 0) {
        Z_PUTS_LIT("c_demo: PASS\n");
    } else {
        static char msg[] = "c_demo: FAIL mask=0x00000000\n";
        put_hex32(msg + (sizeof "c_demo: FAIL mask=0x" - 1u), fail);
        z_puts(msg, (uint32_t)(sizeof msg - 1u));
    }
}

int main(void)
{
    Z_PUTS_LIT("c_demo: running\n");

    uint32_t fail = 0;
    if (!test_crc())     fail |= 1u << 0;
    if (!test_sieve())   fail |= 1u << 1;
    if (!test_fib())     fail |= 1u << 2;
    if (!test_mul())     fail |= 1u << 3;
    if (!test_div())     fail |= 1u << 4;
    if (!test_mul64())   fail |= 1u << 5;
    if (!test_subword()) fail |= 1u << 6;
    if (!test_data())    fail |= 1u << 7;
    if (!test_mem())     fail |= 1u << 8;

    report(fail);
    return (int)fail;
}

/* Zenith Core showcase demo
 *
 *   1) CPU self-check : six small tests with known answers (CRC-32, xorshift, sub-word loads/stores, sorting,
 *                       prime sieve, recursion). Every result is printed with PASS / FAIL.
 *   2) Guessing game  : the core picks a number from 1 to 100, you answer with sendbyte <n>. The time you take to
 *                       make the first guess seeds the random number generator.
 *   3) Mandelbrot     : drawn live over the UART in ASCII, integer fixed-point only. RV32I has no multiply
 *                       instruction, so even the multiplications are done with shift-and-add in software.
 *                       Three views, each zooming further in. Send any byte (sendbyte 1) to go to the next one.
 *
 * Build:  make cprog PROG=showcase
 */
#include <zenith.h>
#include <zcutils.h>

#define LINE_SIZE   80
#define COLS        64          /* characters per Mandelbrot row                 */
#define ROWS        24
#define FRAC_BITS   12          /* Q.12 fixed point: 1.0 == 4096                 */
#define N_VIEWS     3

/* ------------------------------------------------------------------------------------------ output helpers */
static void say(const char *s) { z_puts(s, c_strlen(s)); }

static void hex32(uint32_t v, char *out)            /* 8 hex digits + NUL */
{
    int i = 0;
    for (int sh = 28; sh >= 0; sh -= 4) {
        uint32_t d = (v >> sh) & 0xFu;
        out[i++] = (char)(d < 10 ? '0' + d : 'A' + d - 10);
    }
    out[i] = '\0';
}

/* one result line:  "  <name><value>PASS|FAIL"   (the caller pre-pads the name to a fixed width) */
static int report(const char *name, const char *val, int ok)
{
    char b[LINE_SIZE];
    c_strcpy(b, "  ", sizeof b);
    c_strcat(b, name, sizeof b);
    c_strcat(b, val, sizeof b);
    for (uint32_t l = c_strlen(val); l < 16; l++) c_strcat(b, " ", sizeof b);      /* align the PASS column */
    c_strcat(b, ok ? "PASS\n" : "FAIL\n", sizeof b);
    say(b);
    return ok;
}

/* ------------------------------------------------------------------------------------------ self-check tests */
static uint32_t xorshift32(uint32_t x)
{
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

/* CRC-32 (reflected, poly 0xEDB88320); the standard check value for "123456789" is 0xCBF43926 */
static uint32_t crc32(const char *s, uint32_t n)
{
    uint32_t crc = 0xFFFFFFFFu;
    for (uint32_t i = 0; i < n; i++) {
        crc ^= (uint8_t)s[i];
        for (int k = 0; k < 8; k++)
            crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
    }
    return ~crc;
}

/* 1000 back-to-back dependent ALU operations: every instruction needs the result of the one before it,
 * which is exactly what the forwarding paths in the pipeline exist for */
static uint32_t dependent_chain(void)
{
    volatile uint32_t seed = 2463534242u;           /* volatile: the compiler cannot precompute the answer */
    uint32_t x = seed;
    for (int i = 0; i < 1000; i++) x = xorshift32(x);
    return x;
}

/* sb / sh stores followed by lb / lbu / lh / lhu / lw loads of the same memory */
static int subword_memory(void)
{
    volatile union { uint32_t w[2]; uint16_t h[4]; int16_t sh[4]; uint8_t b[8]; int8_t sb[8]; } m;

    m.b[0] = 0x11; m.b[1] = 0x22; m.b[2] = 0x33; m.b[3] = 0x44;     /* sb */
    m.h[2] = 0xBEEF; m.h[3] = 0xDEAD;                                /* sh */

    return m.w[0] == 0x44332211u && m.w[1] == 0xDEADBEEFu           /* lw  */
        && m.b[4]  == 0xEFu      && m.sb[4] == -17                  /* lbu, lb */
        && m.h[3]  == 0xDEADu    && m.sh[3] == -8531;               /* lhu, lh */
}

/* bubble sort of 32 pseudo-random words: loads, stores and lots of data-dependent branches */
static int sort_words(void)
{
    uint32_t a[32], sum_before = 0, sum_after = 0, x = 12345;

    for (int i = 0; i < 32; i++) {
        x = xorshift32(x);
        a[i] = x & 0x3FFu;
        sum_before += a[i];
    }
    for (int i = 0; i < 31; i++)
        for (int j = 0; j < 31 - i; j++)
            if (a[j] > a[j + 1]) { uint32_t t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; }

    for (int i = 0; i < 32; i++) sum_after += a[i];
    for (int i = 0; i < 31; i++) if (a[i] > a[i + 1]) return 0;
    return sum_before == sum_after;
}

/* sieve of Eratosthenes on a bit array: there are exactly 168 primes below 1000 */
static uint32_t count_primes(void)
{
    uint32_t composite[32];
    uint32_t n = 0;

    for (int i = 0; i < 32; i++) composite[i] = 0;
    for (uint32_t i = 2; i < 1000; i++) {
        if (composite[i >> 5] & (1u << (i & 31))) continue;
        n++;
        for (uint32_t j = i + i; j < 1000; j += i) composite[j >> 5] |= 1u << (j & 31);
    }
    return n;
}

/* deliberately naive recursion: ~57000 calls, exercises jal / jalr and the stack */
static uint32_t fib(uint32_t n) { return n < 2 ? n : fib(n - 1) + fib(n - 2); }

static int self_check(void)
{
    char v[LINE_SIZE];
    int passed = 0;
    uint32_t r;

    r = crc32("123456789", 9);
    hex32(r, v);
    passed += report("CRC-32(\"123456789\")    ", v, r == 0xCBF43926u);

    r = dependent_chain();
    hex32(r, v);
    passed += report("1000 dependent ALU ops ", v, r == 0xC4A2B16Cu);

    passed += report("sb sh / lb lbu lh lhu  ", "byte/half/word", subword_memory());
    passed += report("bubble sort, 32 words  ", "sorted", sort_words());

    r = count_primes();
    c_int_to_ascii((int32_t)r, v);
    passed += report("primes below 1000      ", v, r == 168u);

    r = fib(22);
    c_int_to_ascii((int32_t)r, v);
    passed += report("recursive fib(22)      ", v, r == 17711u);

    return passed;
}

/* ------------------------------------------------------------------------------------------ guessing game */
#define MAX_TRIES   7           /* 7 tries are always enough for 1..100 with a binary search */

/* wait for one byte from the host; every failed poll adds to *ticks, so *ticks measures how long the human took */
static uint8_t read_byte(uint32_t *ticks)
{
    uint8_t k;
    while (z_uart_rx(&k, 2000u) != 0) (*ticks)++;
    return k;
}

static void guessing_game(void)
{
    char b[LINE_SIZE], n[12];
    uint32_t ticks = 0;

    say("  I'm thinking of a number from 1 to 100. You have 7 tries.\n"
        "  >> sendbyte <number>   (how long you take seeds my random number generator)\n");

    uint8_t g = read_byte(&ticks);

    uint32_t x = ticks + 0x9E3779B9u, secret;
    for (int i = 0; i < 8; i++) x = xorshift32(x);
    do { x = xorshift32(x); secret = x & 127u; } while (secret < 1u || secret > 100u);   /* no division needed */

    int tries = 0;
    for (;;) {
        if (g < 1 || g > 100) {
            say("  pick a number from 1 to 100\n");
        } else {
            tries++;
            c_int_to_ascii(g, n);
            c_strcpy(b, "  guess ", sizeof b);
            c_strcat(b, n, sizeof b);

            if (g == secret) {
                c_strcat(b, " is correct! tries used: ", sizeof b);
                c_int_to_ascii(tries, n);
                c_strcat(b, n, sizeof b);
                c_strcat(b, "\n", sizeof b);
                say(b);
                return;
            }
            c_strcat(b, g < secret ? " is too low\n" : " is too high\n", sizeof b);
            say(b);

            if (tries >= MAX_TRIES) {
                c_int_to_ascii((int32_t)secret, n);
                c_strcpy(b, "  out of tries, the number was ", sizeof b);
                c_strcat(b, n, sizeof b);
                c_strcat(b, "\n", sizeof b);
                say(b);
                return;
            }
        }
        g = read_byte(&ticks);
    }
}

/* ------------------------------------------------------------------------------------------ countdown */
#define COUNT_STEP_CYCLES   10000000u       /* about 1 second at 10 MHz; z_uart_rx's timeout counts CPU cycles */

/* wait roughly `cycles` CPU cycles by letting the UART poll time out (a byte arriving would end the wait early) */
static void delay(uint32_t cycles)
{
    uint8_t k;
    z_uart_rx(&k, cycles);
}

static void countdown(void)
{
    static const char *const steps[] = { "  3 ...\n", "  2 ...\n", "  1 ...\n" };

    say("  starting in\n");
    for (int i = 0; i < 3; i++) {
        say(steps[i]);
        delay(COUNT_STEP_CYCLES);
    }
}

/* ------------------------------------------------------------------------------------------ Mandelbrot */
/* Q.12 multiply with shift-and-add (no mul instruction in RV32I). Needs |a*b| < 2^31 before the shift. */
static int32_t fmul(int32_t a, int32_t b)
{
    uint32_t neg = 0;
    if (a < 0) { a = -a; neg ^= 1u; }
    if (b < 0) { b = -b; neg ^= 1u; }

    uint32_t ua = (uint32_t)a, ub = (uint32_t)b;
    if (ub > ua) { uint32_t t = ua; ua = ub; ub = t; }      /* loop over the operand with fewer bits */

    uint32_t p = 0;
    while (ub) {
        if (ub & 1u) p += ua;
        ua <<= 1;
        ub >>= 1;
    }
    int32_t r = (int32_t)p;
    if (neg) r = -r;
    return r >> FRAC_BITS;
}

typedef struct {
    int32_t     x0, y0;         /* top-left corner of the view, Q.12                      */
    int32_t     dx;             /* step per column, Q.12 (the row step is 2*dx: characters are ~2x taller than wide) */
    uint32_t    max_iter;
    const char *title;
} view_t;

static const view_t views[N_VIEWS] = {
    { -8602, -4920, 205,  40, "view 1/3: the whole set" },
    { -7680,  -384,  16,  80, "view 2/3: zoom x13, a tiny copy of the whole set" },
    { -3308,   271,   8,  90, "view 3/3: zoom x26, seahorse valley" },
};

static void render(const view_t *v)
{
    static const char palette[] = ".,:;+*#%";             /* iteration count & 7 picks the character; inside the set: ' ' */
    char row[COLS + 1];
    uint32_t total_iter = 0;
    int32_t cy = v->y0;

    row[COLS] = '\n';
    for (int r = 0; r < ROWS; r++) {
        int32_t cx = v->x0;
        for (int c = 0; c < COLS; c++) {
            int32_t x = 0, y = 0;
            uint32_t i = 0;
            while (i < v->max_iter) {
                int32_t x2 = fmul(x, x), y2 = fmul(y, y);
                if (x2 + y2 > (4 << FRAC_BITS)) break;      /* |z| > 2: escaped */
                int32_t xy = fmul(x, y);
                y = xy + xy + cy;
                x = x2 - y2 + cx;
                i++;
            }
            total_iter += i;
            row[c] = (i >= v->max_iter) ? ' ' : palette[i & 7u];
            cx += v->dx;
        }
        z_puts(row, COLS + 1);                              /* one row per frame: it paints line by line */
        cy += v->dx + v->dx;
    }

    char b[LINE_SIZE], n[12];
    c_int_to_ascii((int32_t)total_iter, n);
    c_strcpy(b, "  ", sizeof b);
    c_strcat(b, n, sizeof b);
    c_strcat(b, " iterations computed on the core\n", sizeof b);
    say(b);
}

/* ------------------------------------------------------------------------------------------ main */
void main(void)
{
    say("==================================================\n"
        "  ZENITH CORE  -  my own RV32I CPU, on an FPGA\n"
        "  5-stage pipeline | forwarding | ~10 MHz | UART\n"
        "  no multiplier, no divider, no FPU, no libc\n"
        "  all built from scratch, hardware, and software.\n"
        "==================================================\n\n"
        "[1/3] CPU self-check\n");

    int passed = self_check();

    char b[LINE_SIZE], n[12];
    c_int_to_ascii(passed, n);
    c_strcpy(b, "  -> ", sizeof b);
    c_strcat(b, n, sizeof b);
    c_strcat(b, "/6 checks passed\n", sizeof b);
    say(b);
    /* a small shaded ^_^ between two # rules, drawn with the same characters as the Mandelbrot palette */
    say("\n##################################################\n"
        "\n"
        "             +*##*+            +*##*+\n"
        "           +*#%##%#*+        +*#%##%#*+\n"
        "          *#%#*++*#%#*      *#%#*++*#%#*\n"
        "         *##*+    +*##*    *##*+    +*##*\n"
        "\n"
        "                  +%__________%+\n"
        "                  :############:\n"
        "\n"
        "##################################################\n");
    say("\n[2/3] Guessing game\n");
    guessing_game();

    say("\n[3/3] Mandelbrot set, integer maths only\n");
    countdown();

    for (int i = 0; i < N_VIEWS; i++) {
        c_strcpy(b, "\n  ", sizeof b);
        c_strcat(b, views[i].title, sizeof b);
        c_strcat(b, "\n", sizeof b);
        say(b);

        render(&views[i]);

        if (i < N_VIEWS - 1) {
            say("\n  >> sendbyte 1  for the next view\n");
            uint8_t key;
            while (z_uart_rx(&key, Z_UART_FOREVER) != 0) { }
        }
    }

    say("\nDone! Be sure to check out my GitHub and stay tuned for more updates :D\n");
}
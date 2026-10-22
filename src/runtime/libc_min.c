/* Zenith Core - the few libc functions GCC may call by itself in freestanding code (struct copies, array
 * initialisers, loop idioms). Strict-alignment safe: the word paths are only taken when everything is aligned. */
#pragma GCC optimize ("no-tree-loop-distribute-patterns")   /* or these loops would turn into calls to themselves */

#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = dst;
    const unsigned char *s = src;
    if ((((uintptr_t)d | (uintptr_t)s) & 3u) == 0) {
        uint32_t *dw = (uint32_t *)d;
        const uint32_t *sw = (const uint32_t *)s;
        for (; n >= 4; n -= 4) *dw++ = *sw++;
        d = (unsigned char *)dw;
        s = (const unsigned char *)sw;
    }
    while (n--) *d++ = *s++;
    return dst;
}

void *memmove(void *dst, const void *src, size_t n)
{
    unsigned char *d = dst;
    const unsigned char *s = src;
    if (d == s || n == 0) return dst;
    if (d < s || d >= s + n) return memcpy(dst, src, n);
    d += n; s += n;                             /* overlapping with dst above src: copy backwards */
    while (n--) *--d = *--s;
    return dst;
}

void *memset(void *dst, int c, size_t n)
{
    unsigned char *d = dst;
    unsigned char v = (unsigned char)c;
    while (n && ((uintptr_t)d & 3u)) { *d++ = v; n--; }
    if (n >= 4) {
        uint32_t w = v * 0x01010101u;
        uint32_t *dw = (uint32_t *)d;
        for (; n >= 4; n -= 4) *dw++ = w;
        d = (unsigned char *)dw;
    }
    while (n--) *d++ = v;
    return dst;
}

int memcmp(const void *a, const void *b, size_t n)
{
    const unsigned char *x = a, *y = b;
    for (; n; n--, x++, y++) {
        if (*x != *y) return (int)*x - (int)*y;
    }
    return 0;
}

size_t strlen(const char *s)
{
    const char *p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

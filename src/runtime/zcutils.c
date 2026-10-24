#include <zcutils.h>

void c_strcpy(char *dest, const char *src, uint32_t max_len) {
    if (max_len == 0) return;
    uint32_t i = 0;

    while (src[i] != '\0' && i < (max_len - 1)) {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

void c_strcat(char* dest, const char *src, uint32_t max_len) {
    if (max_len == 0) return;
    uint32_t cur_len = 0;

    while (*dest != '\0' && cur_len < max_len) { 
        dest++;
        cur_len++;
    }
    if (cur_len >= max_len) return;
    while (*src != '\0' && cur_len < (max_len - 1)) {
        *dest++ = *src++;
        cur_len++;
    }

    *dest = '\0';
}

uint32_t c_strlen(const char* str) {
    uint32_t len = 0;
    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}

int8_t c_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    if (*s1 > *s2) return 1;
    else if (*s1 == *s2) return 0;
    else return -1;
}

int8_t to_cstring(char* buf, uint32_t len, uint32_t max_len) {
    if (max_len == 0) return -1;
    if (len < max_len) buf[len] = '\0';
    else return -1;
    return 0;
}

void c_int_to_ascii(int32_t val, char* buf) {    // base 10
    char* ptr = buf;
    uint32_t abs_val;

    if (val < 0) {
        *ptr++ = '-';
        abs_val = 0u - (uint32_t)val;           // also correct for INT32_MIN
    } else {
        abs_val = (uint32_t)val;
    }

    // repeated subtraction instead of / and %, rv32i has no divide instruction
    static const uint32_t powers[] = {
        1000000000u, 
        100000000u, 
        10000000u, 
        1000000u, 
        100000u, 
        10000u, 
        1000u, 
        100u, 
        10u
    };
    uint8_t suppress_leading_zero = 1;

    for (int i = 0; i < 9; i++) {
        uint8_t count = 0;
        uint32_t power = powers[i];

        while (abs_val >= power) {
            abs_val -= power;
            count++;
        }

        if (count > 0 || !suppress_leading_zero) {
            *ptr++ = (char)(count + '0');
            suppress_leading_zero = 0;
        }
    }

    *ptr++ = (char)(abs_val + '0');
    *ptr = '\0';
}
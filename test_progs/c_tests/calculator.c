#include "zenith.h"
#include <string.h>

#define BUFFER_SIZE 100
#define BYTE_CONV_BUF_SIZE 5

// NOTE: functions that use c_ require C strings and must use null terminators, will be changed from void to int later for returning errrors

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

int8_t to_cstring(char* buf, uint32_t len, uint32_t max_len) {
    if (max_len == 0) return -1;
    if (len < max_len) buf[len] = '\0';
    else return -1;
    return 0;
}

void c_int_to_ascii(int8_t val, char* buf) {    // base 10
    char* ptr = buf;
    uint8_t abs_val;

    if (val < 0) {
        *ptr++ = '-';
        abs_val = (uint8_t)(-((int32_t)val));
    } else {
        abs_val = (uint8_t)(val);
    }

    static const uint8_t powers[] = {100, 10};
    uint8_t suppress_leading_zero = 1;

    for (int i = 0; i < 2; i++) {
        uint8_t count = 0;
        uint8_t power = powers[i];

        while (abs_val >= power) {
            abs_val -= power;
            count++;
        }

        if (count > 0 || !suppress_leading_zero) {
            *ptr++ = count + '0';
            suppress_leading_zero = 0;
        }
    }

    *ptr++ = (char)(abs_val + '0');
    *ptr = '\0';
}

void main(void) {

    int8_t num_1, num_2, sum, diff;
    char print_buf[BUFFER_SIZE];
    char num_conv_buf[BYTE_CONV_BUF_SIZE];
    char input_buf[BUFFER_SIZE];

    uint8_t chk = 1;    // temp var, allow uart poll loop as long as there is no input byte
    c_strcpy(print_buf, "Enter your first number : ", BUFFER_SIZE);
    z_puts(print_buf, c_strlen(print_buf));
    while (chk != 0) {
        chk = z_uart_rx((uint8_t *)&num_1, 0);
    }
    chk = 1;
    c_strcpy(print_buf, "Enter your second number : ", BUFFER_SIZE);
    z_puts(print_buf, c_strlen(print_buf));
    while (chk != 0) {
        chk = z_uart_rx((uint8_t *)&num_2, 0);
    }

    sum = num_1 + num_2;
    diff = num_1 - num_2;

    c_int_to_ascii(sum, num_conv_buf);

    c_strcpy(print_buf, "The sum of the two numbers is: ", BUFFER_SIZE);
    c_strcat(print_buf, num_conv_buf, BUFFER_SIZE);
    c_strcat(print_buf, ".\n", BUFFER_SIZE);
    uint32_t s_len = c_strlen(print_buf);
    z_puts(print_buf, s_len);

    c_int_to_ascii(diff, num_conv_buf);

    c_strcpy(print_buf, "The difference of the two numbers is: ", BUFFER_SIZE);
    c_strcat(print_buf, num_conv_buf, BUFFER_SIZE);
    c_strcat(print_buf, ".\n", BUFFER_SIZE);
    s_len = c_strlen(print_buf);
    z_puts(print_buf, s_len);

    c_strcpy(print_buf, "What should I call you? ", BUFFER_SIZE);
    z_puts(print_buf, c_strlen(print_buf));
    uint32_t size = (uint32_t)-1;
    while ((int32_t)size == -1) {
        size = z_gets(input_buf, BUFFER_SIZE, 0);
        if ((int32_t)size < -1) return; // just return prematurely from program if bad input
    }
    if (to_cstring(input_buf, size, BUFFER_SIZE) != 0) return;

    c_strcpy(print_buf, "Hii, it's nice to meet you ", BUFFER_SIZE);
    c_strcat(print_buf, input_buf, BUFFER_SIZE);
    c_strcat(print_buf, "! :D", BUFFER_SIZE);
    s_len = c_strlen(print_buf);
    z_puts(print_buf, s_len);

    // no return as platform doesn't require a return point to tell if function succeeded.
}
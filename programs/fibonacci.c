#include <zenith.h>
#include <zcutils.h>

#define BUFFER_SIZE 100
#define CONV_BUF_SIZE 12

uint32_t fibonacci(uint8_t n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return fibonacci(n - 1) + fibonacci(n - 2);
}

void main(void) {
    uint8_t num;
    char print_buf[BUFFER_SIZE];
    char num_conv_buf[CONV_BUF_SIZE];

    c_strcpy(print_buf, "Enter a number for fibonacci: ", BUFFER_SIZE);
    z_puts(print_buf, c_strlen(print_buf));

    uint8_t _ = 1;
    while (_) _ = z_uart_rx(&num, 0);

    uint32_t res = fibonacci(num);
    c_int_to_ascii(res, num_conv_buf);

    c_strcpy(print_buf, "\nThe fibonacci series for the given number is: ", BUFFER_SIZE);
    c_strcat(print_buf, num_conv_buf, BUFFER_SIZE);
    c_strcat(print_buf, ".\n", BUFFER_SIZE);
    z_puts(print_buf, c_strlen(print_buf));
}
#include <zenith.h>
#include <zcutils.h>

#define BUFFER_SIZE 100
#define CONV_BUF_SIZE 12

void main(void) {

    int8_t num_1, num_2;
    int32_t sum, diff;
    char print_buf[BUFFER_SIZE];
    char num_conv_buf[CONV_BUF_SIZE];
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
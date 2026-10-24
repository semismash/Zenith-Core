#include <zenith.h>
#include <zcutils.h>

#define BUFFER_SIZE 100

void main(void) {
    char print_buf[BUFFER_SIZE];

    c_strcpy(print_buf, "how 'bout i clutch in endsems uwu", BUFFER_SIZE);
    z_puts(print_buf, c_strlen(print_buf));
}
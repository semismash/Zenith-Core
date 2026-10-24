/*
    C-program utilities provided for the Zenith Core architecture.
    The below functions can be used as regular C functions.
    NOTE: String functions require accounting for the NULL terminator.
*/


#ifndef ZCUTILS_H
#define ZCUTILS_H

#include <stddef.h>
#include <stdint.h>

void        c_strcpy(char *dest, const char *src, uint32_t max_len);    // copy C string from one buffer to another
void        c_strcat(char* dest, const char *src, uint32_t max_len);    // concatenate a src C string infront of another dst C string
uint32_t    c_strlen(const char* str);                                  // find the length of a C string
int8_t      c_strcmp(const char* s1, const char* s2);                   // compare the length of two strings and return output
int8_t      to_cstring(char* buf, uint32_t len, uint32_t max_len);      // convert a byte buffer to C string
void        c_int_to_ascii(int32_t val, char* buf);                     // convert an integer to ASCII string

#endif
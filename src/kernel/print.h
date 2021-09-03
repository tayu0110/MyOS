#ifndef _PRINT_H_INCLUDED_
#define _PRINT_H_INCLUDED_

#include <stdint.h>

#define CHARCTER_SPACE 0

void set_cursor(uint16_t x, uint16_t y);
int put_char(char c);
int put_string(const char *s);

#endif
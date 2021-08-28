#ifndef _FONT_H_INCLUDED_
#define _FONT_H_INCLUDED_

#include <stdint.h>

extern uint64_t _binary_hankaku16_bin_size;
extern uint64_t _binary_hankaku16_bin_start;
extern uint64_t _binary_hankaku16_bin_end;

uint64_t get_font(char c);

#endif
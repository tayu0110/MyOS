#ifndef _FONT_H_INCLUDED_
#define _FONT_H_INCLUDED_

#include <stdint.h>

#define FONT_WIDTH 8
#define FONT_HEIGHT 16
#define FONT_NUM 256

extern const uint8_t _binary_hankaku16_bin_start[];
extern const uint8_t _binary_hankaku16_bin_end[];
extern const uint8_t _binary_hankaku16_bin_size[];

const uint8_t *get_font(char c);

#endif
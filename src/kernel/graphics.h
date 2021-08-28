#ifndef _GRAPHICS_H_INCLUDED_
#define _GRAPHICS_H_INCLUDED_

#include <stdint.h>
#include "frame_buffer.h"

void init_graphics(frame_buffer_info_t frame_buffer);
void clear_srceen();
void draw_dot(uint16_t x, uint16_t y, uint32_t color);
uint32_t make_color(uint8_t red, uint8_t green, uint8_t blue);

#endif
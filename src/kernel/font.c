#include "font.h"

// Get the address of the fonts.
// c : ascii code of the character which want to get.
const uint8_t *get_font(char c) {
  uint32_t offset = (uint32_t)c * FONT_HEIGHT;
  return _binary_hankaku16_bin_start + offset;
}
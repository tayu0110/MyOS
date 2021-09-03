#include <string.h>

#include "graphics.h"
#include "util.h"

uint32_t horizontal_resolution;
uint32_t vertical_resolution;

static frame_buffer_info_t global_frame_buffer;
static uint32_t size_of_pixel_elements;

static uint32_t red_offset;
static uint32_t green_offset;
static uint32_t blue_offset;

// Initialize the information about graphics.
// frame_buffer : frame buffer which is taken from UEFI.
void init_graphics(frame_buffer_info_t frame_buffer) {
  memcpy(&global_frame_buffer, &frame_buffer, sizeof(frame_buffer));
  horizontal_resolution = frame_buffer.horizontal_resolution;
  vertical_resolution = frame_buffer.vertical_resolution;
  
  switch(global_frame_buffer.pixel_format) {
    case PixelBlueGreenRedReserved8BitPerColor:
      size_of_pixel_elements = 4;
      blue_offset = 0;
      green_offset = 8;
      red_offset = 16;
      break;
    case PixelRedGreenBlueReserved8BitPerColor:
      size_of_pixel_elements = 4;
      blue_offset = 16;
      green_offset = 8;
      red_offset = 0;
      break;
    case PixelBitMask:
    case PixelBltOnly:
    case PixelFormatMax:
    default:
      size_of_pixel_elements = 4;
      // Not implemented.
      // I'm not sure how to set it up, and since it is basically expected to be set up with
      // PixelBlueGreenRedReserved8BitColor, I may implement it in the future.
      break;
  }
}

// Fill the screen with black.
void clear_srceen() {
  uint64_t base = global_frame_buffer.frame_buffer_base;
  uint64_t hr = global_frame_buffer.horizontal_resolution;
  uint64_t vr = global_frame_buffer.vertical_resolution;
  uint64_t scanline = global_frame_buffer.pixels_per_scanline;
  for(uint64_t i = 0; i < vr; i++) {
    for(uint64_t j = 0; j < hr; j++) {
      *((uint32_t *)(base + i * scanline * size_of_pixel_elements + j * size_of_pixel_elements)) = (uint32_t)0;
    }
  }
}

// Draw a dot at (x, y). (0 <= x < HorizontalResolusion, 0 <= y < VerticalResolusion)
// If the dot position is specified outside the range, the dot will be drawn at the closest position within the range.
// By setting "color", can specify the color of the dot. Can use make_color() for setting "color".
void draw_dot(uint16_t x, uint16_t y, uint32_t color) {
  // If the coordinates are invaild, fit them within the range.
  x = max_u16(0, min_u16(x, (uint16_t)global_frame_buffer.horizontal_resolution-1));
  y = max_u16(0, min_u16(y, (uint16_t)global_frame_buffer.vertical_resolution-1));

  uint64_t base = global_frame_buffer.frame_buffer_base;
  uint64_t scanline = global_frame_buffer.pixels_per_scanline;
  *((uint32_t *)(base + scanline * y * size_of_pixel_elements + x * size_of_pixel_elements)) = color;
}

// Make the value of color for drawing dots.
// The color must be specified as an 8-bit value, and any bits out of range will be ignored.
uint32_t make_color(uint8_t red, uint8_t green, uint8_t blue) {
  return (uint32_t)red << red_offset | (uint32_t)green << green_offset | (uint32_t)blue << blue_offset;
}

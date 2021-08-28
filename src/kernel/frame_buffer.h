#ifndef _FRAME_BUFFER_H_INCLUDED_
#define _FRAME_BUFFER_H_INCLUDED_

#include <stdint.h>

typedef enum {
  PixelRedGreenBlueReserved8BitPerColor,
  PixelBlueGreenRedReserved8BitPerColor,
  PixelBitMask,
  PixelBltOnly,
  PixelFormatMax
} efi_graphics_pixel_format_t;

typedef struct _frame_buffer_info {
  uint32_t horizontal_resolution;
  uint32_t vertical_resolution;
  efi_graphics_pixel_format_t pixel_format;
  // the offset in video memory from pixel element (x, y) to pixel element (x, y+1) has to be calculate as 
  // (Number of pixel elements) * pixels_per_scanline, NOT (Number of pixel elements) * horizontal_resolution.
  uint32_t pixels_per_scanline;
  // The physical address of the top of the frame buffer.
  uint64_t frame_buffer_base;
  uint64_t frame_buffer_size;
} frame_buffer_info_t;

#endif
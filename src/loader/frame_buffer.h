#ifndef _FRAME_BUFFER_H_INCLUDED_
#define _FRAME_BUFFER_H_INCLUDED_
#include <efi.h>

typedef struct _frame_buffer_info {
  UINT32 horizontal_resolution;
  UINT32 vertical_resolution;
  EFI_GRAPHICS_PIXEL_FORMAT pixel_format;
  // the offset in video memory from pixel element (x, y) to pixel element (x, y+1) has to be calculate as 
  // (Number of pixel elements) * pixels_per_scanline, NOT (Number of pixel elements) * horizontal_resolution.
  UINT32 pixels_per_scanline;
  // The physical address of the top of the frame buffer.
  EFI_PHYSICAL_ADDRESS frame_buffer_base;
  UINTN frame_buffer_size;
} frame_buffer_info_t;

#endif
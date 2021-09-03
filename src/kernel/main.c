#include "graphics.h"
#include "print.h"

int main(frame_buffer_info_t frame_buffer) {
  init_graphics(frame_buffer);

  clear_srceen();

  set_cursor(0, 0);
  put_string("Hello, World!\n");

  for(uint32_t i = 0; i < 0xff; i++)
    put_char(i);

  return 0;
}

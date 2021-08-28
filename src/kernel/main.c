#include "graphics.h"

int main(frame_buffer_info_t frame_buffer) {
  init_graphics(frame_buffer);

  clear_srceen();

  for(int x = 20; x <= 70; x++) {
    draw_dot(x, 20, make_color(0xff, 0xff, 0xff));
    draw_dot(x, 70, make_color(0xff, 0xff, 0xff));
  }
  for(int y = 20; y <= 70; y++) {
    draw_dot(20, y, make_color(0xff, 0xff, 0xff));
    draw_dot(70, y, make_color(0xff, 0xff, 0xff));
  }
  return 0xffee;
}

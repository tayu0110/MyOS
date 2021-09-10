#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "print.h"
#include "graphics.h"
#include "font.h"
#include "util.h"

// Keep the information of the cursor.
static struct {
  uint16_t row;
  uint16_t column;
} cursor;

// Increase the position of the cursor.
// If the cursor reaches the right edge, make cursor move to the next line.
static void inc_cursor() {
  uint16_t h_offset = FONT_WIDTH + CHARCTER_SPACE;
  cursor.column += h_offset;
  
  if(cursor.column > horizontal_resolution - h_offset) {
    uint16_t v_offset = FONT_HEIGHT + CHARCTER_SPACE;
    cursor.row += v_offset;
    cursor.column = 0;
  }
}

// Decrease the position of the cursor.
// If the cursor reaches the left edge, make cursor move to the previous line.
static void dec_cursor() {
  uint16_t h_offset = FONT_WIDTH + CHARCTER_SPACE;
  cursor.column -= h_offset;

  if(cursor.column < 0) {
    uint16_t v_offset = FONT_HEIGHT + CHARCTER_SPACE;
    cursor.row -= v_offset;
    cursor.column = (horizontal_resolution - h_offset) / h_offset * h_offset;
  }
}

// Make the cursor move to the next line.
static void newline_cursor() {
  cursor.row += FONT_HEIGHT + CHARCTER_SPACE;
  cursor.column = 0;
}

// Set the cursor at the optional position.
// x : horizontal position
// y : vertical position
void set_cursor(uint16_t x, uint16_t y) {
  x = max_u16(0, min_u16(x, horizontal_resolution - FONT_WIDTH - CHARCTER_SPACE));
  y = max_u16(0, min_u16(y, vertical_resolution - FONT_HEIGHT - CHARCTER_SPACE));

  cursor.column = x;
  cursor.row = y;
}  

// Display the character which is 'c' on ascii code.
// c : ascii code (8-bit unsigned integer)
int put_char(char c) {
  if(c == '\n') {
    newline_cursor();
    return 0;
  }

  const uint8_t *font = get_font(c);
  uint16_t row = cursor.row;
  uint16_t column = cursor.column;

  for(int16_t i = 0; i < FONT_HEIGHT; i++) {
    uint8_t now_row = font[i];
    for(int16_t j = FONT_WIDTH-1; j >= 0; j--) {
      if(now_row & (1 << j)) {
        draw_dot(column + (7-j), row + i, make_color(0xff, 0xff, 0xff));
      }
    }
  }

  inc_cursor();

  return 0;
}

// Display the string 's'.
// s : null terminated string.
int put_string(const char *s) {
  while(*s) {
    if(*s == '\n') {
      newline_cursor();
      s++;
      continue;
    }

    put_char(*s);
    s++;
  }

  return 0;
}

// Currently, this provides the same functionality as printf().
int printk(const char* fmt, ...) {
  char buf[4096];
  va_list ap;

  va_start(ap, fmt);
  int res = vsprintf(buf, fmt, ap);
  va_end(ap);

  put_string(buf);

  return res;
}
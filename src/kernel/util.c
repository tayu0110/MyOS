#include "util.h"

uint16_t max_u16(uint16_t lhs, uint16_t rhs) {
  return (lhs > rhs ? lhs : rhs);
}

uint16_t min_u16(uint16_t lhs, uint16_t rhs) {
  return (lhs < rhs ? lhs : rhs);
}

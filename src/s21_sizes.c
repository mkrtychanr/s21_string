#include "s21_sizes.h"

void sizes_init(sizes *s) {
  s->L = false;
  s->h = false;
  s->l = false;
  s->width = 0;
  s->precision = 6;
}

bool set_size(sizes *s, char size) {
  bool result = true;
  switch (size) {
    case 'L':
      s->L = true;
      break;
    case 'h':
      s->h = true;
      break;
    case 'l':
      s->l = true;
      break;
    default:
      result = false;
      break;
  }
  return result;
}

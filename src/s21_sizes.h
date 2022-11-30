typedef struct sizes sizes;

#ifndef SRC_S21_SIZES_H_
#define SRC_S21_SIZES_H_

#include "s21_string.h"

struct sizes {
  bool L;
  bool h;
  bool l;
  s21_size_t width;
  s21_size_t precision;
};

void sizes_init(sizes *s);

bool set_size(sizes *s, char size);

#endif  // SRC_S21_SIZES_H_

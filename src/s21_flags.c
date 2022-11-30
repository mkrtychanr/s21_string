#include "s21_flags.h"

#include "s21_string.h"

void flags_init(flags *f) {
  f->minus = false;
  f->plus = false;
  f->space = false;
  f->hashtag = false;
  f->zero = false;
  f->precision = false;
}

bool set_flag(flags *f, char flag) {
  bool result = true;
  switch (flag) {
    case '-':
      f->minus = true;
      f->zero = false;
      break;
    case '+':
      f->plus = true;
      break;
    case ' ':
      f->space = true;
      break;
    case '#':
      f->hashtag = true;
      break;
    case '0':
      if (f->minus == false) {
        f->zero = true;
      }
      break;
    default:
      result = false;
      break;
  }
  return result;
}

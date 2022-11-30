typedef struct s21_string s21_string;
#ifndef SRC_S21_DYNAMIC_STRING_H_
#define SRC_S21_DYNAMIC_STRING_H_

#include "s21_string.h"

struct s21_string {
  char *data;
  s21_size_t size;
  s21_size_t capacity;
};

void s21_string_resize(s21_string *str, s21_size_t capacity);

void s21_string_init(s21_string *str);

void s21_string_push_back(s21_string *str, const char rhs);

void s21_string_add_string(s21_string *str, s21_string *rhs);

void s21_string_free(s21_string *str);

#endif  // SRC_S21_DYNAMIC_STRING_H_

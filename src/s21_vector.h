typedef struct s21_vector s21_vector;

#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include "s21_string.h"

struct s21_vector {
  s21_size_t *data;
  s21_size_t size;
  s21_size_t capacity;
};

void s21_vector_resize(s21_vector *v, s21_size_t capacity);

void s21_vector_init(s21_vector *v);

void s21_vector_push_back(s21_vector *v, const s21_size_t rhs);

void s21_vector_free(s21_vector *v);

#endif  // SRC_S21_VECTOR_H_

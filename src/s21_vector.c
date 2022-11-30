#include "s21_vector.h"

#include <stdio.h>
#include <stdlib.h>

void s21_vector_resize(s21_vector *v, s21_size_t capacity) {
  s21_size_t *temp = (s21_size_t *)malloc(v->size * sizeof(s21_size_t));
  for (s21_size_t i = 0; i < v->size; i++) {
    temp[i] = v->data[i];
  }
  free(v->data);
  v->capacity = capacity;
  v->data = (s21_size_t *)malloc(v->capacity * sizeof(s21_size_t));
  for (s21_size_t i = 0; i < v->size; i++) {
    v->data[i] = temp[i];
  }
  free(temp);
}

void s21_vector_init(s21_vector *v) {
  v->size = 0;
  v->capacity = 2;
  v->data = (s21_size_t *)malloc(v->capacity * sizeof(s21_size_t));
  s21_vector_resize(v, 2);
}

void s21_vector_push_back(s21_vector *v, const s21_size_t rhs) {
  if (v->size + 1 < v->capacity) {
    v->data[v->size] = rhs;
    v->size++;
  } else {
    s21_vector_resize(v, v->capacity * 2);
    s21_vector_push_back(v, rhs);
  }
}

void s21_vector_free(s21_vector *v) { free(v->data); }

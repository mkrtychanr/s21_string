#include "s21_dynamic_string.h"

#include <stdio.h>
#include <stdlib.h>

void s21_string_resize(s21_string *str, s21_size_t capacity) {
  char *temp = (char *)malloc(str->size * sizeof(char));
  for (s21_size_t i = 0; i < str->size; i++) {
    temp[i] = str->data[i];
  }
  free(str->data);
  str->capacity = capacity;
  str->data = (char *)malloc(str->capacity * sizeof(char));
  for (s21_size_t i = 0; i < str->size; i++) {
    str->data[i] = temp[i];
  }
  free(temp);
}

void s21_string_init(s21_string *str) {
  str->size = 0;
  str->capacity = 2;
  str->data = (char *)malloc(str->capacity * sizeof(char));
  s21_string_resize(str, 2);
}

void s21_string_push_back(s21_string *str, const char rhs) {
  if (str->size + 1 < str->capacity) {
    str->data[str->size] = rhs;
    str->size++;
  } else {
    s21_string_resize(str, str->capacity * 2);
    s21_string_push_back(str, rhs);
  }
}

void s21_string_add_string(s21_string *str, s21_string *rhs) {
  for (s21_size_t i = 0; i < rhs->size; i++) {
    s21_string_push_back(str, rhs->data[i]);
  }
  str->data[str->size] = '\0';
}

void s21_string_free(s21_string *str) { free(str->data); }

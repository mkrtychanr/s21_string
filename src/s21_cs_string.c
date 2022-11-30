#include "s21_cs_string.h"

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  s21_size_t str_len = 0;
  if (str != s21_NULL) {
    str_len = s21_strlen(str);
    result = (char *)calloc(str_len + 1, sizeof(char));
    for (s21_size_t i = 0; i < str_len; i++) {
      char to_result = str[i];
      if ('a' <= to_result && to_result <= 'z') {
        to_result -= 32;
      }
      result[i] = to_result;
    }
  }
  return (void *)result;
}

void *s21_to_lower(const char *str) {
  char *result = s21_NULL;
  s21_size_t str_len = 0;
  if (str != s21_NULL) {
    str_len = s21_strlen(str);
    result = (char *)calloc(str_len + 1, sizeof(char));
    for (s21_size_t i = 0; i < str_len; i++) {
      char to_result = str[i];
      if ('A' <= to_result && to_result <= 'Z') {
        to_result += 32;
      }
      result[i] = to_result;
    }
  }
  return (void *)result;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  s21_size_t src_len = 0;
  s21_size_t str_len = 0;
  char *result = s21_NULL;
  if (src != s21_NULL) {
    src_len = s21_strlen(src);
  }
  if (str != s21_NULL) {
    str_len = s21_strlen(str);
  }
  if (start_index <= src_len) {
    result = (char *)calloc(src_len + str_len + 1, sizeof(char));
    for (s21_size_t i = 0; i < start_index; i++) {
      result[i] = src[i];
    }
    for (s21_size_t i = start_index; i < start_index + str_len; i++) {
      result[i] = str[i - start_index];
    }
    for (s21_size_t i = start_index + str_len; i < src_len + str_len; i++) {
      result[i] = src[i - str_len];
    }
  }
  return (void *)result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  s21_size_t src_len = 0;
  if (src && trim_chars) {
    src += s21_strspn(src, trim_chars);
    src_len = s21_strlen(src);

    int collision[256] = {0};
    char *ptr = (char *)trim_chars;
    while (*ptr) {
      collision[(int)*(ptr++)] = 1;
    }
    char *right = (char *)src + src_len;
    for (s21_size_t i = src_len - 1;; i--) {
      if (collision[(int)src[i]] == 0) {
        right = (char *)src + i + 1;
        break;
      }
    }

    s21_size_t result_size = right - src;
    result = (char *)calloc(result_size + 1, sizeof(char));
    s21_memcpy(result, src, result_size);
    result[result_size] = '\0';
  }
  return (void *)result;
}

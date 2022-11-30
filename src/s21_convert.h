#ifndef SRC_S21_CONVERT_H_
#define SRC_S21_CONVERT_H_

#include "s21_string.h"

char *s21_int_to_str(int value);

void s21_to_precision(s21_string *result, s21_string *core_number,
                      s21_size_t precision, s21_size_t i_start);

void s21_integer_to_str(s21_string *result, s21_size_t value, char spec,
                        s21_size_t precision, bool need_zero);

bool s21_set_denominator_and_prefix(s21_size_t *denominator, s21_size_t *prefix,
                                    char spec);

void s21_long_double_to_str(s21_string *result, long double num, bool hashtag,
                            s21_size_t precision);

void s21_fill(s21_string *result, s21_vector *right, char spec, bool hashtag,
              s21_size_t dot, char sign);

s21_size_t s21_find_first(s21_string *num, s21_size_t from);

void s21_long_double_str_to_e_notation_str(s21_string *result, s21_string *num,
                                           char spec, bool hashtag,
                                           s21_size_t precision);

s21_size_t s21_find_a_dot(s21_string *num);

// void s21_double_to_str(s21_string *result, double value, bool need_sign, int
// precision);

#endif  // SRC_S21_CONVERT_H_

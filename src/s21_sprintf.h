#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...);

s21_size_t handler(s21_string *old_str, s21_string *to_hand, char *to_format,
                   bool *collision, va_list factor);
// поск длины до спецификатора
s21_size_t s21_find_format_len(char *to_format, bool *collision);

s21_size_t get_number(char *to_format, s21_size_t *number, va_list factor);

s21_size_t parse_number_from_string(char *to_format, s21_size_t *number);

void branching(s21_string *old_string, s21_string *to_hand, flags *f, sizes *s,
               specs *sp, va_list factor);

void integer(s21_string *number, flags *f, sizes *s, specs *sp, va_list factor);

void decimal(s21_string *number, flags *f, sizes *s, specs *sp, va_list factor);

void oct_and_hex(s21_string *number, flags *f, sizes *s, char spec,
                 va_list factor);

void string(s21_string *result, bool precision_flag, s21_size_t precision,
            va_list factor);

void character(s21_string *result, va_list factor);

void pointer(s21_string *number, va_list factor);

void size_of_line(s21_string *str);

void floating(s21_string *result, flags *f, sizes *s, va_list factor);

void ex(s21_string *result, flags *f, sizes *s, char spec, va_list factor);

void g(s21_string *result, flags *f, sizes *s, char spec, va_list factor);

s21_size_t s21_find_short(s21_string *ex_string, char spec);

void reconstruct(s21_string *ex_string, char spec, s21_size_t last);

#endif  // SRC_S21_SPRINTF_H_

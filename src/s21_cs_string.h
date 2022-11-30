#ifndef SRC_S21_CS_STRING_H_
#define SRC_S21_CS_STRING_H_

#include "s21_string.h"

// Возвращает копию строки (str), преобразованной в верхний регистр.
// В случае какой-либо ошибки следует вернуть значение NULL.
void *s21_to_upper(const char *str);

// Возвращает копию строки (str), преобразованной в нижний регистр.
// В случае какой-либо ошибки следует вернуть значение NULL
void *s21_to_lower(const char *str);

// Возвращает новую строку, в которой указанная строка (str)
// вставлена в указанную позицию (start_index) в данной строке (src).
// В случае какой-либо ошибки следует вернуть значение NULL
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

// Возвращает новую строку, в которой удаляются все начальные
// и конечные вхождения набора заданных символов (trim_chars)
// из данной строки (src).
// В случае какой - либо ошибки следует вернуть значение NULL
void *s21_trim(const char *src, const char *trim_chars);

#endif  // SRC_S21_CS_STRING_H_

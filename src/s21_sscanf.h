#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_

#include <math.h>

#include "s21_string.h"

typedef enum {
  spec_c,  // 0 Символ
  spec_d,  // 1 Знаковое десятичное целое число
  spec_i,  // 2 Знаковое целое число (может быть десятичным, восьмеричным или
           //  шестнадцатеричным)
  spec_e,  // 3 Десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_E,  // 4 Десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_f,  // 5 Десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_g,  // 6 Десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_G,  // 7 Десятичное число с плавающей точкой или научная нотация
           //  (мантисса/экспонента)
  spec_o,  // 8 Беззнаковое восьмеричное число
  spec_s,  // 9 Строка символов
  spec_u,  // 10 Беззнаковое десятичное целое число
  spec_x,  // 11 Беззнаковое шестнадцатеричное целое число (любые буквы)
  spec_X,  // 12 Беззнаковое шестнадцатеричное целое число (любые буквы)
  spec_p,  // 13 Адрес указателя
  spec_n,  // 14 Количество символов, считанных до появления %n
  spec_unknown,  // 15 Неизвестный спецификатор
} sspecs;

typedef enum lens {
  len_none,  // 0
  len_h,     // 1
  len_l,     // 2
  len_L,     // 3
} lens;

typedef struct {
  sspecs spec;
  int width;
  lens len;
  bool skip;
} specifier;

#define LLONG_MAX 0x7fffffffffffffff
#define LLONG_MIN (-LLONG_MAX - 1LL)
#define ULLONG_MAX 0xffffffffffffffff
#define INT_MAX 0x7fffffff

int s21_sscanf(const char *str, const char *format, ...);

specifier scan_specifier(char **format);
int scan_width(char **f_str);

bool is_digit(char c, int base);
s21_size_t to_digit(char c, int base);
char chr_lower(char c);
bool strstr_icase(char **str, char *pat);

bool scan(specifier spec, char **str, va_list ap, int *res, char *start);

bool parse_string(specifier spec, char **str, va_list ap);
bool parse_int(specifier spec, char **str, va_list ap);
bool parse_based_uint(specifier spec, char **str, va_list ap, int base,
                      bool neg);
bool parse_uint(specifier spec, char **str, va_list ap, bool neg);
bool parse_hex(specifier spec, char **str, va_list ap, bool neg);
bool parse_oct(specifier spec, char **str, va_list ap, bool neg);
bool parse_i_uint(specifier spec, char **str, va_list ap);
bool parse_ptr(specifier spec, char **str, va_list ap);
bool parse_float(specifier spec, char **str, va_list ap);

bool scan_int(char **str, int width, long long *dest);
bool scan_based_uint(char **str, int width, unsigned long long *dest, int base,
                     bool neg);
bool scan_float(char **str, int width, long double *dest);

long double s21_atof(char **str, int *width);
bool nan_inf(char **str, long double *dest);
bool scientific(char **str, int *width, long double *res);

#endif  // SRC_S21_SSCANF_H_

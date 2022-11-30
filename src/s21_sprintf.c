#include "s21_sprintf.h"

#include <stdarg.h>
#include <stdlib.h>

#include "s21_convert.h"
#include "s21_dynamic_string.h"
#include "s21_flags.h"
#include "s21_sizes.h"
#include "s21_specs.h"
#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list factor;
  va_start(factor, format);
  bool collision[256] = {false};
  char *specs_str = "dfsgGeExXcuiopn";
  for (s21_size_t i = 0; i < 15; i++) {
    collision[(s21_size_t)specs_str[i]] = 1;
  }
  s21_string answer;
  s21_string_init(&answer);
  s21_size_t format_len = s21_strlen(format);
  for (s21_size_t i = 0; i < format_len; i++) {
    if (format[i] != '%') {
      s21_string_push_back(&answer, format[i]);
    } else if (format[i + 1] == '%') {
      i++;
      s21_string_push_back(&answer, '%');
    } else {
      s21_string new_string;
      s21_string_init(&new_string);
      i++;
      i += handler(&answer, &new_string, (char *)format + i, collision, factor);
      s21_string_add_string(&answer, &new_string);
      s21_string_free(&new_string);
    }
  }
  s21_size_t result = answer.size;
  for (s21_size_t i = 0; i < result; i++) {
    str[i] = answer.data[i];
  }
  str[result] = '\0';
  s21_string_free(&answer);
  va_end(factor);
  return result;
}

s21_size_t handler(s21_string *old_string, s21_string *to_hand, char *to_format,
                   bool *collision, va_list factor) {
  s21_size_t format_len = s21_find_format_len(to_format, collision);
  flags f;
  sizes s;
  specs sp;
  flags_init(&f);
  sizes_init(&s);
  specs_init(&sp);
  s21_size_t i = 0;
  while (i < format_len) {
    if (set_flag(&f, to_format[i]) == false) {
      break;
    }
    i++;
  }
  if (i < format_len - 1 && to_format[i] != '.') {
    i += get_number(to_format + i, &s.width, factor);
  }
  if (i < format_len - 1 && to_format[i] == '.') {
    i++;
    i += get_number(to_format + i, &s.precision, factor);
    f.precision = true;
  }
  if (i < format_len - 1) {
    if (set_size(&s, to_format[i]) == true) {
      i++;
    }
  }
  bool status = false;
  if (i == format_len - 1) {
    status = set_spec(&sp, to_format[i]);
  }
  if (status) {
    branching(old_string, to_hand, &f, &s, &sp, factor);
  } else {
    // Ошибка обработки
  }
  return i;
}

s21_size_t s21_find_format_len(char *to_format, bool *collision) {
  s21_size_t result = 0;
  while (collision[(int)*to_format] == 0) {
    to_format++;
    result++;
  }
  return result + 1;
}

s21_size_t get_number(char *to_format, s21_size_t *number, va_list factor) {
  s21_size_t result = 0;
  if (to_format[result] == '*') {
    *number = va_arg(factor, s21_size_t);
    result = 1;
  } else {
    result += parse_number_from_string(to_format, number);
  }
  return result;
}

s21_size_t parse_number_from_string(char *to_format, s21_size_t *number) {
  s21_size_t result = 0;
  s21_size_t result_number = 0;
  while ('0' <= to_format[result] && to_format[result] <= '9') {
    result_number *= 10;
    result_number += to_format[result] - 48;
    result++;
  }
  *number = result_number;
  return result;
}

void branching(s21_string *old_string, s21_string *to_hand, flags *f, sizes *s,
               specs *sp, va_list factor) {
  s21_string result;
  s21_string_init(&result);
  if (sp->d == true || sp->i == true || sp->o == true || sp->u == true ||
      sp->x == true || sp->X == true) {
    integer(&result, f, s, sp, factor);
  } else if (sp->s == true) {
    string(&result, f->precision, s->precision, factor);
  } else if (sp->p == true) {
    pointer(&result, factor);
  } else if (sp->n == true) {
    size_of_line(old_string);
  } else if (sp->c == true) {
    character(&result, factor);
  } else if (sp->f == true) {
    floating(&result, f, s, factor);
  } else if (sp->e == true) {
    ex(&result, f, s, 'e', factor);
  } else if (sp->E == true) {
    ex(&result, f, s, 'E', factor);
  } else if (sp->g == true) {
    g(&result, f, s, 'g', factor);
  } else if (sp->G == true) {
    g(&result, f, s, 'G', factor);
  }
  if (result.size < s->width && sp->n == false) {
    if (f->minus == true) {
      s21_string_add_string(to_hand, &result);
      for (s21_size_t i = 0; i < s->width - result.size; i++) {
        s21_string_push_back(to_hand, ' ');
      }
    } else {
      char char_to_replace = ' ';
      if (f->zero == true && sp->s == false) {
        char_to_replace = '0';
        bool minus = false;
        if (result.data[0] == '-') {
          s21_string_push_back(to_hand, '-');
          minus = true;
        }
        for (s21_size_t i = 0; i < s->width - result.size; i++) {
          s21_string_push_back(to_hand, char_to_replace);
        }
        if (minus == true) {
          result.data++;
          result.size--;
        }
        s21_string_add_string(to_hand, &result);
        if (minus) {
          result.data--;
          result.size++;
        }
      } else {
        for (s21_size_t i = 0; i < s->width - result.size; i++) {
          s21_string_push_back(to_hand, char_to_replace);
        }
        s21_string_add_string(to_hand, &result);
      }
    }
  } else {
    s21_string_add_string(to_hand, &result);
  }
  s21_string_free(&result);
}

void integer(s21_string *number, flags *f, sizes *s, specs *sp,
             va_list factor) {
  if (sp->d == true || sp->i == true || sp->u == true) {
    decimal(number, f, s, sp, factor);
  } else if (sp->o == true) {
    oct_and_hex(number, f, s, 'o', factor);
  } else if (sp->x == true) {
    oct_and_hex(number, f, s, 'x', factor);
  } else if (sp->X == true) {
    oct_and_hex(number, f, s, 'X', factor);
  }
}

void decimal(s21_string *number, flags *f, sizes *s, specs *sp,
             va_list factor) {
  void *num = malloc(sizeof(long int));
  if (sp->d == true || sp->i == true) {
    if (s->l == false && s->h == false) {
      *((int *)num) = va_arg(factor, int);
    } else if (s->l == true) {
      *((long *)num) = va_arg(factor, long);
    } else if (s->h == true) {
      *((short *)num) = (short)va_arg(factor, int);
    }
  } else if (sp->u == true) {
    if (s->l == false && s->h == false) {
      *((unsigned int *)num) = va_arg(factor, unsigned int);
    } else if (s->l == true) {
      *((unsigned long int *)num) = va_arg(factor, unsigned long int);
    } else if (s->h == true) {
      *((unsigned short *)num) = (unsigned short)va_arg(factor, unsigned int);
    }
  }
  if (sp->u == false) {
    if ((s->l && *((long *)num) < 0) || (!s->l && !s->h && *((int *)num) < 0) ||
        (s->h && *((short *)num) < 0)) {
      s21_string_push_back(number, '-');
      *((long *)num) *= -1;
    } else if (f->plus == true) {
      s21_string_push_back(number, '+');
    } else if (f->space == true) {
      s21_string_push_back(number, ' ');
    }
    if (s->l == true) {
      s21_integer_to_str(number, *((long *)num), 'd',
                         s->precision * f->precision, false);
    } else if (s->h == true) {
      s21_integer_to_str(number, *((short *)num), 'd',
                         s->precision * f->precision, false);
    } else if (s->h == false && s->l == false) {
      s21_integer_to_str(number, *((int *)num), 'd',
                         s->precision * f->precision, false);
    }
  } else {
    if (s->l == true) {
      s21_integer_to_str(number, *((unsigned long int *)num), 'd',
                         s->precision * f->precision, false);
    } else if (s->h == true) {
      s21_integer_to_str(number, *((unsigned short *)num), 'd',
                         s->precision * f->precision, false);
    } else if (s->h == false && s->l == false) {
      s21_integer_to_str(number, *((unsigned int *)num), 'd',
                         s->precision * f->precision, false);
    }
  }
  free(num);
}

void oct_and_hex(s21_string *number, flags *f, sizes *s, char spec,
                 va_list factor) {
  unsigned int num = va_arg(factor, unsigned int);
  if (f->hashtag == true && num != 0) {
    s21_string_push_back(number, '0');
    if (spec == 'x' || spec == 'X') {
      s21_string_push_back(number, spec);
    }
  }
  s21_integer_to_str(number, num, spec, s->precision * f->precision,
                     f->hashtag);
}

void string(s21_string *result, bool precision_flag, s21_size_t precision,
            va_list factor) {
  const char *str = va_arg(factor, const char *);
  s21_size_t str_len = s21_strlen(str);
  s21_size_t n = 0;
  if (precision_flag == 0) {
    n = str_len;
  } else {
    if (precision < str_len) {
      n = precision;
    } else {
      n = str_len;
    }
  }
  for (s21_size_t i = 0; i < n; i++) {
    s21_string_push_back(result, str[i]);
  }
}

void pointer(s21_string *number, va_list factor) {
  s21_string core_number;
  s21_string_init(&core_number);
  long value = va_arg(factor, long);
  do {
    char symbol = value % 16;
    if (0 <= symbol && symbol <= 9) {
      symbol += '0';
    } else {
      symbol += 87;
    }
    s21_string_push_back(&core_number, symbol);
    value /= 16;
  } while (value > 0);
  s21_string_push_back(number, '0');
  s21_string_push_back(number, 'x');
  for (s21_size_t i = core_number.size - 1; i > 0; i--) {
    s21_string_push_back(number, core_number.data[i]);
  }
  s21_string_push_back(number, core_number.data[0]);
  s21_string_free(&core_number);
}

void size_of_line(s21_string *str) {
  s21_size_t answer = str->size;
  s21_integer_to_str(str, answer, 'd', 0, false);
}

void character(s21_string *result, va_list factor) {
  char a = va_arg(factor, int);
  s21_string_push_back(result, a);
}

void floating(s21_string *result, flags *f, sizes *s, va_list factor) {
  bool dnum = true;
  bool ldnum = true;
  void *num = s21_NULL;
  if (s->L == true) {
    num = malloc(sizeof(long double));
    *((long double *)num) = va_arg(factor, long double);
    if (*((long double *)num) < 0) {
      ldnum = false;
    }
  } else {
    num = malloc(sizeof(double));
    *((double *)num) = va_arg(factor, double);
    if (*((double *)num) < 0) {
      dnum = false;
    }
  }
  if (f->plus && dnum == true && ldnum == true) {
    s21_string_push_back(result, '+');
  }
  if (f->space == true && dnum == true && ldnum == true) {
    s21_string_push_back(result, ' ');
  }
  if (dnum == false || ldnum == false) {
    s21_string_push_back(result, '-');
    if (s->L == true) {
      *((long double *)num) *= -1;
    } else {
      *((double *)num) *= -1;
    }
  }
  long double value = 0;
  if (s->L) {
    value = *((long double *)num);
  } else {
    value = (long double)*((double *)num);
  }
  s21_long_double_to_str(result, value, f->hashtag, s->precision);
  free(num);
}

void ex(s21_string *result, flags *f, sizes *s, char spec, va_list factor) {
  s21_string core_number;
  s21_string_init(&core_number);
  s21_size_t original_precision = s->precision;
  if (s->L == true) {
    s->precision = 4951;
  } else {
    s->precision = 324;
  }
  bool hashtag = f->hashtag;
  f->hashtag = true;
  va_list temp_factor;
  va_copy(temp_factor, factor);
  floating(&core_number, f, s, temp_factor);
  s21_size_t dot = s21_find_a_dot(&core_number);
  s->precision = s21_find_first(&core_number, dot + 1) + original_precision;
  s21_string_free(&core_number);
  s21_string_init(&core_number);
  floating(&core_number, f, s, factor);
  bool minus = false;
  if (core_number.data[0] == '-') {
    s21_string_push_back(result, '-');
    core_number.data++;
    core_number.size--;
    core_number.capacity--;
    minus = true;
  }
  f->hashtag = hashtag;
  s->precision = original_precision;
  s21_long_double_str_to_e_notation_str(result, &core_number, spec, f->hashtag,
                                        s->precision);
  if (minus == true) {
    core_number.data--;
  }
  s21_string_free(&core_number);
}

void g(s21_string *result, flags *f, sizes *s, char spec, va_list factor) {
  char new_spec = 0;
  if (spec == 'g') {
    new_spec = 'e';
  } else {
    new_spec = 'E';
  }
  if (s->precision == 0) {
    ex(result, f, s, new_spec, factor);
    return;
  } else {
    s->precision--;
  }
  s21_string float_string;
  s21_string_init(&float_string);
  s21_size_t original_precision = s->precision;
  if (s->L == true) {
    s->precision = 4951;
  } else {
    s->precision = 324;
  }
  bool hashtag = f->hashtag;
  f->hashtag = true;
  va_list temp_factor;
  va_copy(temp_factor, factor);
  floating(&float_string, f, s, temp_factor);
  s21_size_t dot = s21_find_a_dot(&float_string);
  s->precision =
      s21_find_first(&float_string, dot + 1) + original_precision - 1;
  s21_string_free(&float_string);
  s21_string_init(&float_string);
  va_copy(temp_factor, factor);
  floating(&float_string, f, s, temp_factor);
  s21_string ex_string;
  s21_string_init(&ex_string);
  va_copy(temp_factor, factor);
  f->hashtag = hashtag;
  s->precision = original_precision;
  ex(&ex_string, f, s, new_spec, factor);
  s21_size_t last = s21_find_short(&ex_string, new_spec);
  reconstruct(&ex_string, new_spec, last);
  if ((float_string.size == 1 && float_string.data[0] == '0' &&
       ex_string.data[0] != '0') ||
      float_string.size > ex_string.size) {
    ex_string.data[ex_string.size] = '\0';
    s21_string_add_string(result, &ex_string);
  } else {
    float_string.data[float_string.size] = '\0';
    s21_string_add_string(result, &float_string);
  }
  s21_string_free(&float_string);
  s21_string_free(&ex_string);
}

s21_size_t s21_find_short(s21_string *ex_string, char spec) {
  s21_size_t result = 0;
  for (s21_size_t i = 2; ex_string->data[i] != spec; i++) {
    if (ex_string->data[i] != '0') {
      result = i;
    }
  }
  return result;
}

void reconstruct(s21_string *ex_string, char spec, s21_size_t last) {
  s21_string temp;
  s21_string_init(&temp);
  s21_size_t i = 0;
  while (i <= last) {
    s21_string_push_back(&temp, ex_string->data[i]);
    i++;
  }
  while (ex_string->data[i] != spec) {
    i++;
  }
  while (i < ex_string->size) {
    s21_string_push_back(&temp, ex_string->data[i]);
    i++;
  }
  s21_string_free(ex_string);
  s21_string_init(ex_string);
  s21_string_add_string(ex_string, &temp);
  s21_string_free(&temp);
}

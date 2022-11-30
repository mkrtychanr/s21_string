#include "s21_convert.h"

#include <math.h>

#include "s21_dynamic_string.h"
#include "s21_string.h"
#include "s21_vector.h"

char *s21_int_to_str(int value) {
  bool need_sign = false;
  char *result = s21_NULL;
  s21_size_t len = 0;
  int temp = value;
  char sign = '+';
  if (value < 0) {
    sign = '-';
    value = temp = -value;
    need_sign = true;
  }
  if (value == 0) {
    len = 1;
  } else {
    while (temp != 0) {
      temp /= 10;
      len++;
    }
  }
  result = (char *)calloc(len + 1 + need_sign, sizeof(char));
  if (need_sign) result[0] = sign;
  for (int i = len - 1; i >= 0; i--) {
    result[i + need_sign] = (value % 10) + '0';
    value /= 10;
  }

  return result;
}

void s21_to_precision(s21_string *result, s21_string *core_number,
                      s21_size_t precision, s21_size_t i_start) {
  if (core_number->size < precision) {
    for (s21_size_t i = i_start; i < precision - core_number->size; i++) {
      s21_string_push_back(result, '0');
    }
  }
  for (s21_size_t i = core_number->size - 1; i > 0; i--) {
    s21_string_push_back(result, core_number->data[i]);
  }
  s21_string_push_back(result, core_number->data[0]);
}

void s21_integer_to_str(s21_string *result, s21_size_t value, char spec,
                        s21_size_t precision, bool need_zero) {
  s21_string core_number;
  s21_string_init(&core_number);
  s21_size_t denominator = 0;
  s21_size_t prefix = 0;
  s21_set_denominator_and_prefix(&denominator, &prefix, spec);
  do {
    s21_size_t symbol = value % denominator;
    if (symbol <= 9) {
      symbol += '0';
    } else {
      symbol += prefix;
    }
    s21_string_push_back(&core_number, symbol);
    value /= denominator;
  } while (value > 0);
  s21_to_precision(
      result, &core_number, precision,
      (core_number.size < precision) && (denominator == 8) && need_zero);
  s21_string_free(&core_number);
}

bool s21_set_denominator_and_prefix(s21_size_t *denominator, s21_size_t *prefix,
                                    char spec) {
  bool result = true;
  *prefix = '0';
  switch (spec) {
    case 'd':
      *denominator = 10;
      break;
    case 'o':
      *denominator = 8;
      break;
    case 'x':
      *denominator = 16;
      *prefix += 39;
      break;
    case 'X':
      *denominator = 16;
      *prefix += 7;
      break;
    default:
      result = false;
      break;
  }
  return result;
}

void s21_long_double_to_str(s21_string *result, long double num, bool hashtag,
                            s21_size_t precision) {
  s21_size_t left = (s21_size_t)num;
  s21_vector right;
  s21_vector_init(&right);
  num -= left;
  if (precision == 0) {
    s21_size_t temp = num * 10;
    if (temp > 4) {
      left++;
    }
  } else {
    for (s21_size_t i = 0; i < precision + 1; i++) {
      s21_size_t temp = num;
      num -= temp;
      s21_vector_push_back(&right, (s21_size_t)(num * 10));
      num *= 10;
    }
    if (right.data[precision] > 4) {
      right.data[precision - 1]++;
      for (s21_size_t i = precision - 1; i > 0; i--) {
        if (right.data[i] == 10) {
          right.data[i] = 0;
          right.data[i - 1]++;
          continue;
        }
        break;
      }
      if (right.data[0] == 10) {
        right.data[0] = 0;
        left++;
      }
    }
    right.size--;
  }
  s21_integer_to_str(result, left, 'd', 0, false);
  if (hashtag == true || precision != 0) {
    s21_string_push_back(result, '.');
  }
  if (precision != 0) {
    for (s21_size_t i = 0; i < right.size; i++) {
      s21_string_push_back(result, right.data[i] + '0');
    }
  }
  s21_vector_free(&right);
}

void s21_long_double_str_to_e_notation_str(s21_string *result, s21_string *num,
                                           char spec, bool hashtag,
                                           s21_size_t precision) {
  s21_size_t dot = s21_find_a_dot(num);
  s21_vector right;
  s21_vector_init(&right);
  if (dot > 1) {
    s21_string_push_back(result, num->data[0]);
    s21_size_t i = 1;
    while (i < num->size && i <= precision) {
      if (num->data[i] == '.') {
        precision++;
      } else {
        s21_vector_push_back(&right, num->data[i] - '0');
      }
      i++;
    }
    while (i <= precision) {
      s21_vector_push_back(&right, 0);
      i++;
    }
    s21_fill(result, &right, spec, hashtag, dot, '+');
  } else if (dot == 1) {
    if (num->data[0] == '0') {
      s21_size_t counter = s21_find_first(num, 2);
      if (counter == 0) {
        s21_string_push_back(result, '0');
        if (hashtag == true || precision != 0) {
          s21_string_push_back(result, '.');
        }
        for (s21_size_t i = 0; i < precision; i++) {
          s21_string_push_back(result, '0');
        }
        s21_string_push_back(result, spec);
        s21_string_push_back(result, '+');
        s21_string_push_back(result, '0');
        s21_string_push_back(result, '0');

      } else {
        s21_string_push_back(result, num->data[counter + 1]);
        s21_size_t i = counter + 2;
        while (i < num->size && i < precision + counter + 2) {
          s21_vector_push_back(&right, num->data[i] - '0');
          i++;
        }
        while (i < precision + counter + 2) {
          s21_vector_push_back(&right, 0);
        }
        s21_fill(result, &right, spec, hashtag, counter + 1, '-');
      }
    } else {
      s21_string_push_back(result, num->data[0]);
      s21_size_t i = 2;
      while (i < num->size && i < precision + 2) {
        s21_vector_push_back(&right, num->data[i] - '0');
        i++;
      }
      while (i < precision + 2) {
        s21_vector_push_back(&right, 0);
        i++;
      }
      s21_fill(result, &right, spec, hashtag, dot, '+');
    }
  }
  s21_vector_free(&right);
}

void s21_fill(s21_string *result, s21_vector *right, char spec, bool hashtag,
              s21_size_t dot, char sign) {
  if (hashtag == true || 0 < right->size) {
    s21_string_push_back(result, '.');
  }
  for (s21_size_t i = 0; i < right->size; i++) {
    s21_string_push_back(result, right->data[i] + '0');
  }
  s21_string_push_back(result, spec);
  s21_string_push_back(result, sign);
  if (dot - 1 < 10) {
    s21_string_push_back(result, '0');
    s21_string_push_back(result, dot - 1 + '0');
  } else {
    s21_integer_to_str(result, dot - 1, 'd', 0, false);
  }
}

s21_size_t s21_find_first(s21_string *num, s21_size_t from) {
  s21_size_t result = 0;
  for (s21_size_t i = from; i < num->size; i++) {
    if (num->data[i] != '0') {
      result = i - 1;
      break;
    }
  }
  return result;
}

s21_size_t s21_find_a_dot(s21_string *num) {
  s21_size_t result = 0;
  for (s21_size_t i = 1; i < num->size; i++) {
    if (num->data[i] == '.') {
      result = i;
      break;
    }
  }
  return result;
}

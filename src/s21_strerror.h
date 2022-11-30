#ifndef SRC_S21_STRERROR_H_
#define SRC_S21_STRERROR_H_

#include "s21_string.h"

#ifdef __linux
#define MAX_ERRNO 134
#define UNKNOWN_ERROR "Unknown error "
#endif
#ifdef __APPLE__
#define MAX_ERRNO 107
#define UNKNOWN_ERROR "Unknown error: "
#endif

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке. Нужно объявить макросы,
// содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
// осуществляется с помощью директив.
char *s21_strerror(int errnum);

#endif  // SRC_S21_STRERROR_H_

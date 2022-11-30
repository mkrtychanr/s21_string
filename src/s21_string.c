#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result = s21_NULL;
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    if (*ptr == c) {
      result = ptr;
      break;
    }
    ptr++;
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int answer = 0;
  unsigned char *ptr1 = (unsigned char *)str1;
  unsigned char *ptr2 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (*ptr1 != *ptr2) {
      answer = *ptr1 - *ptr2;
      break;
    }
    ptr1++;
    ptr2++;
  }
  return answer;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    *(((char *)dest) + i) = *(((char *)src) + i);
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *temp = calloc(n + 1, sizeof(unsigned char));
  unsigned char *ptr = (unsigned char *)src;
  for (s21_size_t i = 0; i < n && *ptr != '\0'; i++) {
    temp[i] = *ptr;
    ptr++;
    if (*ptr == '\0') temp[i + 1] = *ptr;
  }
  dest = s21_memcpy(dest, temp, n);
  free(temp);
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    *(ptr++) = c;
  }
  return (void *)str;
}

char *s21_strcat(char *dest, const char *src) {
  char *t = (char *)src;
  int i = 0;
  while (dest[i] != '\0') {
    i++;
  }
  while (*t != '\0') {
    dest[i++] = *t++;
  }
  dest[i] = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t src_len = s21_strlen(src);
  if (src_len < n) {
    n = src_len;
  }
  dest = realloc(dest, (dest_len + n + 1) * sizeof(char));
  char *ptr = dest + dest_len;
  for (s21_size_t i = 0; i < n; i++) {
    *ptr = src[i];
    ptr++;
  }
  *ptr = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  char *ptr = (char *)str;
  while (*ptr != '\0') {
    if (*ptr == c) {
      result = ptr;
      break;
    }
    ptr++;
  }
  if (*ptr == c) {
    result = ptr;
  }
  return result;
}

int s21_strcmp(const char *str1, const char *str2) {
  s21_size_t str1_len = s21_strlen(str1);
  s21_size_t str2_len = s21_strlen(str2);
  s21_size_t n = (str1_len > str2_len) ? str1_len : str2_len;
  return s21_memcmp(str1, str2, n);
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  return s21_memcmp(str1, str2, n);
}

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t src_len = s21_strlen(src);
  return (char *)s21_memcpy(dest, src, src_len);
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  return (char *)s21_memcpy(dest, src, n);
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  s21_size_t str1_len = s21_strlen(str1);
  s21_size_t str2_len = s21_strlen(str2);
  int flag = 0;
  int collision[256] = {0};
  for (s21_size_t i = 0; i < str2_len; i++) {
    collision[(int)str2[i]] = 1;
  }
  for (s21_size_t i = 0; i < str1_len && !flag; i++) {
    if (collision[(int)str1[i]] == 1) {
      result = i;
      flag = 1;
    }
  }
  if (!flag) {
    result = str1_len;
  }
  return result;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t answer = 0;
  char *ptr = (char *)str;
  while (*ptr != '\0') {
    answer++;
    ptr++;
  }
  return answer;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  s21_size_t str1_len = s21_strlen(str1);
  s21_size_t str2_len = s21_strlen(str2);
  int collision[256] = {0};
  for (s21_size_t i = 0; i < str2_len; i++) {
    collision[(int)str2[i]] = 1;
  }
  for (s21_size_t i = 0; i < str1_len; i++) {
    if (collision[(int)str1[i]] == 1) {
      result = (char *)(str1 + i);
      break;
    }
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  char *ptr = (char *)str;
  while (*ptr != '\0') {
    if (*ptr == c) {
      result = ptr;
    }
    ptr++;
  }
  if (*ptr == c) {
    result = ptr;
  }
  return result;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t str1_len = s21_strlen(str1);
  s21_size_t str2_len = s21_strlen(str2);
  s21_size_t result = str1_len;
  int collision[256] = {0};
  for (s21_size_t i = 0; i < str2_len; i++) {
    collision[(int)str2[i]] = 1;
  }
  for (s21_size_t i = 0; i < str1_len; i++) {
    if (collision[(int)str1[i]] != 1) {
      result = i;
      break;
    }
  }
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  s21_size_t haystack_len = s21_strlen(haystack);
  s21_size_t needle_len = s21_strlen(needle);
  for (s21_size_t i = 0; i < haystack_len; i++) {
    int find = 1;
    for (s21_size_t j = 0; j < needle_len; j++) {
      if (haystack[i + j] != needle[j]) {
        find = 0;
        break;
      }
    }
    if (find == 1) {
      result = (char *)haystack + i;
      break;
    }
  }
  return result;
}

static char *olds;

char *s21_strtok(char *str, const char *delim) {
  char *token = s21_NULL;
  int flag = 1;

  if (!str) str = olds;

  str += s21_strspn(str, delim);
  if (!*str) {
    olds = str;
    flag = 0;
  }
  if (flag) {
    token = str;
    str = s21_strpbrk(str, delim);
    if (str) {
      *str = '\0';
      olds = str + 1;
    } else {
      olds = token + s21_strlen(token);
    }
  }
  return token;
}

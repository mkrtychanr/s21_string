#include "check_s21_string.h"

START_TEST(test_s21_memchr) {
  const char *s = "Abracadabra";
  const char *empty = "";
  ck_assert_ptr_eq(memchr(s, 'c', 100), s21_memchr(s, 'c', 100));
  ck_assert_ptr_eq(memchr(s, 'd', 1), s21_memchr(s, 'd', 1));
  ck_assert_ptr_eq(memchr(s, 'A', 1), s21_memchr(s, 'A', 1));
  ck_assert_ptr_eq(memchr(empty, 'A', 0), s21_memchr(empty, 'A', 0));
  for (char c = -128; c < 127; c++) {
    for (s21_size_t i = 0; i < 15; i++) {
      ck_assert_ptr_eq(memchr(s, c, i), s21_memchr(s, c, i));
      ck_assert_ptr_eq(memchr(empty, c, i), s21_memchr(empty, c, i));
    }
  }
}
END_TEST

// в стандарте не указано возращает memcmp -1, 0, 1 или разницу чаров, поэтому
// приходится чекать так иначе на маке и убунте тест выдаёт разное
int both_lthteq_zero(int a, int b) {
  return ((a < 0) && (b < 0)) || ((a == 0) && (b == 0)) || ((a > 0) && (b > 0));
}

START_TEST(test_s21_memcmp) {
  const char *s1 = "AAAAZAAAA";
  const char *s2 = "AAAAB";

  for (int i = -15; i < 15; i++) {
    ck_assert(both_lthteq_zero(memcmp(s1, s2, i), s21_memcmp(s1, s2, i)));
    ck_assert(both_lthteq_zero(memcmp(s2, s1, i), s21_memcmp(s2, s1, i)));
  }
}
END_TEST

START_TEST(test_s21_memcpy) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));
  char *str1 = "AbraCadabra";
  char *str2 = "Hello World";
  char *str3 = "Python sucks";
  for (s21_size_t i = 0; i < 15; i++) {
    dest1 = memcpy(dest1, str1, i);
    dest2 = s21_memcpy(dest2, str1, i);
    ck_assert_str_eq(dest1, dest2);

    dest1 = memcpy(dest1, str2, i);
    dest2 = s21_memcpy(dest2, str2, i);
    ck_assert_str_eq(dest1, dest2);

    dest1 = memcpy(dest1, str3, i);
    dest2 = s21_memcpy(dest2, str3, i);
    ck_assert_str_eq(dest1, dest2);
  }
  free(dest1);
  free(dest2);
}
END_TEST

START_TEST(test_s21_memmove) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));
  char *str1 = "AbraCadabra";
  char *str2 = "Hello World";
  char *str3 = "Python sucks";
  for (s21_size_t i = 0; i < 15; i++) {
    dest1 = memmove(dest1, str1, i);
    dest2 = s21_memmove(dest2, str1, i);
    ck_assert_str_eq(dest1, dest2);

    dest1 = memmove(dest1, str2, i);
    dest2 = s21_memmove(dest2, str2, i);
    ck_assert_str_eq(dest1, dest2);

    dest1 = memmove(dest1, str3, i);
    dest2 = s21_memmove(dest2, str3, i);
    ck_assert_str_eq(dest1, dest2);
  }
  free(dest1);
  free(dest2);
}
END_TEST

START_TEST(test_s21_memset) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));
  for (s21_size_t i = 0; i < 100; i++) {
    char c = (char)((i * 7) % 127);
    dest1 = memset(dest1, c, i);
    dest2 = s21_memset(dest2, c, i);
    ck_assert_str_eq(dest1, dest2);
  }
  dest1 = memset(dest1, '\0', 15);
  dest2 = s21_memset(dest2, '\0', 15);
  ck_assert_str_eq(dest1, dest2);
  free(dest1);
  free(dest2);
}
END_TEST

START_TEST(test_s21_strcat) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));

  dest1 = strcat(dest1, "cat");
  dest2 = s21_strcat(dest2, "cat");
  ck_assert_str_eq(dest1, dest2);

  dest1 = strcat(dest1, "dog");
  dest2 = s21_strcat(dest2, "dog");
  ck_assert_str_eq(dest1, dest2);

  dest1 = strcat(dest1, "frog");
  dest2 = s21_strcat(dest2, "frog");
  ck_assert_str_eq(dest1, dest2);

  free(dest1);
  free(dest2);
}
END_TEST

START_TEST(test_s21_strncat) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));

  for (s21_size_t i = 0; i < 15; i++) {
    dest1 = strncat(dest1, "1234567890", i);
    dest2 = s21_strncat(dest2, "1234567890", i);
    ck_assert_str_eq(dest1, dest2);
  }
  free(dest1);
  free(dest2);
}
END_TEST

START_TEST(test_s21_strchr) {
  const char *s = "Abracadabra";
  const char *empty = "";

  for (char c = 0; c < 127; c++) {
    ck_assert_ptr_eq(strchr(s, c), s21_strchr(s, c));
    ck_assert_ptr_eq(strchr(empty, c), s21_strchr(empty, c));
  }
}
END_TEST

START_TEST(test_s21_strcmp) {
  const char *s1 = "AAAAZAAAA";
  const char *s2 = "AAAAB";

  ck_assert(both_lthteq_zero(strcmp(s1, s2), s21_strcmp(s1, s2)));
  ck_assert(both_lthteq_zero(strcmp(s2, s1), s21_strcmp(s2, s1)));
}
END_TEST

START_TEST(test_s21_strncmp) {
  const char *s1 = "AAAAZAAAA";
  const char *s2 = "AAAAB";

  for (int i = -15; i < 15; i++) {
    ck_assert(both_lthteq_zero(strncmp(s1, s2, i), s21_strncmp(s1, s2, i)));
    ck_assert(both_lthteq_zero(strncmp(s2, s1, i), s21_strncmp(s2, s1, i)));
  }
}
END_TEST

START_TEST(test_s21_strcpy) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));
  char *str1 = "AbraCadabra";
  char *str2 = "Hello World";
  char *str3 = "Python sucks";
  dest1 = strcpy(dest1, str1);
  dest2 = s21_strcpy(dest2, str1);
  ck_assert_str_eq(dest1, dest2);

  dest1 = strcpy(dest1, str2);
  dest2 = s21_strcpy(dest2, str2);
  ck_assert_str_eq(dest1, dest2);

  dest1 = strcpy(dest1, str3);
  dest2 = s21_strcpy(dest2, str3);
  ck_assert_str_eq(dest1, dest2);

  free(dest1);
  free(dest2);
}
END_TEST

START_TEST(test_s21_strncpy) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));
  char *str1 = "AbraCadabra";
  char *str2 = "Hello World";
  char *str3 = "Python sucks";
  for (s21_size_t i = 0; i < 15; i++) {
    dest1 = strncpy(dest1, str1, i);
    dest2 = s21_strncpy(dest2, str1, i);
    ck_assert_str_eq(dest1, dest2);

    dest1 = strncpy(dest1, str2, i);
    dest2 = s21_strncpy(dest2, str2, i);
    ck_assert_str_eq(dest1, dest2);

    dest1 = strncpy(dest1, str3, i);
    dest2 = s21_strncpy(dest2, str3, i);
    ck_assert_str_eq(dest1, dest2);
  }
  free(dest1);
  free(dest2);
}
END_TEST

START_TEST(test_s21_strcspn) {
  char *str1 = "zzzaba";
  char *str2 = "ab";
  char *str3 = "kopa";
  char *str4 = "abcd";
  char *str5 = "x";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
  ck_assert_int_eq(strcspn(str3, str4), s21_strcspn(str3, str4));

  // if no match, return strlen(str1)
  ck_assert_int_eq(strcspn(str1, str5), s21_strcspn(str1, str5));
}
END_TEST

START_TEST(test_s21_strlen) {
  char *str1 = "Hello World";
  char *str2 = "Python sucks";
  char *str3 = "C is the best";
  char *str4 = "";
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));
  ck_assert_int_eq(s21_strlen(str3), strlen(str3));
  ck_assert_int_eq(s21_strlen(str4), strlen(str4));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char *str1 = "zzzaba";
  char *str2 = "ab";
  char *str3 = "kopa";
  char *str4 = "abcd";
  char *str5 = "z";

  ck_assert_str_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
  ck_assert_str_eq(strpbrk(str3, str4), s21_strpbrk(str3, str4));
  ck_assert_str_eq(strpbrk(str1, str5), s21_strpbrk(str1, str5));
}
END_TEST

START_TEST(test_s21_strrchr) {
  char *str1 = "zzzaba";
  char *empty = "";

  for (int c = 0; c < 127; c++) {
    ck_assert_ptr_eq(strrchr(str1, c), s21_strrchr(str1, c));
    ck_assert_ptr_eq(strrchr(empty, c), s21_strrchr(empty, c));
  }
}
END_TEST

START_TEST(test_s21_strspn) {
  // if start wirh
  ck_assert_int_eq(strspn("school21", "chs"), s21_strspn("school21", "chs"));
  // if not start with
  ck_assert_int_eq(strspn("sber", "yandex"), s21_strspn("sber", "yandex"));
  // if full match
  ck_assert_int_eq(strspn("sber", "sberbank"), s21_strspn("sber", "sberbank"));
}
END_TEST

START_TEST(test_s21_strstr) {
  ck_assert_ptr_eq(strstr("school21", "ool"), s21_strstr("school21", "ool"));
  ck_assert_ptr_eq(strstr("school21", "21"), s21_strstr("school21", "21"));
  ck_assert_ptr_eq(strstr("school21", "c"), s21_strstr("school21", "c"));
  ck_assert_ptr_eq(strstr("school21", "sch"), s21_strstr("school21", "sch"));
  ck_assert_ptr_eq(strstr("school", "work"), s21_strstr("school", "work"));
}
END_TEST

START_TEST(test_s21_strtok) {
  char str1[25] = "school21 is the best";
  char str2[25] = "school21 is the best";
  char *token1 = strtok(str1, " ");
  char *token2 = s21_strtok(str2, " ");
  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = strtok(NULL, " ");
    token2 = s21_strtok(NULL, " ");
  }
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("S21 String");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memmove);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strcat);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strcmp);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strcpy);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strspn);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_string() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_string_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

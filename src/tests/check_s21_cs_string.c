#include "check_s21_cs_string.h"

START_TEST(test_s21_to_upper) {
  char *str1 = "school21";
  char *str2 = "SCHOOL21";
  char *str3 = "ScHoOl21";
  char *str4 = "";
  char *str5 = "{}[]()";
  char *str6 = s21_NULL;

  ck_assert_str_eq(s21_to_upper(str1), str2);
  ck_assert_str_eq(s21_to_upper(str3), str2);
  ck_assert_str_eq(s21_to_upper(str4), str4);
  ck_assert_str_eq(s21_to_upper(str5), str5);
  ck_assert_ptr_eq(s21_to_upper(str6), str6);
  ck_assert_int_eq(s21_strlen(s21_to_upper(str1)), strlen(str2));
}
END_TEST

START_TEST(test_s21_to_lower) {
  char *str1 = "school21";
  char *str2 = "SCHOOL21";
  char *str3 = "ScHoOl21";
  char *str4 = "";
  char *str5 = "{}[]()";
  char *str6 = s21_NULL;

  ck_assert_str_eq(s21_to_lower(str2), str1);
  ck_assert_str_eq(s21_to_lower(str3), str1);
  ck_assert_str_eq(s21_to_lower(str4), str4);
  ck_assert_str_eq(s21_to_lower(str5), str5);
  ck_assert_ptr_eq(s21_to_lower(str6), str6);
  ck_assert_int_eq(s21_strlen(s21_to_upper(str1)), strlen(str2));
}
END_TEST

START_TEST(test_s21_insert) {
  char *str1 = "school21 ";
  char *str2 = "is the best";
  char *str3 = "school21 is the best";
  char *str4 = "school21  the best";
  char *str5 = "is";

  ck_assert_str_eq(s21_insert(str1, str2, 9), str3);
  ck_assert_str_eq(s21_insert(str1, s21_NULL, 2), str1);
  ck_assert_str_eq(s21_insert(str4, str5, 9), str3);

  ck_assert_ptr_eq(s21_insert(str1, str2, 10), s21_NULL);
  ck_assert_ptr_eq(s21_insert(s21_NULL, str2, 2), s21_NULL);
}
END_TEST

START_TEST(test_s21_trim) {
  ck_assert_str_eq(s21_trim("-=1--1=--=", "-="), "1--1");
  ck_assert_str_eq(s21_trim("1--1=--=", "-="), "1--1");
  ck_assert_str_eq(s21_trim("1--1-----------------------------", "-="), "1--1");
  ck_assert_str_eq(s21_trim("", "-="), "");

  ck_assert_ptr_eq(s21_trim(s21_NULL, " "), s21_NULL);
  ck_assert_ptr_eq(s21_trim("-test-", s21_NULL), s21_NULL);
}
END_TEST

Suite *s21_cs_string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("S21 C# String");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_to_upper);
  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_insert);
  tcase_add_test(tc_core, test_s21_trim);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_cs_string() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_cs_string_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

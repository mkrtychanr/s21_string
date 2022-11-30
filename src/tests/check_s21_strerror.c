
#include "check_s21_strerror.h"

START_TEST(test_s21_strerror) {
  for (int i = -10; i < 256; i++) {
    char *str = s21_strerror(i);

    ck_assert_str_eq(str, strerror(i));
    if (i < 0 || i >= MAX_ERRNO) {
      free(str);
    }
  }
}
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("S21 String Error");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strerror);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_strerror() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_strerror_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

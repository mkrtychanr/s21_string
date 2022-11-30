#include "tests/check_s21_cs_string.h"
#include "tests/check_s21_sprintf.h"
#include "tests/check_s21_sscanf.h"
#include "tests/check_s21_strerror.h"
#include "tests/check_s21_string.h"

int main() {
  int no_failed = 0;

  no_failed |= test_cs_string();
  no_failed |= test_sprintf();
  no_failed |= test_strerror();
  no_failed |= test_sscanf();
  no_failed |= test_string();

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

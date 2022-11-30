#include "check_s21_sscanf.h"

START_TEST(test_s21_sscanf) {
  int a = 0;
  int b = 0;
  ck_assert_int_eq(s21_sscanf("123", "%d", &a), sscanf("123", "%d", &b));
  ck_assert_int_eq(a, b);

  short sa = 0;
  short sb = 0;
  ck_assert_int_eq(s21_sscanf("123456", "%hd", &sa),
                   sscanf("123456", "%hd", &sb));
  ck_assert_int_eq(sa, sb);

  ck_assert_int_eq(s21_sscanf("98765", "%3d", &a), sscanf("98765", "%3d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("98765", "%3hd%d", &sa, &a),
                   sscanf("98765", "%3hd%d", &sb, &b));
  ck_assert_int_eq(sa, sb);
  ck_assert_int_eq(a, b);

  int c = 0;
  int d = 0;
  ck_assert_int_eq(s21_sscanf("111%111", "%d%%%d", &a, &b),
                   sscanf("111%111", "%d%%%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("222%222", "%d %d", &a, &b),
                   sscanf("222%222", "%d %d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("333abcde333", "%dabcde%d", &a, &b),
                   sscanf("333abcde333", "%dabcde%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("44", "%1d %1d", &a, &b),
                   sscanf("44", "%1d %1d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("4 4", "%d%d", &a, &b),
                   sscanf("4 4", "%d%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf(" ", "%%"), sscanf(" ", "%%"));

  // пустая строка
  ck_assert_int_eq(s21_sscanf("", "%d", &a), sscanf("", "%d", &b));
  ck_assert_int_eq(a, b);

  // строки с пробелами
  ck_assert_int_eq(s21_sscanf(" ", "%d", &a), sscanf(" ", "%d", &b));
  ck_assert_int_eq(a, b);

  // пустая форматная строка с флагом -Werror sscanf не работает
  //    ck_assert_int_eq(s21_sscanf("123", "", &a), sscanf("123", "", &b));
  ck_assert_int_eq(s21_sscanf("123", ""), 0);
  ck_assert_int_eq(s21_sscanf("123", "a"), sscanf("123", "a"));

  // скип числа
  ck_assert_int_eq(s21_sscanf("123123", "%*3d%d", &a),
                   sscanf("123123", "%*3d%d", &b));
  ck_assert_int_eq(a, b);

  // несуществующий формат
  ck_assert_int_eq(s21_sscanf("123", "%a", &a), -1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_int) {
  short sa = 0, sb = 0, sc = 0, sd = 0;
  int a = 0, b = 0;
  long la = 0, lb = 0, lc = 0, ld = 0;

  ck_assert_int_eq(s21_sscanf("123456123", "%6hd%hd", &sa, &sb),
                   sscanf("123456123", "%6hd%hd", &sc, &sd));
  ck_assert_int_eq(sa, sc);
  ck_assert_int_eq(sb, sd);

  ck_assert_int_eq(s21_sscanf("12345678901", "%d", &a),
                   sscanf("12345678901", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901", "%d", &a),
                   sscanf("-12345678901", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901", "%ld", &la),
                   sscanf("-12345678901", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  // переполнение longlong
  ck_assert_int_eq(s21_sscanf("12345678901234567890", "%ld", &la),
                   sscanf("12345678901234567890", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("-12345678901234567890", "%ld", &la),
                   sscanf("-12345678901234567890", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  // переполнение на целый круг
  lb = 0;
  ck_assert_int_eq(s21_sscanf("19223372036854775807", "%ld%ld", &la, &lb),
                   sscanf("19223372036854775807", "%ld%ld", &lc, &ld));
  ck_assert_int_eq(la, lc);
  ck_assert_int_eq(lb, ld);

  // понижение разряда при переполнении
  ck_assert_int_eq(s21_sscanf("12345678901234567890", "%d", &a),
                   sscanf("12345678901234567890", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901234567890", "%d", &a),
                   sscanf("-12345678901234567890", "%d", &b));
  ck_assert_int_eq(a, b);

  // long long
  long long lla = 0, llb = 0, llc = 0, lld = 0;
  ck_assert_int_eq(s21_sscanf("123456789012345", "%lld", &lla),
                   sscanf("123456789012345", "%lld", &llb));
  ck_assert_int_eq(lla, llb);

  ck_assert_int_eq(
      s21_sscanf("-123456789012345678901", "%21lld%lld", &lla, &llb),
      sscanf("-123456789012345678901", "%21lld%lld", &llc, &lld));
  ck_assert_int_eq(lla, llc);
  ck_assert_int_eq(llb, lld);

  ck_assert_int_eq(s21_sscanf("987654321", "%lld", &lla),
                   sscanf("987654321", "%lld", &llb));  // Ld - long long
  // Ахах это УБ
  ck_assert_int_eq(lla, llb);

  // нет числа совсем
  ck_assert_int_eq(s21_sscanf("abc", "%d", &a), sscanf("abc", "%d", &b));
  ck_assert_int_eq(a, b);

  // отрицательное ничего
  ck_assert_int_eq(s21_sscanf("-abc", "%d", &a), sscanf("-abc", "%d", &b));
  ck_assert_int_eq(a, b);

  // слишком широкий спецификатор
  ck_assert_int_eq(s21_sscanf("123", "%5d", &a), sscanf("123", "%5d", &b));
  ck_assert_int_eq(a, b);

  // with +
  ck_assert_int_eq(s21_sscanf("++321", "%d", &a), sscanf("++321", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+321", "%d", &a), sscanf("+321", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+98765", "%*5d%d", &a),
                   sscanf("+98765", "%*5d%d", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_uint) {
  unsigned int a = 0, b = 0;
  unsigned long la = 0, lb = 0;
  unsigned long long lla = 0, llb = 0;

  ck_assert_int_eq(s21_sscanf("1234567890", "%u", &a),
                   sscanf("1234567890", "%u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("12345678901", "%u", &a),
                   sscanf("12345678901", "%u", &b));
  ck_assert_int_eq(a, b);

  // переполнение
  ck_assert_int_eq(s21_sscanf("123456789012345678901", "%llu", &lla),
                   sscanf("123456789012345678901", "%llu", &llb));
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("12345678901234567890123", "%22llu", &lla),
                   sscanf("12345678901234567890123", "%22llu", &llb));
  ck_assert_int_eq(la, lb);

  unsigned short sa = 0, sb = 0;
  ck_assert_int_eq(s21_sscanf("1234567890", "%5hu%lu", &sa, &la),
                   sscanf("1234567890", "%5hu%lu", &sb, &lb));
  ck_assert_int_eq(sa, sb);
  ck_assert_int_eq(la, lb);

  // слишком широкий спецификатор
  ck_assert_int_eq(s21_sscanf("123", "%5u", &a), sscanf("123", "%5u", &b));
  ck_assert_int_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-123", "%u", &a), sscanf("-123", "%u", &b));
  ck_assert_int_eq(a, b);

  // +
  ck_assert_int_eq(s21_sscanf("+123", "%u", &a), sscanf("+123", "%u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+123", "%*2u%u", &a),
                   sscanf("+123", "%*2u%u", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_hex) {
  unsigned int a = 0, b = 0;
  // 0x
  ck_assert_int_eq(s21_sscanf("0x1234567890", "%x", &a),
                   sscanf("0x1234567890", "%x", &b));
  ck_assert_int_eq(a, b);

  // 0X
  ck_assert_int_eq(s21_sscanf("0X1234567890", "%x", &a),
                   sscanf("0X1234567890", "%x", &b));
  ck_assert_int_eq(a, b);

  // a - f
  ck_assert_int_eq(s21_sscanf("0x1abcdef", "%X", &a),
                   sscanf("0x1abcdef", "%X", &b));
  ck_assert_int_eq(a, b);

  // A - F
  ck_assert_int_eq(s21_sscanf("0X1ACDEF", "%X", &a),
                   sscanf("0X1ACDEF", "%X", &b));
  ck_assert_int_eq(a, b);

  // switch case
  ck_assert_int_eq(s21_sscanf("0x1aBcDeF", "%x", &a),
                   sscanf("0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  // half prefix
  ck_assert_int_eq(s21_sscanf("01aBcDeF", "%x", &a),
                   sscanf("01AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("01aBcDeF", "%X", &a),
                   sscanf("01AbCdEf", "%X", &b));
  ck_assert_int_eq(a, b);

  // bad prefix
  ck_assert_int_eq(s21_sscanf("x1aBcDeF", "%x", &a),
                   sscanf("x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(s21_sscanf("X1aBcDeF", "%X", &a),
                   sscanf("X1AbCdEf", "%X", &b));
  ck_assert_int_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-0x1aBcDeF", "%x", &a),
                   sscanf("-0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  // +
  ck_assert_int_eq(s21_sscanf("++0x1aBcDeF", "%x", &a),
                   sscanf("++0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+0x1aBcDeF", "%x", &a),
                   sscanf("+0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_oct) {
  unsigned int a = 0, b = 0;
  // prefix
  ck_assert_int_eq(s21_sscanf("01234567", "%o", &a),
                   sscanf("01234567", "%o", &b));
  ck_assert_int_eq(a, b);
  // no prefix
  ck_assert_int_eq(s21_sscanf("21234567", "%o", &a),
                   sscanf("21234567", "%o", &b));
  ck_assert_int_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-01234567", "%o", &a),
                   sscanf("-01234567", "%o", &b));
  ck_assert_int_eq(a, b);

  // bad prefix
  ck_assert_int_eq(s21_sscanf("0-1234567", "%o", &a),
                   sscanf("0-1234567", "%o", &b));

  // +
  a = 0, b = 0;
  ck_assert_int_eq(s21_sscanf("++01234567", "%o", &a),
                   sscanf("++01234567", "%o", &b));  // уб бан
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+01234567", "%o", &a),
                   sscanf("+01234567", "%o", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_uint) {
  unsigned int a = 0, b = 0;
  // no prefix
  ck_assert_int_eq(s21_sscanf("1234567890", "%i", &a),
                   sscanf("1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // oct prefix
  ck_assert_int_eq(s21_sscanf("01234567", "%i", &a),
                   sscanf("01234567", "%i", &b));
  ck_assert_int_eq(a, b);

  // hex prefix
  ck_assert_int_eq(s21_sscanf("0x1234567890", "%i", &a),
                   sscanf("0x1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-1234567890", "%i", &a),
                   sscanf("-1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // -0 prefix
  ck_assert_int_eq(s21_sscanf("-01234567", "%i", &a),
                   sscanf("-01234567", "%i", &b));
  ck_assert_int_eq(a, b);

  // -0x prefix
  ck_assert_int_eq(s21_sscanf("-0x1234567890", "%i", &a),
                   sscanf("-0x1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // wierd -- prefix
  ck_assert_int_eq(s21_sscanf("--1234567890", "%i", &a),
                   sscanf("--1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // wierd -0- prefix
  ck_assert_int_eq(s21_sscanf("-0-1234567890", "%i", &a),
                   sscanf("-0-1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // wierd -0x- prefix
  ck_assert_int_eq(s21_sscanf("-0x-ab34567890", "%i", &a),
                   sscanf("-0x-ab34567890", "%i", &b));
  ck_assert_int_eq(a, b);

  // hex without prefix
  ck_assert_int_eq(s21_sscanf("123abcdef", "%i", &a),
                   sscanf("123abcdef", "%i", &b));
  ck_assert_int_eq(a, b);

  // hex without prefix starting with letter
  ck_assert_int_eq(s21_sscanf("a123abcdef", "%i", &a),
                   sscanf("a123abcdef", "%i", &b));
  ck_assert_int_eq(a, b);

  // hex with + prefix
  ck_assert_int_eq(s21_sscanf("+0xfaf", "%i", &a), sscanf("+0xfaf", "%i", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_ptr) {
  void *a = NULL, *b = NULL;
  ck_assert_int_eq(s21_sscanf("0x1234567890", "%p", &a),
                   sscanf("0x1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0xabc", "%p", &a), sscanf("0xabc", "%p", &b));
  ck_assert_ptr_eq(a, b);

  // no prefix
  ck_assert_int_eq(s21_sscanf("1234567890", "%p", &a),
                   sscanf("1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);

  // -
  ck_assert_int_eq(s21_sscanf("-1234567890", "%p", &a),
                   sscanf("-1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);
}
END_TEST

START_TEST(test_parse_string) {
  char buf1[100] = {0}, buf2[100] = {0};
  // %c
  ck_assert_int_eq(s21_sscanf("123", "%c", buf1), sscanf("123", "%c", buf2));
  ck_assert_int_eq(buf1[0], buf2[0]);

  // %s
  ck_assert_int_eq(s21_sscanf("1234567890", "%s", buf1),
                   sscanf("1234567890", "%s", buf2));
  ck_assert_str_eq(buf1, buf2);

  // %c with len
  // %c shouldnt add null terminator
  ck_assert_int_eq(s21_sscanf("qwertyuiop", "%9c", buf1),
                   sscanf("qwertyuiop", "%9c", buf2));
  ck_assert_str_eq(buf1, buf2);

  // %s with len
  ck_assert_int_eq(s21_sscanf("abcdefghk", "%5s", buf1),
                   sscanf("abcdefghk", "%5s", buf2));
  ck_assert_str_eq(buf1, buf2);

  // %c with len
  ck_assert_int_eq(s21_sscanf("qwe", "%2c", buf1), sscanf("qwe", "%2c", buf2));
  ck_assert_str_eq(buf1, buf2);

  // empty string
  ck_assert_int_eq(s21_sscanf("", "%s", buf1), sscanf("", "%s", buf2));
  ck_assert_str_eq(buf1, buf2);

  // two strings with space
  char buf3[100] = {0}, buf4[100] = {0};
  ck_assert_int_eq(s21_sscanf("123 456", "%s %s", buf1, buf3),
                   sscanf("123 456", "%s %s", buf2, buf4));
  ck_assert_str_eq(buf1, buf2);
  ck_assert_str_eq(buf3, buf4);
}
END_TEST

START_TEST(test_scan_n) {
  char buf1[100] = {0}, buf2[100] = {0};
  int a = 0, b = 0;
  ck_assert_int_eq(s21_sscanf("1234567890", "%5s%n", buf1, &a),
                   sscanf("1234567890", "%5s%n", buf2, &b));
  ck_assert_int_eq(a, b);

  // empty string
  ck_assert_int_eq(s21_sscanf("", "%s%n", buf1, &a),
                   sscanf("", "%s%n", buf2, &b));
  ck_assert_int_eq(a, b);

  int i = 0, j = 0;  // опять уб
  ck_assert_int_eq(s21_sscanf("123456", "%*3d%d%n", &i, &a),
                   sscanf("123456", "%*3d%d%n", &j, &b));
  ck_assert_int_eq(a, b);
}
END_TEST

long double ldabs(long double x) { return x < 0 ? -x : x; }

bool float_eq(float a, float b) { return fabs(a - b) < 0.00001; }
bool double_eq(double a, double b) { return fabs(a - b) < 0.00001; }
bool ldouble_eq(long double a, long double b) { return ldabs(a - b) < 0.00001; }

START_TEST(test_scan_float) {
  float a = 0, b = 0;
  double da = 0, db = 0;
  long double lda = 0, ldb = 0;
  ck_assert_int_eq(s21_sscanf("123.456", "%f", &a),
                   sscanf("123.456", "%f", &b));
  ck_assert(float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("123.456", "%lf", &da),
                   sscanf("123.456", "%lf", &db));
  ck_assert(double_eq(da, db));

  ck_assert_int_eq(s21_sscanf("123.456", "%Lf", &lda),
                   sscanf("123.456", "%Lf", &ldb));
  ck_assert(ldouble_eq(lda, ldb));

  ck_assert_int_eq(s21_sscanf("123.456", "%hf", &a),
                   sscanf("123.456", "%f", &b));
  ck_assert(float_eq(a, b));

  // nan
  ck_assert_int_eq(s21_sscanf("nan", "%e", &a), sscanf("nan", "%e", &b));
  ck_assert(isnan(a));
  ck_assert(isnan(b));

  // inf +inf -inf
  ck_assert_int_eq(s21_sscanf("iNf", "%g", &a), sscanf("iNf", "%g", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));

  ck_assert_int_eq(s21_sscanf("+inf", "%G", &a), sscanf("+inf", "%G", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));

  ck_assert_int_eq(s21_sscanf("-inf", "%E", &a), sscanf("-inf", "%E", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));

  // scientific
  ck_assert_int_eq(s21_sscanf("1.23e-4", "%e", &a),
                   sscanf("1.23e-4", "%e", &b));
  ck_assert(float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("1.23e4", "%e", &a), sscanf("1.23e4", "%e", &b));
  ck_assert(float_eq(a, b));

  // empty string
  ck_assert_int_eq(s21_sscanf("", "%f", &a), sscanf("", "%f", &b));
  ck_assert(float_eq(a, b));

  // empty negative string
  ck_assert_int_eq(s21_sscanf("-", "%f", &a), sscanf("-", "%f", &b));
  ck_assert(float_eq(a, b));

  // with width
  ck_assert_int_eq(s21_sscanf("123.456", "%6f", &a),
                   sscanf("123.456", "%6f", &b));
  ck_assert(float_eq(a, b));

  // scientific with width
  ck_assert_int_eq(s21_sscanf("1.23E10", "%6E", &a),
                   sscanf("1.23E10", "%6E", &b));
  ck_assert(float_eq(a, b));

  // only .
  ck_assert_int_eq(s21_sscanf(".", "%f", &a), sscanf(".", "%f", &b));
  ck_assert(float_eq(a, b));

  // not digits
  ck_assert_int_eq(s21_sscanf("abc", "%f", &a), sscanf("abc", "%f", &b));
  ck_assert(float_eq(a, b));

  // dot at the end
  ck_assert_int_eq(s21_sscanf("123.", "%f", &a), sscanf("123.", "%f", &b));
  ck_assert(float_eq(a, b));

  // dot at the beginning
  ck_assert_int_eq(s21_sscanf(".123", "%f", &a), sscanf(".123", "%f", &b));
  ck_assert(float_eq(a, b));

  // letters after dot
  ck_assert_int_eq(s21_sscanf("123.abc", "%f", &a),
                   sscanf("123.abc", "%f", &b));
  ck_assert(float_eq(a, b));

  // no dot
  ck_assert_int_eq(s21_sscanf("222", "%f", &a), sscanf("222", "%f", &b));
  ck_assert(float_eq(a, b));

  // letters
  ck_assert_int_eq(s21_sscanf("abc", "%f", &a), sscanf("abc", "%f", &b));
  ck_assert(float_eq(a, b));
}
END_TEST

START_TEST(test_scanf_impossible) {
  char *buf = calloc(100, sizeof(*buf));
  char *tmp = buf;
  s21_strcpy(buf, "123");
  specifier spec = {0};
  spec.spec = 123;
  spec.len = 123;
  int a = 123;
  scan(spec, &buf, s21_NULL, &a, buf);
  parse_float(spec, &buf, s21_NULL);
  parse_int(spec, &buf, s21_NULL);
  free(tmp);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("S21 Sscanf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sscanf);
  tcase_add_test(tc_core, test_parse_int);
  tcase_add_test(tc_core, test_parse_uint);
  tcase_add_test(tc_core, test_parse_hex);
  tcase_add_test(tc_core, test_parse_oct);
  tcase_add_test(tc_core, test_parse_i_uint);
  tcase_add_test(tc_core, test_parse_ptr);
  tcase_add_test(tc_core, test_parse_string);
  tcase_add_test(tc_core, test_scan_n);
  tcase_add_test(tc_core, test_scan_float);
  tcase_add_test(tc_core, test_scanf_impossible);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_sscanf() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_sscanf_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

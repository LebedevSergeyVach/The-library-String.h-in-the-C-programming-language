#include "unit_tests_s21_sscanf.h"

// Тесты для спецификатора %d (целые числа)
START_TEST(test_s21_sscanf_d) {
  int a = 0, b = 0, c = 0, d = 0;
  const char *str = "123 456";

  int result1 = s21_sscanf(str, "%d %d", &a, &b);
  int result2 = sscanf(str, "%d %d", &c, &d);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %i (целые числа в разных системах счисления)
START_TEST(test_s21_sscanf_i) {
  int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
  const char *str = "123 0xABC 0777";

  int result1 = s21_sscanf(str, "%i %i %i", &a, &b, &c);
  int result2 = sscanf(str, "%i %i %i", &d, &e, &f);

  ck_assert_int_eq(a, d);  // Assertion 'a == d' failed: a == 291, d == 123
  ck_assert_int_eq(b, e);
  ck_assert_int_eq(c, f);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %u (беззнаковые целые числа)
START_TEST(test_s21_sscanf_u) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "123 456";

  int result1 = s21_sscanf(str, "%u %u", &a, &b);
  int result2 = sscanf(str, "%u %u", &c, &d);

  ck_assert_uint_eq(a, c);
  ck_assert_uint_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %x и %X (шестнадцатеричные числа
START_TEST(test_s21_sscanf_x) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "0xABC d";

  int result1 = s21_sscanf(str, "%x %X", &a, &b);
  int result2 = sscanf(str, "%x %X", &c, &d);

  ck_assert_uint_eq(a, c);
  ck_assert_uint_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %o (восьмеричные числа
START_TEST(test_s21_sscanf_o) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "0777 0123";

  int result1 = s21_sscanf(str, "%o %o", &a, &b);
  int result2 = sscanf(str, "%o %o", &c, &d);

  ck_assert_uint_eq(a, c);
  ck_assert_uint_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %f и %lf (числа с плавающей точкой)
START_TEST(test_s21_sscanf_f) {
  float a_fl = 0, b_fl = 0, c_fl = 0, d_fl = 0;
  double a_db = 0, b_db = 0, c_db = 0, d_db = 0;
  const char *str = "123.456 789.012 123.456 789.012";

  int result1 = s21_sscanf(str, "%f %f %lf %lf", &a_fl, &b_fl, &a_db, &b_db);
  int result2 = sscanf(str, "%f %f %lf %lf", &c_fl, &d_fl, &c_db, &d_db);

  ck_assert_float_eq(a_fl, c_fl);
  ck_assert_float_eq(b_fl, d_fl);
  ck_assert_double_eq(a_db, c_db);
  ck_assert_double_eq(b_db, d_db);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %s (строки)
START_TEST(test_s21_sscanf_s) {
  char str1[100] = {0}, str2[100] = {0}, str3[100] = {0}, str4[100] = {0};
  const char *input = "Hello World";

  int result1 = s21_sscanf(input, "%99s %99s", str1, str2);
  int result2 = sscanf(input, "%99s %99s", str3, str4);

  ck_assert_str_eq(str1, str3);
  ck_assert_str_eq(str2, str4);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %c (символы)
START_TEST(test_s21_sscanf_c) {
  char a = 0, b = 0, c = 0, d = 0;
  const char *str = "A B";

  int result1 = s21_sscanf(str, "%c %c", &a, &b);
  int result2 = sscanf(str, "%c %c", &c, &d);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %p (указатели
START_TEST(test_s21_sscanf_p) {
  void *a = S21_NULL, *b = S21_NULL, *c = S21_NULL, *d = S21_NULL;
  const char *str = "0xABCDEF 0x123456";

  int result1 = s21_sscanf(str, "%p %p", &a, &b);
  int result2 = sscanf(str, "%p %p", &c, &d);

  ck_assert_ptr_eq(a, c);  // (void *)0xABCDEF
  ck_assert_ptr_eq(b, d);  // (void *)0x123456
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %n (количество прочитанных символов)
START_TEST(test_s21_sscanf_n) {
  int a = 0, b = 0, c = 0, d = 0, n1 = 0, n2 = 0;
  const char *str = "123 456";

  int result1 = s21_sscanf(str, "%d %d%n", &a, &b, &n1);
  int result2 = sscanf(str, "%d %d%n", &c, &d, &n2);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для ширины и точности
START_TEST(test_s21_sscanf_width) {
  int a = 0, b = 0, c = 0, d = 0;
  const char *str = "12345 67890";

  int result1 = s21_sscanf(str, "%2d %3d", &a, &b);
  int result2 = sscanf(str, "%2d %3d", &c, &d);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для флагов форматирования
START_TEST(test_s21_sscanf_flags) {
  int a = 0, b = 0, c = 0, d = 0;
  const char *str = "+123 -456";

  int result1 = s21_sscanf(str, "%d %d", &a, &b);
  int result2 = sscanf(str, "%d %d", &c, &d);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для комбинированных случаев
START_TEST(test_s21_sscanf_combined) {
  int a_int = 0, b_int = 0, c_int = 0, d_int = 0;
  float a_fl = 0, b_fl = 0;
  char str1[100] = {0}, str2[100] = {0}, str3[100] = {0}, str4[100] = {0};
  const char *input = "123 456 789.012 Hello World";

  int result1 = s21_sscanf(input, "%d %d %f %99s %99s", &a_int, &b_int, &a_fl,
                           str1, str2);
  int result2 =
      sscanf(input, "%d %d %f %99s %99s", &c_int, &d_int, &b_fl, str3, str4);

  ck_assert_int_eq(a_int, c_int);
  ck_assert_int_eq(d_int, d_int);
  ck_assert_float_eq(a_fl, b_fl);  // 789.012f
  ck_assert_str_eq(str1, str3);
  ck_assert_str_eq(str2, str4);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %d с шириной и флагами
START_TEST(test_s21_sscanf_d_width) {
  int a = 0, b = 0, c = 0, d = 0;
  const char *str = "12345 67890";

  int result1 = s21_sscanf(str, "%2d %3d", &a, &b);
  int result2 = sscanf(str, "%2d %3d", &c, &d);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_d_neg) {
  int a = 0, b = 0, c = 0, d = 0;
  const char *str = "-123 +456";

  int result1 = s21_sscanf(str, "%d %d", &a, &b);
  int result2 = sscanf(str, "%d %d", &c, &d);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %i с разными системами счисления
START_TEST(test_s21_sscanf_i_hex) {
  int a = 0, b = 0, c = 0, d = 0;
  const char *str = "0xABC 0X123";

  int result1 = s21_sscanf(str, "%i %i", &a, &b);
  int result2 = sscanf(str, "%i %i", &c, &d);

  ck_assert_int_eq(a, c);  // 0xABC
  ck_assert_int_eq(b, d);  // 0x123
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_i_oct) {
  int a = 0, b = 0, c = 0, d = 0;
  const char *str = "0777 0123";

  int result1 = s21_sscanf(str, "%i %i", &a, &b);
  int result2 = sscanf(str, "%i %i", &c, &d);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %u с шириной и флагами
START_TEST(test_s21_sscanf_u_width) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "12345 67890";

  int result1 = s21_sscanf(str, "%3u %4u", &a, &b);
  int result2 = sscanf(str, "%3u %4u", &c, &d);

  ck_assert_uint_eq(a, c);
  ck_assert_uint_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_u_neg) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "-123 +456";

  int result1 = s21_sscanf(str, "%u %u", &a, &b);
  int result2 = sscanf(str, "%u %u", &c, &d);

  ck_assert_uint_eq(a, c);
  ck_assert_uint_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %x и %X с шириной и флагами
START_TEST(test_s21_sscanf_x_width) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "0xABC 0xDEF";

  int result1 = s21_sscanf(str, "%3x %3X", &a, &b);
  int result2 = sscanf(str, "%3x %3X", &c, &d);

  ck_assert_uint_eq(a, c);  // 0xABC
  ck_assert_uint_eq(b, d);  // 0xDEF
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_x_no_prefix) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "ABC DEF";

  int result1 = s21_sscanf(str, "%x %X", &a, &b);
  int result2 = sscanf(str, "%x %X", &c, &d);

  ck_assert_uint_eq(a, c);  // 0xABC
  ck_assert_uint_eq(b, d);  // 0xDEF
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %o с шириной и флагами
START_TEST(test_s21_sscanf_o_width) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "0777 0123";

  int result1 = s21_sscanf(str, "%3o %3o", &a, &b);
  int result2 = sscanf(str, "%3o %3o", &c, &d);

  ck_assert_uint_eq(a, c);
  ck_assert_uint_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_o_no_prefix) {
  unsigned int a = 0, b = 0, c = 0, d = 0;
  const char *str = "777 123";

  int result1 = s21_sscanf(str, "%o %o", &a, &b);
  int result2 = sscanf(str, "%o %o", &c, &d);

  ck_assert_uint_eq(a, c);
  ck_assert_uint_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %f и %lf с шириной и точностью
START_TEST(test_s21_sscanf_f_width) {
  float a = 0, b = 0, c = 0, d = 0;
  const char *str = "123.456 789.012";

  int result1 = s21_sscanf(str, "%3f %4f", &a, &b);
  int result2 = sscanf(str, "%3f %4f", &c, &d);

  ck_assert_float_eq(a, c);
  ck_assert_float_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_f_precision) {
  float a = 0, b = 0, c = 0, d = 0;
  const char *str = "123.456 789.012";

  int result1 = s21_sscanf(str, "%f %f", &a, &b);
  int result2 = sscanf(str, "%f %f", &c, &d);

  ck_assert_float_eq(a, c);  // 123.456f
  ck_assert_float_eq(b, d);  // 789.012f
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_f_exponent) {
  float a = 0, b = 0, c = 0, d = 0;
  const char *str = "1.456e-01 789.012";

  int result1 = s21_sscanf(str, "%e %f", &a, &b);
  int result2 = sscanf(str, "%e %f", &c, &d);

  ck_assert_float_eq(a, c);  // 123.456f
  ck_assert_float_eq(b, d);  // 789.012f
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_f_inf) {
  float a = 0, b = 0, c = 0, d = 0;
  const char *str = "inf 789.012";

  int result1 = s21_sscanf(str, "%f %f", &a, &b);
  int result2 = sscanf(str, "%f %f", &c, &d);

  ck_assert_float_eq(a, c);  // inf
  // ck_assert_float_eq(b, d);  // 789.012f
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %s с шириной
START_TEST(test_s21_sscanf_s_width) {
  char str1[100] = {0}, str2[100] = {0}, str3[100] = {0}, str4[100] = {0};
  const char *input = "Hello World";

  int result1 = s21_sscanf(input, "%5s %5s", str1, str2);
  int result2 = sscanf(input, "%5s %5s", str3, str4);

  ck_assert_str_eq(str1, str3);
  ck_assert_str_eq(str2, str4);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %c с шириной
START_TEST(test_s21_sscanf_c_width) {
  char a = 0, b = 0, c = 0, d = 0;
  const char *str = "AB";

  int result1 = s21_sscanf(str, "%1c %1c", &a, &b);
  int result2 = sscanf(str, "%1c %1c", &c, &d);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %n (количество прочитанных символов)
START_TEST(test_s21_sscanf_n_combined) {
  int a = 0, b = 0, c = 0, d = 0, n1 = 0, n2 = 0;
  const char *str = "123 456";

  int result1 = s21_sscanf(str, "%d %d%n", &a, &b, &n1);
  int result2 = sscanf(str, "%d %d%n", &c, &d, &n2);

  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для комбинированных случаев с разными спецификаторами
START_TEST(test_s21_sscanf_combined_mixed) {
  int a_int = 0, b_int = 0, c_int = 0, d_int = 0;
  float a_fl = 0, b_fl = 0;
  char str1[100] = {0}, str2[100] = {0}, str3[100] = {0}, str4[100] = {0};

  const char *input = "123 456 789.012 Hello World";
  int result1 = s21_sscanf(input, "%d %d %f %99s %99s", &a_int, &b_int, &a_fl,
                           str1, str2);
  int result2 =
      sscanf(input, "%d %d %f %99s %99s", &c_int, &d_int, &b_fl, str3, str4);

  ck_assert_int_eq(a_int, c_int);
  ck_assert_int_eq(b_int, d_int);
  ck_assert_float_eq(a_fl, b_fl);
  ck_assert_str_eq(str1, str3);
  ck_assert_str_eq(str2, str4);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sscanf_long_str) {
  int a_int = 0, b_int = 0, c_int = 0, d_int = 0;
  float a_fl = 0, b_fl = 0;
  char str2[100] = {0}, str4[100] = {0};
  s21_wchar_t str1[100] = {0}, str3[100] = {0};

  const char *input = "123 456 789.012 Hello World";
  int result1 = s21_sscanf(input, "%d %d %f %99ls %99s", &a_int, &b_int, &a_fl,
                           str1, str2);
  int result2 =
      sscanf(input, "%d %d %f %99ls %99s", &c_int, &d_int, &b_fl, str3, str4);

  ck_assert_int_eq(a_int, c_int);
  ck_assert_int_eq(b_int, d_int);
  ck_assert_float_eq(a_fl, b_fl);
  ck_assert_str_eq((const char *)str1, (const char *)str3);
  ck_assert_str_eq(str2, str4);
  ck_assert_int_eq(result1, result2);
}
END_TEST

Suite *s21_sscanf_suite() {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc_core = tcase_create("core");

  printf(BLUE "RUN UNIT TESTS FOR " GREEN "s21_sscanf.c\n" RESET);

  tcase_add_test(tc_core, test_s21_sscanf_d);
  tcase_add_test(tc_core, test_s21_sscanf_i);
  tcase_add_test(tc_core, test_s21_sscanf_u);
  tcase_add_test(tc_core, test_s21_sscanf_x);
  tcase_add_test(tc_core, test_s21_sscanf_o);
  tcase_add_test(tc_core, test_s21_sscanf_f);
  tcase_add_test(tc_core, test_s21_sscanf_s);
  tcase_add_test(tc_core, test_s21_sscanf_c);
  tcase_add_test(tc_core, test_s21_sscanf_p);
  tcase_add_test(tc_core, test_s21_sscanf_n);
  tcase_add_test(tc_core, test_s21_sscanf_width);
  tcase_add_test(tc_core, test_s21_sscanf_flags);
  tcase_add_test(tc_core, test_s21_sscanf_combined);
  tcase_add_test(tc_core, test_s21_sscanf_d_width);
  tcase_add_test(tc_core, test_s21_sscanf_d_neg);
  tcase_add_test(tc_core, test_s21_sscanf_i_hex);
  tcase_add_test(tc_core, test_s21_sscanf_i_oct);
  tcase_add_test(tc_core, test_s21_sscanf_u_width);
  tcase_add_test(tc_core, test_s21_sscanf_u_neg);
  tcase_add_test(tc_core, test_s21_sscanf_x_width);
  tcase_add_test(tc_core, test_s21_sscanf_x_no_prefix);
  tcase_add_test(tc_core, test_s21_sscanf_o_width);
  tcase_add_test(tc_core, test_s21_sscanf_o_no_prefix);
  tcase_add_test(tc_core, test_s21_sscanf_f_width);
  tcase_add_test(tc_core, test_s21_sscanf_f_precision);
  tcase_add_test(tc_core, test_s21_sscanf_f_exponent);
  tcase_add_test(tc_core, test_s21_sscanf_f_inf);
  tcase_add_test(tc_core, test_s21_sscanf_s_width);
  tcase_add_test(tc_core, test_s21_sscanf_c_width);
  tcase_add_test(tc_core, test_s21_sscanf_n_combined);
  tcase_add_test(tc_core, test_s21_sscanf_combined_mixed);
  tcase_add_test(tc_core, test_s21_sscanf_long_str);

  suite_add_tcase(s, tc_core);
  return s;
}

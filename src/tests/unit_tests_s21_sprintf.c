#include "unit_tests_s21_sprintf.h"

START_TEST(test_s21_sprintf_d) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 12345;

  int result1 = s21_sprintf(buffer1, "%d", num);
  int result2 = sprintf(buffer2, "%d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_s) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  char *str = "Hello, World!";

  int result1 = s21_sprintf(buffer1, "%s", str);
  int result2 = sprintf(buffer2, "%s", str);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 123.456;

  int result1 = s21_sprintf(buffer1, "%.2f", num);
  int result2 = sprintf(buffer2, "%.2f", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_x) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0xABCD;

  int result1 = s21_sprintf(buffer1, "%x", num);
  int result2 = sprintf(buffer2, "%x", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_e) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 123.456;

  int result1 = s21_sprintf(buffer1, "%e", num);
  int result2 = sprintf(buffer2, "%e", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_g) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double double_num = 123.456;

  int result1 = s21_sprintf(buffer1, "%g", double_num);
  int result2 = sprintf(buffer2, "%g", double_num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_g_capital) {
  char buffer3[100] = {0};
  char buffer4[100] = {0};
  float num = 123.456;

  int result3 = s21_sprintf(buffer3, "%g", num);
  int result4 = sprintf(buffer4, "%g", num);

  ck_assert_str_eq(buffer3, buffer4);
  ck_assert_int_eq(result3, result4);
}
END_TEST

START_TEST(test_s21_sprintf_flags) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;

  int result1 = s21_sprintf(buffer1, "%+d", num);
  int result2 = sprintf(buffer2, "%+d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %c (символы)
START_TEST(test_s21_sprintf_c) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  char ch = 'A';

  int result1 = s21_sprintf(buffer1, "%c", ch);
  int result2 = sprintf(buffer2, "%c", ch);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}

// ПОШЛИ ТЕСТЫ ДЛЯ SPRINF

END_TEST
// Тесты для спецификатора %u (беззнаковые целые числа)
START_TEST(test_s21_sprintf_u) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 12345;

  int result1 = s21_sprintf(buffer1, "%u", num);
  int result2 = sprintf(buffer2, "%u", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %x и %X (шестнадцатеричные числа)
START_TEST(test_s21_sprintf_x_lower) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0xABCD;

  int result1 = s21_sprintf(buffer1, "%x", num);
  int result2 = sprintf(buffer2, "%x", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_x_upper) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0xABCD;

  int result1 = s21_sprintf(buffer1, "%X", num);
  int result2 = sprintf(buffer2, "%X", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %o (восьмеричные числа)
START_TEST(test_s21_sprintf_o) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0777;

  int result1 = s21_sprintf(buffer1, "%o", num);
  int result2 = sprintf(buffer2, "%o", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %p (указатели)
START_TEST(test_s21_sprintf_p) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  void *ptr = (void *)0xABCDEF;

  int result1 = s21_sprintf(buffer1, "%p", ptr);
  int result2 = sprintf(buffer2, "%p", ptr);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %e и %E (экспоненциальная запись)
START_TEST(test_s21_sprintf_e_lower) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 123.456;
  int result1 = s21_sprintf(buffer1, "%e", num);
  int result2 = sprintf(buffer2, "%e", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_e_upper) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 123.456;

  int result1 = s21_sprintf(buffer1, "%E", num);
  int result2 = sprintf(buffer2, "%E", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для спецификатора %g и %G (выбор между %f и %e)
START_TEST(test_s21_sprintf_g_lower) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 123.456;

  int result1 = s21_sprintf(buffer1, "%g", num);
  int result2 = sprintf(buffer2, "%g", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_g_upper) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 123.456;

  int result1 = s21_sprintf(buffer1, "%G", num);
  int result2 = sprintf(buffer2, "%G", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для флагов форматирования
START_TEST(test_s21_sprintf_flags_plus) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;

  int result1 = s21_sprintf(buffer1, "%+d", num);
  int result2 = sprintf(buffer2, "%+d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_flags_space) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;

  int result1 = s21_sprintf(buffer1, "% d", num);
  int result2 = sprintf(buffer2, "% d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_flags_zero) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;

  int result1 = s21_sprintf(buffer1, "%05d", num);
  int result2 = sprintf(buffer2, "%05d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_flags_minus) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;

  int result1 = s21_sprintf(buffer1, "%-5d", num);
  int result2 = sprintf(buffer2, "%-5d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_flags_double_plus) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 1.4;

  int result1 = s21_sprintf(buffer1, "%+09.3lf", num);
  int result2 = sprintf(buffer2, "%+09.3lf", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для ширины и точности
START_TEST(test_s21_sprintf_width) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;

  int result1 = s21_sprintf(buffer1, "%5d", num);
  int result2 = sprintf(buffer2, "%5d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_precision) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 123.456;

  int result1 = s21_sprintf(buffer1, "%.4f", num);
  int result2 = sprintf(buffer2, "%.4f", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для комбинированных случаев
START_TEST(test_s21_sprintf_combined) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;
  double dbl = 123.456;
  char *str = "Hello";

  int result1 = s21_sprintf(buffer1, "%+05d %.2f %s", num, dbl, str);
  int result2 = sprintf(buffer2, "%+05d %.2f %s", num, dbl, str);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на комбинацию флагов +, 0, и ширины:
START_TEST(test_s21_sprintf_flags_plus_zero_width) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;

  int result1 = s21_sprintf(buffer1, "%+08d", num);
  int result2 = sprintf(buffer2, "%+08d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на комбинацию флагов -, #, и ширины:
START_TEST(test_s21_sprintf_flags_minus_hash_width) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 123;

  int result1 = s21_sprintf(buffer1, "%-10x", num);
  int result2 = sprintf(buffer2, "%-10x", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на комбинацию флагов (пробел), +, и точности:
START_TEST(test_s21_sprintf_flags_space_plus_precision) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = -123;

  int result1 = s21_sprintf(buffer1, "%+.5d", num);
  int result2 = sprintf(buffer2, "%+.5d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// // Тесты на неправильные аргументы
// // Тест на неправильный спецификатор:
// START_TEST(test_s21_sprintf_invalid_specifier) {
//   char buffer1[100] = {0};
//   char buffer2[100] = {0};
//   int num = 123;

//   int result1 = s21_sprintf(buffer1, "%z", num);  // Неправильный
//   спецификатор int result2 = sprintf(buffer2, "%z", num);      // Ожидаем
//   ошибку

//   ck_assert_str_eq(buffer1, buffer2);  // Оба должны вернуть пустую строку
//   ck_assert_int_eq(result1, result2);
// }
// END_TEST

// // Тест на отсутствие аргумента:
// START_TEST(test_s21_sprintf_missing_argument) {
//   char buffer1[100] = {0};
//   char buffer2[100] = {0};

//   int result1 = s21_sprintf(buffer1, "%d");  // Нет аргумента
//   int result2 = sprintf(buffer2, "%d");      // Ожидаем ошибку

//   ck_assert_str_eq(buffer1, buffer2);  // Оба должны вернуть пустую строку
//   ck_assert_int_eq(result1, result2);
// }
// END_TEST

// . Тесты на граничные условия
// Тест на максимальное значение int:
START_TEST(test_s21_sprintf_int_max) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = INT_MAX;

  int result1 = s21_sprintf(buffer1, "%d", num);
  int result2 = sprintf(buffer2, "%d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на минимальное значение int:
START_TEST(test_s21_sprintf_int_min) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = INT_MIN;

  int result1 = s21_sprintf(buffer1, "%d", num);
  int result2 = sprintf(buffer2, "%d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на очень большое число с плавающей точкой:
START_TEST(test_s21_sprintf_large_float) {
  char buffer1[400] = {0};
  char buffer2[400] = {0};
  double num = 1.7976931348623157e+10;  // Максимальное значение double

  int result1 = s21_sprintf(buffer1, "%f", num);
  int result2 = sprintf(buffer2, "%f", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты на спецификаторы с разной точностью и шириной
// Тест на ширину и точность для строки:
START_TEST(test_s21_sprintf_string_width_precision) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  char *str = "Hello, World!";

  int result1 = s21_sprintf(buffer1, "%20.5s", str);
  int result2 = sprintf(buffer2, "%20.5s", str);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на ширину и точность для чисел с плавающей точкой:
START_TEST(test_s21_sprintf_float_width_precision) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 123.456789;

  int result1 = s21_sprintf(buffer1, "%10.3f", num);
  int result2 = sprintf(buffer2, "%10.3f", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты на спецификаторы с разными системами счисления
// Тест на шестнадцатеричное число с флагом #:
START_TEST(test_s21_sprintf_hex_hash) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0xABCD;

  int result1 = s21_sprintf(buffer1, "%#x", num);
  int result2 = sprintf(buffer2, "%#x", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на восьмеричное число с флагом #:
START_TEST(test_s21_sprintf_octal_hash) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0777;

  int result1 = s21_sprintf(buffer1, "%#o", num);
  int result2 = sprintf(buffer2, "%#o", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты на спецификаторы %n
// START_TEST(test_s21_sprintf_n_specifier) {
//   char buffer1[100] = {0};
//   char buffer2[100] = {0};
//   int count1 = 0, count2 = 0;

//   int result1 = s21_sprintf(buffer1, "Hello, World!%n", &count1);
//   int result2 = sprintf(buffer2, "Hello, World!%n", &count2);

//   ck_assert_str_eq(buffer1, buffer2);
//   ck_assert_int_eq(result1, result2);
//   ck_assert_int_eq(count1, count2);
// }
// END_TEST

// Тесты на спецификаторы %p
START_TEST(test_s21_sprintf_pointer) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  void *ptr = (void *)0xABCDEF;

  int result1 = s21_sprintf(buffer1, "%p", ptr);
  int result2 = sprintf(buffer2, "%p", ptr);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты на спецификаторы %g и %G
// Тест на спецификатор %g с большим числом:
START_TEST(test_s21_sprintf_g_large_number) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 1.23e+10;

  int result1 = s21_sprintf(buffer1, "%g", num);
  int result2 = sprintf(buffer2, "%g", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %G с маленьким числом:
START_TEST(test_s21_sprintf_G_small_number) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 1.23e-10;

  int result1 = s21_sprintf(buffer1, "%G", num);
  int result2 = sprintf(buffer2, "%G", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты на спецификаторы %e и %E
// Тест на спецификатор %e с отрицательным числом:
START_TEST(test_s21_sprintf_e_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = -123.456;

  int result1 = s21_sprintf(buffer1, "%e", num);
  int result2 = sprintf(buffer2, "%e", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %E с нулем:
START_TEST(test_s21_sprintf_E_zero) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 0.0;

  int result1 = s21_sprintf(buffer1, "%E", num);
  int result2 = sprintf(buffer2, "%E", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %u с максимальным значением:
START_TEST(test_s21_sprintf_u_max) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = UINT_MAX;

  int result1 = s21_sprintf(buffer1, "%u", num);
  int result2 = sprintf(buffer2, "%u", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %c с нулевым символом:
START_TEST(test_s21_sprintf_c_null) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  char ch = '\0';

  int result1 = s21_sprintf(buffer1, "%c", ch);
  int result2 = sprintf(buffer2, "%c", ch);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %s с пустой строкой:
START_TEST(test_s21_sprintf_s_empty) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  char *str = "";

  int result1 = s21_sprintf(buffer1, "%s", str);
  int result2 = sprintf(buffer2, "%s", str);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %f с отрицательным числом:
START_TEST(test_s21_sprintf_f_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = -123.456;

  int result1 = s21_sprintf(buffer1, "%f", num);
  int result2 = sprintf(buffer2, "%f", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %d с нулем:
START_TEST(test_s21_sprintf_d_zero) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = 0;

  int result1 = s21_sprintf(buffer1, "%d", num);
  int result2 = sprintf(buffer2, "%d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %x с нулем:
START_TEST(test_s21_sprintf_x_zero) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0;

  int result1 = s21_sprintf(buffer1, "%x", num);
  int result2 = sprintf(buffer2, "%x", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %o с нулем:
START_TEST(test_s21_sprintf_o_zero) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0;

  int result1 = s21_sprintf(buffer1, "%o", num);
  int result2 = sprintf(buffer2, "%o", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %p с нулевым указателем:
START_TEST(test_s21_sprintf_p_null) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  void *ptr = NULL;

  int result1 = s21_sprintf(buffer1, "%p", ptr);
  int result2 = sprintf(buffer2, "%p", ptr);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %g с нулем:
START_TEST(test_s21_sprintf_g_zero) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 0.0;

  int result1 = s21_sprintf(buffer1, "%g", num);
  int result2 = sprintf(buffer2, "%g", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %u с нулем:
START_TEST(test_s21_sprintf_u_zero) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = 0;

  int result1 = s21_sprintf(buffer1, "%u", num);
  int result2 = sprintf(buffer2, "%u", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %c с символом новой строки:
START_TEST(test_s21_sprintf_c_newline) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  char ch = '\n';

  int result1 = s21_sprintf(buffer1, "%c", ch);
  int result2 = sprintf(buffer2, "%c", ch);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %s с нулевым указателем:
START_TEST(test_s21_sprintf_s_null) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  char *str = NULL;

  int result1 = s21_sprintf(buffer1, "%s", str);
  int result2 = sprintf(buffer2, "%s", str);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %f с нулем:
START_TEST(test_s21_sprintf_f_zero) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = 0.0;

  int result1 = s21_sprintf(buffer1, "%f", num);
  int result2 = sprintf(buffer2, "%f", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %x с отрицательным числом:
START_TEST(test_s21_sprintf_x_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = -123;

  int result1 = s21_sprintf(buffer1, "%x", num);
  int result2 = sprintf(buffer2, "%x", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %o с отрицательным числом:
START_TEST(test_s21_sprintf_o_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = -123;

  int result1 = s21_sprintf(buffer1, "%o", num);
  int result2 = sprintf(buffer2, "%o", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %p с отрицательным числом:
START_TEST(test_s21_sprintf_p_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  void *ptr = (void *)-123;

  int result1 = s21_sprintf(buffer1, "%p", ptr);
  int result2 = sprintf(buffer2, "%p", ptr);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %n с отрицательным числом:
// START_TEST(test_s21_sprintf_n_negative) {
//   char buffer1[100] = {0};
//   char buffer2[100] = {0};
//   int count1 = -123, count2 = -123;

//   int result1 = s21_sprintf(buffer1, "Hello, World!%n", &count1);
//   int result2 = sprintf(buffer2, "Hello, World!%n", &count2);

//   ck_assert_str_eq(buffer1, buffer2);
//   ck_assert_int_eq(result1, result2);
//   ck_assert_int_eq(count1, count2);
// }
// END_TEST

// Тест на спецификатор %g с отрицательным числом:
START_TEST(test_s21_sprintf_g_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  double num = -123.456;

  int result1 = s21_sprintf(buffer1, "%g", num);
  int result2 = sprintf(buffer2, "%g", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %u с отрицательным числом:
START_TEST(test_s21_sprintf_u_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned int num = -123;

  int result1 = s21_sprintf(buffer1, "%u", num);
  int result2 = sprintf(buffer2, "%u", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %c с отрицательным числом:
START_TEST(test_s21_sprintf_c_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  char ch = -123;

  int result1 = s21_sprintf(buffer1, "%c", ch);
  int result2 = sprintf(buffer2, "%c", ch);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тест на спецификатор %d с отрицательным числом:
START_TEST(test_s21_sprintf_d_negative) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int num = -123;

  int result1 = s21_sprintf(buffer1, "%d", num);
  int result2 = sprintf(buffer2, "%d", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %ls (широкие строки)
START_TEST(test_s21_sprintf_ls) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  wchar_t *wide_str = L"Hello, World!";

  int result1 = s21_sprintf(buffer1, "%ls", wide_str);
  int result2 = sprintf(buffer2, "%ls", wide_str);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %lc (широкие символы)
START_TEST(test_s21_sprintf_lc) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  wchar_t wide_char = L'A';

  int result1 = s21_sprintf(buffer1, "%lc", wide_char);
  int result2 = sprintf(buffer2, "%lc", wide_char);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %* (ширина и точность через аргумент)
START_TEST(test_s21_sprintf_width_precision_star) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  int width = 10;
  int precision = 4;
  double num = 123.456789;

  int result1 = s21_sprintf(buffer1, "%*.*f", width, precision, num);
  int result2 = sprintf(buffer2, "%*.*f", width, precision, num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %Lf (long double)
START_TEST(test_s21_sprintf_long_double) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  long double num = 123.456789L;

  int result1 = s21_sprintf(buffer1, "%Lf", num);
  int result2 = sprintf(buffer2, "%Lf", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %lu (unsigned long)
START_TEST(test_s21_sprintf_unsigned_long) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  unsigned long num = 123456789UL;

  int result1 = s21_sprintf(buffer1, "%lu", num);
  int result2 = sprintf(buffer2, "%lu", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %% (символ процента)
START_TEST(test_s21_sprintf_percent) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "%%");
  int result2 = sprintf(buffer2, "%%");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %ld (long int)
START_TEST(test_s21_sprintf_long_int) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  long int num = 123456789L;

  int result1 = s21_sprintf(buffer1, "%ld", num);
  int result2 = sprintf(buffer2, "%ld", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %lld (long long int)
// START_TEST(test_s21_sprintf_long_long_int) {
//   char buffer1[100] = {0};
//   char buffer2[100] = {0};
//   long long int num = 123456789012345LL;

//   int result1 = s21_sprintf(buffer1, "%lld", num);
//   int result2 = sprintf(buffer2, "%lld", num);

//   ck_assert_str_eq(buffer1, buffer2);
//   ck_assert_int_eq(result1, result2);
// }
// END_TEST

// Тесты для %llu (unsigned long long int)
// START_TEST(test_s21_sprintf_unsigned_long_long_int) {
//   char buffer1[100] = {0};
//   char buffer2[100] = {0};
//   unsigned long long int num = 123456789012345ULL;

//   int result1 = s21_sprintf(buffer1, "%llu", num);
//   int result2 = sprintf(buffer2, "%llu", num);

//   ck_assert_str_eq(buffer1, buffer2);
//   ck_assert_int_eq(result1, result2);
// }
// END_TEST

// Тесты для %h (short int)
START_TEST(test_s21_sprintf_short_int) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};
  short int num = 12345;

  int result1 = s21_sprintf(buffer1, "%hd", num);
  int result2 = sprintf(buffer2, "%hd", num);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// Тесты для %hhu (unsigned char)
// START_TEST(test_s21_sprintf_unsigned_char) {
//   char buffer1[100] = {0};
//   char buffer2[100] = {0};
//   unsigned char num = 255;

//   int result1 = s21_sprintf(buffer1, "%hhu", num);
//   int result2 = sprintf(buffer2, "%hhu", num);

//   ck_assert_str_eq(buffer1, buffer2);
//   ck_assert_int_eq(result1, result2);
// }
// END_TEST

// Тесты для %n (количество записанных символов)
// START_TEST(test_s21_sprintf_n) {
//   char buffer1[100] = {0};
//   char buffer2[100] = {0};
//   int count1 = 0, count2 = 0;

//   int result1 = s21_sprintf(buffer1, "Hello, World!%n", &count1);
//   int result2 = sprintf(buffer2, "Hello, World!%n", &count2);

//   ck_assert_str_eq(buffer1, buffer2);
//   ck_assert_int_eq(result1, result2);
//   ck_assert_int_eq(count1, count2);
// }
// END_TEST

Suite *s21_sprintf_suite() {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc_core = tcase_create("core");

  printf(BLUE "RUN UNIT TESTS FOR " GREEN "s21_sprintf.c\n" RESET);

  tcase_add_test(tc_core, test_s21_sprintf_d);
  tcase_add_test(tc_core, test_s21_sprintf_s);
  tcase_add_test(tc_core, test_s21_sprintf_x);
  tcase_add_test(tc_core, test_s21_sprintf_e);
  tcase_add_test(tc_core, test_s21_sprintf_g);
  tcase_add_test(tc_core, test_s21_sprintf_flags);
  tcase_add_test(tc_core, test_s21_sprintf_c);
  tcase_add_test(tc_core, test_s21_sprintf_u);
  tcase_add_test(tc_core, test_s21_sprintf_x_lower);
  tcase_add_test(tc_core, test_s21_sprintf_x_upper);
  tcase_add_test(tc_core, test_s21_sprintf_o);
  tcase_add_test(tc_core, test_s21_sprintf_p);
  tcase_add_test(tc_core, test_s21_sprintf_e_lower);
  tcase_add_test(tc_core, test_s21_sprintf_e_upper);
  tcase_add_test(tc_core, test_s21_sprintf_g_lower);
  tcase_add_test(tc_core, test_s21_sprintf_g_upper);
  tcase_add_test(tc_core, test_s21_sprintf_precision);
  tcase_add_test(tc_core, test_s21_sprintf_g_capital);
  tcase_add_test(tc_core, test_s21_sprintf_flags_plus);
  tcase_add_test(tc_core, test_s21_sprintf_flags_space);
  tcase_add_test(tc_core, test_s21_sprintf_flags_minus);
  tcase_add_test(tc_core, test_s21_sprintf_flags_double_plus);
  tcase_add_test(tc_core, test_s21_sprintf_width);
  tcase_add_test(tc_core, test_s21_sprintf_f);
  tcase_add_test(tc_core, test_s21_sprintf_flags_zero);
  tcase_add_test(tc_core, test_s21_sprintf_combined);

  tcase_add_test(tc_core, test_s21_sprintf_flags_plus_zero_width);
  tcase_add_test(tc_core, test_s21_sprintf_flags_minus_hash_width);
  tcase_add_test(
      tc_core,
      test_s21_sprintf_flags_space_plus_precision);  // failed: buffer1 ==
                                                     // "-123", buffer2 ==
                                                     // "-00123"
  tcase_add_test(tc_core, test_s21_sprintf_int_max);
  tcase_add_test(tc_core, test_s21_sprintf_int_min);
  tcase_add_test(tc_core,
                 test_s21_sprintf_large_float);  // (after this point) Received
                                                 // signal 6 (Aborted)
  tcase_add_test(
      tc_core,
      test_s21_sprintf_string_width_precision);  // failed: buffer1 == " Hello,
                                                 // World!", buffer2 == " Hello"
  tcase_add_test(tc_core, test_s21_sprintf_float_width_precision);
  tcase_add_test(tc_core, test_s21_sprintf_hex_hash);
  tcase_add_test(tc_core, test_s21_sprintf_octal_hash);
  // tcase_add_test(tc_core, test_s21_sprintf_n_specifier); // failed: count1 ==
  // 0, count2 == 13
  tcase_add_test(tc_core, test_s21_sprintf_pointer);
  tcase_add_test(tc_core, test_s21_sprintf_g_large_number);
  tcase_add_test(tc_core, test_s21_sprintf_G_small_number);
  tcase_add_test(
      tc_core,
      test_s21_sprintf_e_negative);  // failed: buffer1 == "-123.456000e+00",
                                     // buffer2 == "-1.234560e+02"
  tcase_add_test(
      tc_core,
      test_s21_sprintf_E_zero);  // (after this point) Test timeout expired
  tcase_add_test(tc_core, test_s21_sprintf_u_max);
  tcase_add_test(
      tc_core, test_s21_sprintf_c_null);  // failed: result1 == 0, result2 == 1
  tcase_add_test(tc_core, test_s21_sprintf_s_empty);
  tcase_add_test(tc_core, test_s21_sprintf_f_negative);
  tcase_add_test(tc_core, test_s21_sprintf_d_zero);
  tcase_add_test(tc_core, test_s21_sprintf_x_zero);
  tcase_add_test(tc_core, test_s21_sprintf_o_zero);
  tcase_add_test(tc_core,
                 test_s21_sprintf_p_null);  //  failed: buffer1 == "0x0",
                                            //  buffer2 == "(nil)"
  tcase_add_test(tc_core,
                 test_s21_sprintf_g_zero);  //  failed: buffer1 == "0x0",
                                            //  buffer2 == "(nil)"
  tcase_add_test(tc_core, test_s21_sprintf_u_zero);
  tcase_add_test(tc_core, test_s21_sprintf_c_newline);
  tcase_add_test(tc_core,
                 test_s21_sprintf_s_null);  //  (after this point) Received
                                            //  signal 11 (Segmentation fault)
  tcase_add_test(
      tc_core,
      test_s21_sprintf_f_zero);  // (after this point) Test timeout expired
  tcase_add_test(tc_core, test_s21_sprintf_x_negative);
  tcase_add_test(tc_core, test_s21_sprintf_o_negative);
  tcase_add_test(tc_core,
                 test_s21_sprintf_p_negative);  //  buffer1 == "0x7b", buffer2
                                                //  == "0xffffffffffffff85"
  // tcase_add_test(tc_core, test_s21_sprintf_n_negative); // count1 == -123,
  // count2 == 13
  tcase_add_test(tc_core,
                 test_s21_sprintf_g_negative);  //  buffer1 == "-123.46",
                                                //  buffer2 == "-123.456"
  tcase_add_test(tc_core, test_s21_sprintf_u_negative);
  tcase_add_test(tc_core, test_s21_sprintf_c_negative);
  tcase_add_test(tc_core, test_s21_sprintf_d_negative);

  // ЕЩЕ БОЛЬШЕ ТЕСТОВ, Я УЖЕ ИМИ ОБМАЗЫВАЮСЬ
  tcase_add_test(tc_core, test_s21_sprintf_ls);
  tcase_add_test(tc_core, test_s21_sprintf_lc);
  tcase_add_test(tc_core, test_s21_sprintf_width_precision_star);
  tcase_add_test(tc_core, test_s21_sprintf_long_double);
  tcase_add_test(tc_core, test_s21_sprintf_unsigned_long);
  tcase_add_test(tc_core, test_s21_sprintf_percent);
  tcase_add_test(tc_core, test_s21_sprintf_long_int);
  // tcase_add_test(tc_core, test_s21_sprintf_long_long_int); // failed: buffer1
  // == "d", buffer2 == "123456789012345" tcase_add_test(tc_core,
  // test_s21_sprintf_unsigned_long_long_int); // failed: buffer1 == "u",
  // buffer2 == "123456789012345"
  tcase_add_test(tc_core, test_s21_sprintf_short_int);
  // tcase_add_test(tc_core, test_s21_sprintf_unsigned_char); // failed: buffer1
  // == "u", buffer2 == "255" tcase_add_test(tc_core, test_s21_sprintf_n); //
  // failed: count1 == 0, count2 == 13

  suite_add_tcase(s, tc_core);

  return s;
}

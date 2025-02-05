#include "unit_tests_s21_string.h"

START_TEST(test_s21_memchr) {
  char str[] = "Hello, World!";

  ck_assert_ptr_eq(s21_memchr(str, 'o', 13), memchr(str, 'o', 13));
  ck_assert_ptr_eq(s21_memchr(str, 'z', 13), memchr(str, 'z', 13));
  ck_assert_ptr_eq(s21_memchr(str, '\0', 13), memchr(str, '\0', 13));
}
END_TEST

START_TEST(test_s21_memcmp) {
  char str1[] = "Hello";
  char str2[] = "Hellp";

  ck_assert_int_eq(s21_memcmp(str1, str2, 4), memcmp(str1, str2, 4));
  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
  // ck_assert_int_eq(s21_memcmp(str1, str1, 5), memcmp(str1, str1, 5));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char src[] = "Hello";
  char dest1[10] = {0}, dest2[10] = {0};

  s21_memcpy(dest1, src, 5);
  memcpy(dest2, src, 5);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_memset) {
  char str1[10] = {0}, str2[10] = {0};

  s21_memset(str1, 'A', 5);
  memset(str2, 'A', 5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest[20] = "Hello";
  char src[] = ", World!";

  ck_assert_str_eq(s21_strncat(dest, src, 7), strncat(dest, src, 7));
}
END_TEST

START_TEST(test_s21_strchr) {
  char str[] = "Hello, World!";

  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(test_s21_strcspn) {
  char str[] = "Hello, World!";
  char reject[] = " ,!";

  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char dest[20] = {0};
  char src[] = "Hello";

  ck_assert_str_eq(s21_strncpy(dest, src, 5), strncpy(dest, src, 5));
}
END_TEST

START_TEST(test_s21_strlen) {
  char str[] = "Hello, World!";

  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strerror) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(1), strerror(1));
#ifdef __linux__
  ck_assert_str_eq(s21_strerror(999), "Unknown error 999");
#else
  ck_assert_str_eq(s21_strerror(999), "Unknown error: 999");
#endif
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char str[] = "Hello, World!";
  char accept[] = " ,!";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strrchr) {
  char str[] = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_s21_strstr) {
  char haystack[] = "Hello, World!";
  char needle[] = "World";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strtok) {
  char str[] = "Hello, World!";
  char str_copy[] = "Hello, World!";
  char delim[] = ", ";

  char *token = s21_strtok(str_copy, delim);
  char *std_token = strtok(str, delim);

  while (token != S21_NULL && std_token != S21_NULL) {
    ck_assert_str_eq(token, std_token);
    token = s21_strtok(S21_NULL, delim);
    std_token = strtok(S21_NULL, delim);
  }

  token = s21_strtok(S21_NULL, delim);
  std_token = strtok(S21_NULL, delim);

  ck_assert_ptr_eq(token, std_token);
}
END_TEST

START_TEST(test_s21_strcpy) {
  char dest1[20] = {0};
  char dest2[20] = {0};
  char src[] = "Hello";

  ck_assert_str_eq(s21_strcpy(dest1, src), strcpy(dest2, src));
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_to_upper) {
  char str[] = "hello";

  char *result = (char *)s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char str[] = "HELLO";

  char *result = (char *)s21_to_lower(str);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_s21_insert) {
  char src[] = "Hello!";
  char str[] = " World";

  char *result = (char *)s21_insert(src, str, 5);
  ck_assert_str_eq(result, "Hello World!");

  free(result);
}
END_TEST

START_TEST(test_s21_trim) {
  char src[] = "  Hello, World!  ";
  char trim_chars[] = " ";

  char *result = (char *)s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(test_s21_strncmp) {
  char src[] = "  Hello, World!  ";
  char src2[] = "    abc";

  int s21_result = s21_strncmp(src, src2, 1);
  int result = strncmp(src, src2, 1);
  ck_assert_int_eq(result, s21_result);
}
END_TEST

// Тест на s21_to_upper с динамическим выделением памяти:
START_TEST(test_s21_to_upper_dynamic) {
  const char *input = "hello, world!";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  strcpy(dynamic_input, input);

  char *result = (char *)s21_to_upper(dynamic_input);
  ck_assert_str_eq(result, "HELLO, WORLD!");
  free(result);
  free(dynamic_input);
}
END_TEST

// Тест на s21_to_lower с динамическим выделением памяти:
START_TEST(test_s21_to_lower_dynamic) {
  const char *input = "HELLO, WORLD!";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  ;
  strcpy(dynamic_input, input);

  char *result = (char *)s21_to_lower(dynamic_input);
  ck_assert_str_eq(result, "hello, world!");
  free(result);
  free(dynamic_input);
}
END_TEST

// Тест на s21_insert с динамическим выделением памяти:
START_TEST(test_s21_insert_dynamic) {
  const char *src = "Hello!";
  const char *str = " World";
  char *dynamic_src = calloc(strlen(src) + 1, sizeof(char));
  strcpy(dynamic_src, src);

  char *result = (char *)s21_insert(dynamic_src, str, 5);
  ck_assert_str_eq(result, "Hello World!");

  free(dynamic_src);
  free(result);
}
END_TEST

// Тест на s21_trim с динамическим выделением памяти:
START_TEST(test_s21_trim_dynamic) {
  const char *src = "  Hello, World!  ";
  const char *trim_chars = " ";
  char *dynamic_src = calloc(strlen(src) + 1, sizeof(char));
  strcpy(dynamic_src, src);

  char *result = (char *)s21_trim(dynamic_src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
  free(dynamic_src);
}
END_TEST

// Тест на s21_realloc:
START_TEST(test_s21_realloc) {
  size_t old_size = 10;
  size_t new_size = 20;
  char *ptr = calloc(old_size, sizeof(char));
  strcpy(ptr, "Hello");

  char *new_ptr = s21_realloc(ptr, old_size, new_size);
  ck_assert_ptr_nonnull(new_ptr);
  ck_assert_str_eq(new_ptr, "Hello");

  free(new_ptr);
}
END_TEST

// Тест на s21_memchr с динамическим выделением памяти:
START_TEST(test_s21_memchr_dynamic) {
  const char *input = "Hello, World!";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  ;
  strcpy(dynamic_input, input);

  void *result = s21_memchr(dynamic_input, 'o', 13);
  ck_assert_ptr_eq(result, memchr(dynamic_input, 'o', 13));

  free(dynamic_input);
}
END_TEST

// Тест на s21_memcmp с динамическим выделением памяти:
START_TEST(test_s21_memcmp_dynamic) {
  const char *input1 = "Hello";
  const char *input2 = "Hellp";
  char *dynamic_input1 = calloc(strlen(input1) + 1, sizeof(char));
  char *dynamic_input2 = calloc(strlen(input2) + 1, sizeof(char));
  strcpy(dynamic_input1, input1);
  strcpy(dynamic_input2, input2);

  int result = s21_memcmp(dynamic_input1, dynamic_input2, 5);
  ck_assert_int_eq(result, memcmp(dynamic_input1, dynamic_input2, 5));

  free(dynamic_input1);
  free(dynamic_input2);
}
END_TEST

// Тест на s21_memcpy с динамическим выделением памяти:
START_TEST(test_s21_memcpy_dynamic) {
  const char *src = "Hello";
  char *dynamic_src = calloc(strlen(src) + 1, sizeof(char));
  strcpy(dynamic_src, src);

  char *dest1 = calloc(10, sizeof(char));
  char *dest2 = calloc(10, sizeof(char));

  s21_memcpy(dest1, dynamic_src, 5);
  memcpy(dest2, dynamic_src, 5);
  ck_assert_str_eq(dest1, dest2);

  free(dynamic_src);
  free(dest1);
  free(dest2);
}
END_TEST

// Тест на s21_memset с динамическим выделением памяти:
START_TEST(test_s21_memset_dynamic) {
  char *str1 = calloc(10, sizeof(int));
  char *str2 = calloc(10, sizeof(int));

  s21_memset(str1, 'S', 5);
  memset(str2, 'S', 5);
  ck_assert_str_eq(str1, str2);

  free(str1);
  free(str2);
}
END_TEST

// Тест на s21_strncat с динамическим выделением памяти:
START_TEST(test_s21_strncat_dynamic) {
  const char dest_input[] = "Hello";
  const char src_input[] = ", World!";
  char *dynamic_s21 =
      malloc((strlen(dest_input) + strlen(src_input) + 1) * sizeof(char));
  char *dynamic_orig =
      malloc((strlen(dest_input) + strlen(src_input) + 1) * sizeof(char));
  strcpy(dynamic_s21, dest_input);
  strcpy(dynamic_orig, dest_input);

  char *result1 = s21_strncat(dynamic_s21, (char *)src_input, 7);
  char *result2 = strncat(dynamic_orig, (char *)src_input, 7);
  ck_assert_str_eq(result1, result2);
  ck_assert_str_eq(dynamic_s21, dynamic_orig);

  free(dynamic_s21);
  free(dynamic_orig);
}
END_TEST

// Тест на s21_strchr с динамическим выделением памяти:
START_TEST(test_s21_strchr_dynamic) {
  const char *input = "Hello, World!";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  ;
  strcpy(dynamic_input, input);

  char *result = s21_strchr(dynamic_input, 'o');
  ck_assert_ptr_eq(result, strchr(dynamic_input, 'o'));

  free(dynamic_input);
}
END_TEST

// Тест на s21_strcspn с динамическим выделением памяти:
START_TEST(test_s21_strcspn_dynamic) {
  const char *input = "Hello, World!";
  const char *reject = " ,!";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  ;
  strcpy(dynamic_input, input);

  size_t result = s21_strcspn(dynamic_input, reject);
  ck_assert_int_eq(result, strcspn(dynamic_input, reject));

  free(dynamic_input);
}
END_TEST

// Тест на s21_strncpy с динамическим выделением памяти:
START_TEST(test_s21_strncpy_dynamic) {
  const char *src = "Hello";
  char *dynamic_src = calloc(strlen(src) + 1, sizeof(char));
  strcpy(dynamic_src, src);

  char *dest1 = calloc(10, sizeof(char));
  char *dest2 = calloc(10, sizeof(char));

  s21_strncpy(dest1, dynamic_src, 5);
  strncpy(dest2, dynamic_src, 5);
  ck_assert_str_eq(dest1, dest2);

  free(dynamic_src);
  free(dest1);
  free(dest2);
}
END_TEST

// Тест на s21_strlen с динамическим выделением памяти:
START_TEST(test_s21_strlen_dynamic) {
  const char *input = "Hello, World!";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  ;
  strcpy(dynamic_input, input);

  size_t result = s21_strlen(dynamic_input);
  ck_assert_int_eq(result, strlen(dynamic_input));

  free(dynamic_input);
}
END_TEST

// Тест на s21_strerror с динамическим выделением памяти:
START_TEST(test_s21_strerror_dynamic) {
  int errnum = 0;
  char *result = s21_strerror(errnum);
  ck_assert_str_eq(result, strerror(errnum));
}
END_TEST

// Тест на s21_strpbrk с динамическим выделением памяти:
START_TEST(test_s21_strpbrk_dynamic) {
  const char *input = "Hello, World!";
  const char *accept = " ,!";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  ;
  strcpy(dynamic_input, input);

  char *result = s21_strpbrk(dynamic_input, accept);
  ck_assert_ptr_eq(result, strpbrk(dynamic_input, accept));

  free(dynamic_input);
}
END_TEST

// Тест на s21_strrchr с динамическим выделением памяти:
START_TEST(test_s21_strrchr_dynamic) {
  const char *input = "Hello, World!";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  ;
  strcpy(dynamic_input, input);

  char *result = s21_strrchr(dynamic_input, 'o');
  ck_assert_ptr_eq(result, strrchr(dynamic_input, 'o'));

  free(dynamic_input);
}
END_TEST

// Тест на s21_strstr с динамическим выделением памяти:
START_TEST(test_s21_strstr_dynamic) {
  const char *haystack = "Hello, World!";
  const char *needle = "World";
  char *dynamic_haystack = calloc(strlen(haystack) + 1, sizeof(char));
  strcpy(dynamic_haystack, haystack);

  char *result = s21_strstr(dynamic_haystack, needle);
  ck_assert_ptr_eq(result, strstr(dynamic_haystack, needle));

  free(dynamic_haystack);
}
END_TEST

// Тест на s21_strtok с динамическим выделением памяти:
START_TEST(test_s21_strtok_dynamic) {
  const char *input = "Hello, World!";
  const char *delim = ", ";
  char *dynamic_input = calloc(strlen(input) + 1, sizeof(char));
  ;
  strcpy(dynamic_input, input);

  char *token = s21_strtok(dynamic_input, delim);
  char *std_token = strtok(dynamic_input, delim);

  while (token != S21_NULL && std_token != S21_NULL) {
    ck_assert_str_eq(token, std_token);
    token = s21_strtok(S21_NULL, delim);
    std_token = strtok(S21_NULL, delim);
  }

  free(dynamic_input);
}
END_TEST

// Тест на s21_strcpy с динамическим выделением памяти:
START_TEST(test_s21_strcpy_dynamic) {
  const char *src = "Hello";
  char *dynamic_src = calloc(strlen(src) + 1, sizeof(char));
  strcpy(dynamic_src, src);

  char *dest1 = calloc(strlen(src) + 1, sizeof(char));
  char *dest2 = calloc(strlen(src) + 1, sizeof(char));

  s21_strcpy(dest1, dynamic_src);
  strcpy(dest2, dynamic_src);
  ck_assert_str_eq(dest1, dest2);

  free(dynamic_src);
  free(dest1);
  free(dest2);
}
END_TEST

// ДЕЛАЮ ЕЩЕ БОЛЬШЕ ТЕСТОВ ДЛЯ ШАРПОВЫХ ФУНКЦИЙ НА ВСЕ ВОЗМОЖНЫЕ ПРОБЛЕМЫ

// Тесты для s21_to_upper
START_TEST(test_s21_to_upper_basic) {
  const char *input = "hello, world!";
  char *result = (char *)s21_to_upper(input);

  ck_assert_str_eq(result, "HELLO, WORLD!");

  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_empty) {
  const char *input = "";
  char *result = (char *)s21_to_upper(input);

  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_null) {
  const char *input = NULL;
  char *result = (char *)s21_to_upper(input);

  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_to_upper_no_change) {
  const char *input = "HELLO, WORLD!";
  char *result = (char *)s21_to_upper(input);

  ck_assert_str_eq(result, "HELLO, WORLD!");

  free(result);
}
END_TEST

// Тесты для s21_to_lower
START_TEST(test_s21_to_lower_basic) {
  const char *input = "HELLO, WORLD!";
  char *result = (char *)s21_to_lower(input);

  ck_assert_str_eq(result, "hello, world!");

  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  const char *input = "";
  char *result = (char *)s21_to_lower(input);

  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_null) {
  const char *input = NULL;
  char *result = (char *)s21_to_lower(input);

  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_to_lower_no_change) {
  const char *input = "hello, world!";
  char *result = (char *)s21_to_lower(input);

  ck_assert_str_eq(result, "hello, world!");

  free(result);
}
END_TEST

// Тесты для s21_insert
START_TEST(test_s21_insert_basic) {
  const char *src = "Hello!";
  const char *str = " World";
  char *result = (char *)s21_insert(src, str, 5);

  ck_assert_str_eq(result, "Hello World!");

  free(result);
}
END_TEST

START_TEST(test_s21_insert_empty_src) {
  const char *src = "";
  const char *str = "Hello";
  char *result = (char *)s21_insert(src, str, 0);

  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(test_s21_insert_empty_str) {
  const char *src = "Hello!";
  const char *str = "";
  char *result = (char *)s21_insert(src, str, 5);

  ck_assert_str_eq(result, "Hello!");

  free(result);
}
END_TEST

START_TEST(test_s21_insert_null_src) {
  const char *src = NULL;
  const char *str = "Hello";
  char *result = (char *)s21_insert(src, str, 0);

  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_insert_null_str) {
  const char *src = "Hello!";
  const char *str = NULL;
  char *result = (char *)s21_insert(src, str, 5);

  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_insert_invalid_index) {
  const char *src = "Hello!";
  const char *str = " World";
  char *result = (char *)s21_insert(src, str, 10);

  ck_assert_ptr_null(result);
}
END_TEST

// Тесты для s21_trim
START_TEST(test_s21_trim_basic) {
  const char *src = "  Hello, World!  ";
  const char *trim_chars = " ";
  char *result = (char *)s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "Hello, World!");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty_src) {
  const char *src = "";
  const char *trim_chars = " ";
  char *result = (char *)s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty_trim_chars) {
  const char *src = "  Hello, World!  ";
  const char *trim_chars = "";
  char *result = (char *)s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "  Hello, World!  ");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_null_src) {
  const char *src = NULL;
  const char *trim_chars = " ";
  char *result = (char *)s21_trim(src, trim_chars);

  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_trim_null_trim_chars) {
  const char *src = "  Hello, World!  ";
  const char *trim_chars = NULL;
  char *result = (char *)s21_trim(src, trim_chars);

  ck_assert_ptr_null(result);

  free(result);
}
END_TEST

START_TEST(test_s21_trim_no_trim) {
  const char *src = "Hello, World!";
  const char *trim_chars = " ";
  char *result = (char *)s21_trim(src, trim_chars);

  ck_assert_str_eq(result, "Hello, World!");

  free(result);
}
END_TEST

START_TEST(test_s21_strncmp_basic) {
  const char *str1 = "Hello";
  const char *str2 = "Hellp";

  ck_assert_int_eq(s21_strncmp(str1, str2, 4), strncmp(str1, str2, 4));
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_s21_strncmp_equal_strings) {
  const char *str1 = "Hello";
  const char *str2 = "Hello";

  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_s21_strncmp_empty_strings) {
  const char *str1 = "";
  const char *str2 = "";

  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
}
END_TEST

START_TEST(test_s21_strncmp_partial_comparison) {
  const char *str1 = "Hello, World!";
  const char *str2 = "Hello, there!";

  ck_assert_int_eq(s21_strncmp(str1, str2, 7), strncmp(str1, str2, 7));
}
END_TEST

START_TEST(test_s21_strncmp_zero_length) {
  const char *str1 = "Hello";
  const char *str2 = "Hellp";

  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
}
END_TEST

START_TEST(test_s21_strncmp_special_chars) {
  const char *str1 = "Hello\tWorld!";
  const char *str2 = "Hello\nWorld!";

  // Сравнение строк с специальными символами
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_s21_strncmp_unicode) {
  const char *str1 = "Привет";
  const char *str2 = "Пока";

  // Сравнение строк с Unicode символами
  ck_assert_int_eq(s21_strncmp(str1, str2, 4), strncmp(str1, str2, 4));
}
END_TEST

START_TEST(test_s21_strncmp_partial_match) {
  const char *str1 = "Hello, World!";
  const char *str2 = "Hello, there!";

  ck_assert_int_eq(s21_strncmp(str1, str2, 7), strncmp(str1, str2, 7));
}
END_TEST

START_TEST(test_s21_strpbrk_basic) {
  const char *str = "Hello, World!";
  const char *accept = " ,!";

  // Поиск первого вхождения символа из accept
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_no_match) {
  const char *str = "Hello, World!";
  const char *accept = "xyz";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_accept) {
  const char *str = "Hello, World!";
  const char *accept = "";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_str) {
  const char *str = "";
  const char *accept = " ,!";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_first_char_match) {
  const char *str = "Hello, World!";
  const char *accept = "H";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_multiple_matches) {
  const char *str = "Hello, World!";
  const char *accept = "lo";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_accept_at_start) {
  const char *str = "Hello, World!";
  const char *accept = "H";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_accept_at_end) {
  const char *str = "Hello, World!";
  const char *accept = "!";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_accept_contains_null) {
  const char *str = "Hello, World!";
  const char *accept = "\0";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_str_contains_null) {
  const char *str = "Hello\0World!";
  const char *accept = "W";

  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strrchr_basic) {
  const char *str = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
}
END_TEST

START_TEST(test_s21_strrchr_no_match) {
  const char *str = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_s21_strrchr_null_char) {
  const char *str = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_s21_strrchr_first_char_match) {
  const char *str = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, 'H'), strrchr(str, 'H'));
}
END_TEST

START_TEST(test_s21_strrchr_last_char_match) {
  const char *str = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, '!'), strrchr(str, '!'));
}
END_TEST

START_TEST(test_s21_strrchr_multiple_matches) {
  const char *str = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
}
END_TEST

START_TEST(test_s21_strrchr_char_not_in_str) {
  const char *str = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_s21_strrchr_empty_str) {
  const char *str = "";

  ck_assert_ptr_eq(s21_strrchr(str, 'H'), strrchr(str, 'H'));
}
END_TEST

START_TEST(test_s21_strrchr_char_at_start) {
  const char *str = "Hello, World!";

  ck_assert_ptr_eq(s21_strrchr(str, 'H'), strrchr(str, 'H'));
}
END_TEST

START_TEST(test_s21_strstr_basic) {
  const char *haystack = "Hello, World!";
  const char *needle = "World";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_no_match) {
  const char *haystack = "Hello, World!";
  const char *needle = "xyz";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_empty_needle) {
  const char *haystack = "Hello, World!";
  const char *needle = "";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_empty_haystack) {
  const char *haystack = "";
  const char *needle = "World";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_needle_at_start) {
  const char *haystack = "Hello, World!";
  const char *needle = "Hello";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_needle_at_end) {
  const char *haystack = "Hello, World!";
  const char *needle = "World!";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_needle_longer_than_haystack) {
  const char *haystack = "Hello";
  const char *needle = "Hello, World!";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_needle_empty) {
  const char *haystack = "Hello, World!";
  const char *needle = "";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_haystack_empty) {
  const char *haystack = "";
  const char *needle = "Hello";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite *s21_string_suite() {
  Suite *s = suite_create("s21_string");
  TCase *tc_core = tcase_create("core");

  printf(BLUE "RUN UNIT TESTS FOR " GREEN "s21_string.c\n" RESET);

  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_s21_strcpy);
  tcase_add_test(tc_core, test_s21_to_upper);
  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_insert);
  tcase_add_test(tc_core, test_s21_trim);
  tcase_add_test(tc_core, test_s21_strncmp);

  tcase_add_test(tc_core, test_s21_memchr_dynamic);
  tcase_add_test(tc_core, test_s21_memcmp_dynamic);
  tcase_add_test(tc_core, test_s21_memcpy_dynamic);
  // str1 == "SSSSS", str2 == "SSSSS" CALLOC OK MALLOC FAILED
  // test_s21_memset_dynamic
  tcase_add_test(tc_core, test_s21_memset_dynamic);
  tcase_add_test(tc_core, test_s21_strncat_dynamic);
  tcase_add_test(tc_core, test_s21_strchr_dynamic);
  tcase_add_test(tc_core, test_s21_strcspn_dynamic);
  tcase_add_test(tc_core, test_s21_strncpy_dynamic);
  tcase_add_test(tc_core, test_s21_strlen_dynamic);
  tcase_add_test(tc_core, test_s21_strerror_dynamic);
  tcase_add_test(tc_core, test_s21_strpbrk_dynamic);
  tcase_add_test(tc_core, test_s21_strrchr_dynamic);
  tcase_add_test(tc_core, test_s21_strstr_dynamic);
  tcase_add_test(tc_core, test_s21_strtok_dynamic);
  tcase_add_test(tc_core, test_s21_strcpy_dynamic);

  tcase_add_test(tc_core, test_s21_to_upper_basic);
  tcase_add_test(tc_core, test_s21_to_upper_empty);
  tcase_add_test(tc_core, test_s21_to_upper_null);
  tcase_add_test(tc_core, test_s21_to_upper_no_change);
  tcase_add_test(tc_core, test_s21_to_lower_basic);
  tcase_add_test(tc_core, test_s21_to_lower_empty);
  tcase_add_test(tc_core, test_s21_to_lower_null);
  tcase_add_test(tc_core, test_s21_to_lower_no_change);
  tcase_add_test(tc_core, test_s21_insert_basic);
  tcase_add_test(tc_core, test_s21_insert_empty_src);
  tcase_add_test(tc_core, test_s21_insert_empty_str);
  tcase_add_test(tc_core, test_s21_insert_null_src);
  tcase_add_test(tc_core, test_s21_insert_null_str);
  tcase_add_test(tc_core, test_s21_insert_invalid_index);
  tcase_add_test(tc_core, test_s21_trim_basic);
  tcase_add_test(tc_core, test_s21_trim_empty_src);
  tcase_add_test(tc_core, test_s21_trim_empty_trim_chars);
  tcase_add_test(tc_core, test_s21_trim_null_src);
  tcase_add_test(tc_core, test_s21_trim_null_trim_chars);
  tcase_add_test(tc_core, test_s21_trim_no_trim);

  tcase_add_test(tc_core, test_s21_realloc);
  tcase_add_test(tc_core, test_s21_trim_dynamic);
  tcase_add_test(tc_core, test_s21_insert_dynamic);
  tcase_add_test(tc_core, test_s21_to_lower_dynamic);
  tcase_add_test(tc_core, test_s21_to_upper_dynamic);

  // Еще тесты для s21_strncmp
  tcase_add_test(tc_core, test_s21_strncmp_basic);
  tcase_add_test(tc_core, test_s21_strncmp_equal_strings);
  tcase_add_test(tc_core, test_s21_strncmp_empty_strings);
  tcase_add_test(tc_core, test_s21_strncmp_partial_comparison);
  tcase_add_test(tc_core, test_s21_strncmp_zero_length);
  tcase_add_test(tc_core, test_s21_strncmp_special_chars);
  tcase_add_test(tc_core, test_s21_strncmp_unicode);
  tcase_add_test(tc_core, test_s21_strncmp_partial_match);

  // Еще тесты для s21_strpbrk
  tcase_add_test(tc_core, test_s21_strpbrk_basic);
  tcase_add_test(tc_core, test_s21_strpbrk_no_match);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_accept);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_str);
  tcase_add_test(tc_core, test_s21_strpbrk_first_char_match);
  tcase_add_test(tc_core, test_s21_strpbrk_multiple_matches);
  tcase_add_test(tc_core, test_s21_strpbrk_accept_at_start);
  tcase_add_test(tc_core, test_s21_strpbrk_accept_at_end);
  tcase_add_test(tc_core, test_s21_strpbrk_accept_contains_null);
  tcase_add_test(tc_core, test_s21_strpbrk_str_contains_null);

  // Еще тесты для s21_strrchr
  tcase_add_test(tc_core, test_s21_strrchr_basic);
  tcase_add_test(tc_core, test_s21_strrchr_no_match);
  tcase_add_test(tc_core, test_s21_strrchr_null_char);
  tcase_add_test(tc_core, test_s21_strrchr_first_char_match);
  tcase_add_test(tc_core, test_s21_strrchr_last_char_match);
  tcase_add_test(tc_core, test_s21_strrchr_multiple_matches);
  tcase_add_test(tc_core, test_s21_strrchr_char_not_in_str);
  tcase_add_test(tc_core, test_s21_strrchr_null_char);
  tcase_add_test(tc_core, test_s21_strrchr_empty_str);
  tcase_add_test(tc_core, test_s21_strrchr_char_at_start);

  // Еще тесты для s21_strstr
  tcase_add_test(tc_core, test_s21_strstr_basic);
  tcase_add_test(tc_core, test_s21_strstr_no_match);
  tcase_add_test(tc_core, test_s21_strstr_empty_needle);
  tcase_add_test(tc_core, test_s21_strstr_empty_haystack);
  tcase_add_test(tc_core, test_s21_strstr_needle_at_start);
  tcase_add_test(tc_core, test_s21_strstr_needle_at_end);
  tcase_add_test(tc_core, test_s21_strstr_needle_longer_than_haystack);
  tcase_add_test(tc_core, test_s21_strstr_needle_empty);
  tcase_add_test(tc_core, test_s21_strstr_haystack_empty);

  suite_add_tcase(s, tc_core);

  return s;
}
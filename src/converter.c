#include "converter.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "sharp_string.h"

int calculateLengthOfNum(long long *number, const long long *num_copy,
                         int *is_negative) {
  long temp = *num_copy;
  int length = 0;
  do {
    length++;
    temp /= 10;
  } while (temp != 0);

  if (*num_copy < 0) {
    *is_negative = 1;
    *number = -(*number);
  }

  length += *is_negative;
  return length;
}

int calculateLengthOfUnsigned(const unsigned long *num_copy, int *is_negative) {
  unsigned long temp = *num_copy;
  int length = 0;
  do {
    length++;
    temp /= 10;
  } while (temp != 0);

  length += *is_negative;
  return length;
}

char *intToString(long long number, const int *flags) {
  long long temp = number;
  int is_negative = 0;
  int length = calculateLengthOfNum(&number, &temp, &is_negative);

  // if ((*flags & SHOW_SIGN && !is_negative) || (*flags & SIGN_PLACE &&
  // !is_negative)) length++;
  if (!(*flags & ITS_A_FLOAT)) {
    if ((*flags & SHOW_SIGN || *flags & SIGN_PLACE) && !is_negative) length++;
  }

  char *result = (char *)calloc(length + 1, sizeof(char));
  if (result == S21_NULL) return S21_NULL;

  result[length] = '\0';

  for (int i = length - 1; i >= is_negative; i--) {
    result[i] = (number % 10) + '0';
    number /= 10;
  }

  if (*flags & SHOW_SIGN) result[0] = '+';
  if (!(*flags & ITS_A_FLOAT)) {
    if (*flags & SIGN_PLACE) result[0] = ' ';
  }
  if (is_negative) result[0] = '-';

  return result;
}

char *intToHexStr(long unsigned num, int registry, int flags) {
  // если registry == 0, то вернутся маленькие буквы, иначе большие
  unsigned num_is_zero = (num == 0);
  unsigned long num_tmp = num;
  int is_negative = 0, zeros = 0,
      len = calculateLengthOfUnsigned(&num_tmp, &is_negative);
  char *res = (char *)calloc(len + 5, sizeof(char)), *tmp_res = S21_NULL;
  if (res == S21_NULL) return S21_NULL;

  for (int i = len - 1, digit = 0; i >= 0; i--) {
    digit = num % 16;
    res[i] = (digit < 10)      ? digit + '0'
             : (registry == 1) ? digit + 'A' - 10
                               : digit + 'a' - 10;
    num /= 16;
  }
  res[len] = '\0';

  while (res[zeros] == '0') zeros++;
  if (!num_is_zero) {
    tmp_res = (char *)calloc((s21_strlen(res) - zeros + 5), sizeof(char));
    tmp_res = s21_memcpy(tmp_res, res + zeros, s21_strlen(res) + 1);
  } else {
    tmp_res = (char *)calloc(2, sizeof(char));
    tmp_res[0] = '0';
    tmp_res[1] = '\0';
  }
  if (flags & SHOW_NUMBER_SYSTEM && !(flags & FILL_WITH_ZEROS)) {
    cat_number_system(registry, &tmp_res, s21_strlen(tmp_res));
  }
  free(res);
  return tmp_res;
}

char *intToOctStr(long long num, int flags) {
  unsigned num_is_zero = (num == 0);
  if (num < 0) num = (unsigned long)(num);
  long long num_tmp = num;
  int is_negative = 0, zeros = 0, len = 0;
  calculateLengthOfNum(&num, &num_tmp, &is_negative);
  for (long delim = num; delim > 0; delim /= 8) len++;
  char *res = (char *)calloc(len + 2, sizeof(char)), *tmp_res = S21_NULL;
  if (res == S21_NULL) return S21_NULL;

  for (int i = len, digit = 0; i >= 0; i--) {
    digit = num % 8;
    res[i] = digit + '0';
    num /= 8;
  }
  res[len + 1] = '\0';

  while (res[zeros] == '0') zeros++;
  if (!num_is_zero) {
    tmp_res = (char *)calloc((s21_strlen(res) - zeros + 2), sizeof(char));
    tmp_res = s21_memcpy(tmp_res, res + zeros, s21_strlen(res));
  } else {
    tmp_res = (char *)calloc(2, sizeof(char));
    tmp_res[0] = '0';
    tmp_res[1] = '\0';
  }
  if (flags & SHOW_NUMBER_SYSTEM && !(flags & FILL_WITH_ZEROS)) {
    cat_number_system(3, &tmp_res, s21_strlen(tmp_res));
  }
  free(res);
  return tmp_res;
}

long double transformToExpForm(long double num, int *degree) {
  if (num >= -1 && num <= 1 && num != 0) {
    while (num >= -1 && num <= 1) {
      num *= 10;
      (*degree)--;
    }
  } else {
    while (num >= 10 || num <= -10) {
      num /= 10;
      (*degree)++;
    }
  }
  return num;
}

void fillExpPart(char *exp_part, int degree, int registry) {
  exp_part[0] = (registry) ? 'E' : 'e';
  if (degree < 0)
    exp_part[1] = '-';
  else
    exp_part[1] = '+';
  exp_part[2] = (abs(degree) / 10) % 10 + '0';
  exp_part[3] = abs(degree) % 10 + '0';
}

char *doubleToExpStr(long double num, int accuracy, int *flags, int registry,
                     char specificator) {
  int degree = 0;
  long double num_formated = transformToExpForm(num, &degree);
  char *res = doubleToStringWithAccuracy(num_formated, accuracy, flags,
                                         specificator),
       exponent_part[5] = {0};
  fillExpPart(exponent_part, degree, registry);
  s21_strncat(res, exponent_part, 4);
  return res;
}

long double round_to_precision(long double value, int precision) {
  long double factor = pow(10, precision);
  return round(value * factor) / factor;
}

// void int2bin(int a, char *buffer, int buf_size) {
//   buffer += (buf_size - 1);
//   for (int i = 31; i >= 0; i--) {
//     *buffer-- = (a & 1) + '0';
//     a >>= 1;
//   }
//   printf("%s\n", buffer);
// }

int check_round(long double num, int accuracy) {
  int degree = 0;
  return ((int)(transformToExpForm(num, &degree) * pow(10, accuracy + 1)) %
          10) >= 5
             ? 1
             : 0;
}

void add_zeros_in_fpart(int count, char **num, long long *fpart_len) {
  // int count = 0;
  // printf("%d %Lf %lld\n", count, fpart, (long long)fpart);
  // while (fpart > 0 && (long long)fpart % 10 == 0) {
  //     count++;
  //     fpart /= 10;
  // }
  if (count > 0) {
    // Вычисляем текущую длину строки
    size_t original_length = s21_strlen(*num);

    // Переallocируем память для строки с учетом новых нулей
    char *new_num =
        s21_realloc(*num, original_length + 1, original_length + count + 1);
    if (new_num != NULL) {
      *num = new_num;  // Обновляем указатель на строку

      // Сдвигаем содержимое строки вправо вручную
      for (size_t i = original_length; i > 0; i--) {
        (*num)[i + count - 1] = (*num)[i - 1];
      }

      // Заполняем начало строки нулями
      for (int i = 0; i < count; i++) {
        (*num)[i] = '0';
      }

      // Добавляем завершающий ноль
      (*num)[original_length + count] = '\0';
    }
  }
  *fpart_len += count;
}

char *doubleToString_impl(long double num, int accuracy, int *flags,
                          char specificator) {
  int num_is_zero = (num == 0);
  if (check_round(num, accuracy)) num = round_to_precision(num, accuracy);
  long long int ipart = num, ipart_len = 0, fpart_len = 0;
  int accuracy_tmp = accuracy;
  long double fpart = num - ipart;

  char *res = intToString(ipart, flags);
  res = s21_realloc(res, s21_strlen(res) + 1, s21_strlen(res) + accuracy + 6);
  ipart_len = s21_strlen(res);
  if (specificator == 'g' || specificator == 'G') {
    accuracy = accuracy - ipart_len;
    if (num < 0) accuracy++;
  }
  if (accuracy > 0) {
    res[ipart_len] = '.';
    res[ipart_len + 1] = '\0';
    if (fpart < 0) fpart *= -1;
    long double fpart_orig = fpart;
    int i_tmp_part = (int)fpart_orig, count = 0;
    if (!num_is_zero) {
      while (i_tmp_part == 0) {
        count++;
        fpart_orig *= 10;
        i_tmp_part = (int)fpart_orig;
      }
    }
    fpart = fpart * pow(10, accuracy + 1);
    long fpart_int = (long)round(fpart);
    int last_num = fpart_int % 10;
    fpart_int /= 10;
    if (last_num > 4) fpart_int++;
    int flags_tmp = *flags;
    flags_tmp |= ITS_A_FLOAT;
    flags_tmp &= ~SHOW_SIGN;

    char *fpart_str = intToString(fpart_int, &flags_tmp);
    fpart_len = s21_strlen(fpart_str);
    if (!num_is_zero) add_zeros_in_fpart(count - 1, &fpart_str, &fpart_len);
    s21_strncat(res, fpart_str, fpart_len);

    free(fpart_str);
  } else if (accuracy < 0 && (specificator == 'g' || specificator == 'G')) {
    if (accuracy_tmp == 0) accuracy_tmp = 1;

    res = doubleToExpStr(ipart, abs(accuracy_tmp), flags, 0, specificator);
  } else if (accuracy == 0 && *flags & SHOW_NUMBER_SYSTEM) {
    res[ipart_len] = '.';
    res[ipart_len + 1] = '\0';
  }
  if (fpart_len < accuracy) {
    for (int i = fpart_len + ipart_len; i <= ipart_len + accuracy; i++) {
      res[i] = '0';
    }
  }
  return res;
}
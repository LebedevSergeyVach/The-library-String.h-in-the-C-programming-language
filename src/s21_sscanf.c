#include "s21_sscanf.h"

#include <stdio.h>

int ParseWidth(const char **form_p) {
  int flag = 0;
  if (**form_p != '*') {
    char *width = calloc(s21_strlen(*form_p), sizeof(char));
    int i = -1;
    for (; **form_p >= 48 && **form_p <= 57; (*form_p)++, i++)
      width[i + 1] = **form_p;
    for (int len = i; i >= 0; i--) flag += (width[i] - 48) * pow(10, len - i);
    if (flag == 0) flag = -10;
    free(width);
  } else {
    flag = '*';
    (*form_p)++;
  }
  return flag;
}

int ParseLenght(const char **form_p) {
  int flag = 0;
  if (**form_p == 'h')
    flag = 'h';
  else if (**form_p == 'l')
    flag = 'l';
  else if (**form_p == 'L')
    flag = 'L';
  if (flag != 0) (*form_p)++;
  return flag;
}

int ActivateSpecifier(const char **clone_str, const char **form_p, va_list argv,
                      int len_str, int lenght, int width) {
  if (**form_p != 'c' && **form_p != 'n')
    for (; s21_strchr(" \n\t\r\f", **clone_str) && **clone_str; (*clone_str)++);
  if (**form_p == 'c') {
    if (width != '*') {
      if (lenght == 'l')
        *va_arg(argv, s21_wchar_t *) = **clone_str;
      else
        *va_arg(argv, char *) = **clone_str;
    }
    (*clone_str)++;
  } else if (**form_p == 's')
    AddStr(clone_str, argv, width, lenght);
  else if (**form_p == 'd')
    AddSignedInt(clone_str, argv, width, lenght, 10.0);
  else if (**form_p == 'i')
    ActivateI(clone_str, argv, width, lenght);
  else if (**form_p == 'u')
    AddUnsignedInt(clone_str, argv, width, lenght, 10.0);
  else if (**form_p == 'x' || **form_p == 'X')
    AddUnsignedInt(clone_str, argv, width, lenght, 16.0);
  else if (**form_p == 'o')
    AddUnsignedInt(clone_str, argv, width, lenght, 8.0);
  else if (**form_p == 'p')
    AddUnsignedInt(clone_str, argv, width, 'p', 16.0);
  else if (s21_strchr("feEgG", **form_p))
    AddDouble(clone_str, argv, width, lenght);
  else if (**form_p == '%') {
    if (**clone_str == '%') {
      (*clone_str)++;
      (*form_p)++;
    } else
      for (; **clone_str != '\0'; (*clone_str)++);
  } else if (**form_p == 'n') {
    if (width != '*') *va_arg(argv, int *) = (len_str - s21_strlen(*clone_str));
  }
  for (; s21_strchr(" \n\t\r\f", **clone_str) && **clone_str; (*clone_str)++);
  if (s21_strchr("csdiuxXopfeEgG", **form_p) && width != '*') return 1;
  return 0;
}

void AddSignedInt(const char **clone_str, va_list argv, int width, int lenght,
                  double system) {
  long int number = CountingNumberODX(clone_str, width, system);
  if (width != '*') {
    if (lenght == 'h')
      *va_arg(argv, short int *) = (short int)(number);
    else if (lenght == 'l')
      *va_arg(argv, long int *) = number;
    else
      *va_arg(argv, int *) = (int)(number);
  }
}

void AddUnsignedInt(const char **clone_str, va_list argv, int width, int lenght,
                    double system) {
  long int number = CountingNumberODX(clone_str, width, system);
  if (width != '*') {
    if (lenght == 'p') {
      unsigned long int *p_void = va_arg(argv, void *);
      *p_void = number;
    } else if (lenght == 'h')
      *va_arg(argv, unsigned short int *) = (unsigned short int)(number);
    else if (lenght == 'l')
      *va_arg(argv, unsigned long int *) = (unsigned long int)(number);
    else
      *va_arg(argv, unsigned int *) = (unsigned int)(number);
  }
}

void AddDouble(const char **clone_str, va_list argv, int width, int lenght) {
  long double number = CountingFloat(clone_str, width);
  if (width != '*') {
    if (lenght == 'L')
      *va_arg(argv, long double *) = number;
    else if (lenght == 'l')
      *va_arg(argv, double *) = (double)(number);
    else
      *va_arg(argv, float *) = (float)(number);
  }
}

void AddStr(const char **clone_str, va_list argv, int width, int lenght) {
  if (width != '*') {
    if (lenght == 'l') {
      s21_wchar_t *strp = va_arg(argv, s21_wchar_t *);
      GetLongString(clone_str, width, &strp);
    } else {
      char *strp = va_arg(argv, char *);
      GetString(clone_str, width, &strp);
    }
  } else {
    if (lenght == 'l') {
      s21_wchar_t *fake_str = 0;
      GetLongString(clone_str, width, &fake_str);
    } else {
      char *fake_str = " ";
      GetString(clone_str, width, &fake_str);
    }
  }
}

void GetString(const char **clone_str, int width, char **strp) {
  if (*strp != S21_NULL) {
    int counter = 0;
    char *char_str =
        (char *)malloc(sizeof(char) * (s21_strlen(*clone_str) + 1));
    for (; **clone_str != ' ' && **clone_str != '\0' &&
           (counter < width || width <= -10);
         (*clone_str)++, counter++)
      char_str[counter] = **clone_str;
    char_str[counter] = '\0';
    if (width != '*') s21_strcpy(*strp, char_str);
    free(char_str);
  } else
    for (; **clone_str != '\0'; (*clone_str)++);
}

void GetLongString(const char **clone_str, int width, s21_wchar_t **strp) {
  if (*strp != S21_NULL) {
    int counter = 0;
    s21_wchar_t *int_str =
        (s21_wchar_t *)malloc(sizeof(s21_wchar_t) * s21_strlen(*clone_str));
    for (; **clone_str != ' ' && **clone_str != '\0' &&
           (counter < width || width <= -10);
         (*clone_str)++, counter++)
      int_str[counter] = **clone_str;
    if (width != '*') {
      for (int i = 0; i < counter; i++) (*strp)[i] = int_str[i];
      (*strp)[counter] = '\0';
    }
    free(int_str);
  } else
    for (; **clone_str != '\0'; (*clone_str)++);
}

long int CountingNumberODX(const char **clone_str, int width, double system) {
  long int number = 0;
  double counter = 0;
  int minus = 1, counter_bit = 0;
  CheckMinusAndPlus(clone_str, &width, &minus);
  if (**clone_str == '0' && (width > 0 || width <= -10)) {
    (*clone_str)++;
    counter_bit++;
    width--;
  }
  if ((**clone_str == 'x' || **clone_str == 'X') && system == 16.0 &&
      (width > 0 || width <= -10)) {
    (*clone_str)++;
    width--;
  }
  if (width <= -10)
    for (; **clone_str == '0'; (*clone_str)++, counter_bit++);
  if (counter_bit == 0 && !CheckingCondition(*clone_str, system))
    for (; **clone_str != '\0'; (*clone_str)++);
  else
    counter_bit = 0;
  for (; CheckingCondition(*clone_str, system) &&
         (counter_bit < width || width <= -10);
       (*clone_str)++, counter_bit++);
  if (counter_bit >= 17 && system == 16.0)
    number = -1;
  else if (counter_bit >= 23 && system == 8.0)
    number = -1;
  else if (counter_bit >= 20 && system == 10.0)
    number = -1;
  else {
    for ((*clone_str)--;
         CheckingCondition(*clone_str, system) && counter_bit != 0;
         (*clone_str)--, counter++, counter_bit--) {
      if ((**clone_str >= 48 && **clone_str <= 55))
        number += (long int)((**clone_str - 48) * pow(system, counter)) * minus;
      else if (**clone_str >= 48 && **clone_str <= 57)
        number += (long int)((**clone_str - 48) * pow(system, counter)) * minus;
      else if (**clone_str >= 97 && **clone_str <= 102)
        number += (long int)((**clone_str - 87) * pow(system, counter)) * minus;
      else if (**clone_str >= 65 && **clone_str <= 70)
        number += (long int)((**clone_str - 55) * pow(system, counter)) * minus;
    }
    for ((*clone_str)++; CheckingCondition(*clone_str, system) &&
                         (counter_bit < width || width <= -10);
         (*clone_str)++, counter_bit++);
  }
  return number;
}

void ActivateI(const char **clone_str, va_list argv, int width, int lenght) {
  int flag = 0;
  if (**clone_str == '-') {
    (*clone_str)++;
    flag = 1;
  }
  if (**clone_str == '0' && *(++(*clone_str)) != 'x' && **clone_str != 'X') {
    if (flag)
      (*clone_str) -= 2;
    else
      (*clone_str)--;
    AddUnsignedInt(clone_str, argv, width, lenght, 8.0);
  } else if (*(--(*clone_str)) == '0' &&
             (*(++(*clone_str)) == 'x' || **clone_str == 'X')) {
    if (flag)
      (*clone_str) -= 2;
    else
      (*clone_str)--;
    AddUnsignedInt(clone_str, argv, width, lenght, 16.0);
  } else {
    if (!flag) (*clone_str)++;
    AddSignedInt(clone_str, argv, width, lenght, 10.0);
  }
}

long double CountingFloat(const char **clone_str, int width) {
  long double number = 0;
  int minus = 1;
  CheckMinusAndPlus(clone_str, &width, &minus);
  if (width <= -10)
    for (; **clone_str == '0'; (*clone_str)++);
  if (!CheckINFAndNAN(clone_str, &number)) {
    char *str_number = calloc(s21_strlen(*clone_str), sizeof(char));
    int index = 0, num_point = 0;
    for (; ((**clone_str >= 48 && **clone_str <= 57) || **clone_str == 46) &&
           num_point <= 1 && (index < width || width <= -10);
         (*clone_str)++, index++) {
      str_number[index] = **clone_str;
      if (**clone_str == '.') {
        num_point += 1;
      }
    }
    if (width > 0) width -= index;
    char *notation = calloc(s21_strlen(*clone_str), sizeof(char));
    int indexn = 0, sign = 43;
    if ((**clone_str == 'e' || **clone_str == 'E') &&
        (width > 0 || width <= -10) && (*clone_str)++) {
      if (width > 0) width--;
      if ((width > 0 || width <= -10) &&
          (**clone_str == '-' || **clone_str == '+')) {
        sign = **clone_str;
        (*clone_str)++;
        if (width > 0) width--;
      }
      for (; **clone_str >= 48 && **clone_str <= 57 &&
             (indexn < width || width <= -10);
           (*clone_str)++, indexn++)
        notation[indexn] = **clone_str;
    }
    number = GetFloatNumber(str_number, notation, index, indexn, minus, sign);
    free(str_number);
    free(notation);
  }
  return number;
}

void CheckMinusAndPlus(const char **clone_str, int *width, int *minus) {
  if (**clone_str == '-') {
    (*clone_str)++;
    (*minus) = -1;
    (*width)--;
  } else if (**clone_str == '+') {
    (*clone_str)++;
    (*width)--;
  }
}

int CheckINFAndNAN(const char **clone_str, long double *number) {
  int flag = 0;
  if ((**clone_str < 48 || **clone_str > 57) && **clone_str != '.' &&
      !s21_strchr("nNiI", **clone_str))
    for (; **clone_str != '\0'; (*clone_str)++);
  else if (s21_strchr("nN", **clone_str) && **clone_str) {
    (*clone_str)++;
    if (s21_strchr("aA", **clone_str) && **clone_str) {
      (*clone_str)++;
      if (s21_strchr("nN", **clone_str) && **clone_str) {
        (*clone_str)++;
        *number = NAN;
        flag = 1;
      }
    }
    if (!isnan(*number))
      for (; **clone_str != '\0'; (*clone_str)++);
  } else if (s21_strchr("iI", **clone_str) && **clone_str) {
    (*clone_str)++;
    if (s21_strchr("nN", **clone_str) && **clone_str) {
      (*clone_str)++;
      if (s21_strchr("fF", **clone_str) && **clone_str) {
        (*clone_str)++;
        *number = INFINITY;
        flag = 1;
      }
    }
    if (isfinite(*number))
      for (; **clone_str != '\0'; (*clone_str)++);
  }
  return flag;
}

long double GetFloatNumber(const char *str_number, const char *notation,
                           int index, int indexn, int minus, int sign) {
  long double number = 0;
  for (int counter = 0; index > 0; index--, counter++) {
    if (str_number[index - 1] != '.')
      number +=
          (long double)(((str_number[index - 1] - 48) * pow(10.0, counter)) *
                        minus);
    else {
      number /= (long double)(pow(10.0, counter));
      counter = -1.0;
    }
  }
  int num_ch = 0;
  for (int counter = 0; indexn > 0; indexn--, counter++)
    num_ch += ((notation[indexn - 1] - 48) * pow(10.0, (counter)));
  if (num_ch != 0) {
    if (sign == '+') number *= (long double)(pow(10.0, (num_ch)));
    if (sign == '-') number /= (long double)(pow(10.0, (num_ch)));
  }
  return number;
}

int CheckingCondition(const char *clone_str, double system) {
  int ret = 0;
  if (*clone_str >= 48 && *clone_str <= 55 && system == 8.0)
    ret = 1;
  else if (*clone_str >= 48 && *clone_str <= 57 &&
           (system == 10.0 || system == 16.0))
    ret = 1;
  else if (*clone_str >= 97 && *clone_str <= 102 && system == 16.0)
    ret = 1;
  else if (*clone_str >= 65 && *clone_str <= 70 && system == 16.0)
    ret = 1;
  return ret;
}
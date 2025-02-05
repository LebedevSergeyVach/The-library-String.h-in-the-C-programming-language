#include "s21_sprintf.h"

#include <stdio.h>

void switch_sign_double(const int* flags, long double tmp, char* dest_p,
                        char* num, int width, size_t num_len) {
  if (*flags & FILL_WITH_ZEROS && (int)num_len < width) {
    int dp_len = s21_strlen(dest_p);
    if (dp_len < width && *flags & SHOW_SIGN) *num = '0';
    char* tmp_dest = dest_p;
    tmp_dest -= (width - dp_len);
    if (tmp < 0 && *flags & SHOW_SIGN)
      *tmp_dest = '-';
    else if (*flags & SHOW_SIGN)
      *tmp_dest = '+';
  }
}

void switch_sign_int(const int* flags, long tmp, char* dest_p, char* num,
                     int width, size_t num_len) {
  if (*flags & FILL_WITH_ZEROS && (int)num_len < width) {
    int dp_len = s21_strlen(dest_p);
    if (dp_len < width && *flags & SHOW_SIGN) {
      *num = '0';
    }
    char* tmp_dest = dest_p;
    tmp_dest -= (width - dp_len);
    if (tmp < 0 && *flags & SHOW_SIGN)
      *tmp_dest = '-';
    else if (*flags & SHOW_SIGN)
      *tmp_dest = '+';
  }
}

size_t int_cat(char* dest, va_list args, int width, int* flags) {
  long tmp = 0;
  if (*flags & l_LEN)
    tmp = va_arg(args, long);
  else
    tmp = va_arg(args, int);
  if (*flags & h_LEN) tmp = (short)tmp;
  if (tmp < 0 && *flags & ACC) {
    *flags |= SHOW_SIGN;
    char** tmp = &dest;
    mem_fill(&tmp, *flags, 1);
    width++;
  }
  char* num = intToString(tmp, flags);
  size_t num_len = s21_strlen(num);

  char* dest_p = move_p(dest, flags, width, num_len);
  dest_p[width + num_len] = '\0';
  switch_sign_int(flags, tmp, dest_p, num, width, num_len);
  if (*flags & DOC_R) {
    s21_memcpy(dest_p, num, num_len);
    dest_p[width] = '\0';
  } else
    s21_strncpy(dest_p, num, num_len);
  free(num);
  return s21_strlen(dest);
}

size_t unsigned_cat(char* dest, va_list args, int width, int* flags) {
  unsigned long tmp = 0;
  if (*flags & l_LEN)
    tmp = va_arg(args, unsigned long);
  else
    tmp = va_arg(args, unsigned);
  if (*flags & h_LEN) tmp = (unsigned short)tmp;
  int tmp_show_sign = 0;
  if (*flags & SHOW_SIGN) {
    tmp_show_sign = 1;
    *flags ^= SHOW_SIGN;
  }
  char* num = intToString(tmp, flags);
  if (tmp_show_sign) *flags |= SHOW_SIGN;
  size_t num_len = s21_strlen(num);
  char* dest_p = move_p(dest, flags, width, num_len);
  if (*flags & DOC_R) {
    s21_memcpy(dest_p, num, num_len);
    dest_p[width] = '\0';
  } else
    s21_strncpy(dest_p, num, num_len);
  free(num);
  return s21_strlen(dest);
}

char* move_p(char* dest, const int* flags, int width, int len) {
  if (*flags & DOC_R) {
    dest -= width;
    dest[width] = '\0';
  } else if (*flags & PREC) {
    if (len > width) {
      dest -= width;
      dest[width] = '\0';
    } else {
      dest -= len;
      dest[len] = '\0';
    }
  }
  return dest;
}

size_t charp_cat(char* dest, va_list args, int width, int* flags, int acc) {
  char* src = S21_NULL;
  int must_free = 0;
  if (*flags & l_LEN)
    src = wcharp_to_charp(args);
  else
    src = va_arg(args, char*);
  if (!src) {
    src = calloc(7, sizeof(char));
    s21_sprintf(src, "%s", "(null)");
    must_free = 1;
  }
  size_t len_src = 0;
  len_src = s21_strlen(src);
  if (*flags & ACC) len_src = acc;
  char* dest_p = move_p(dest, flags, width, len_src);
  if (*flags & DOC_R) {
    s21_memcpy(dest_p, src, len_src);
    dest_p[width] = '\0';
  } else
    s21_strncpy(dest_p, src, len_src);
  if (*flags & l_LEN || must_free) free(src);
  size_t result = s21_strlen(dest_p);
  return result;
}

char* wcharp_to_charp(va_list args) {
  s21_wchar_t* src = va_arg(args, s21_wchar_t*);
  int len = 0;
  for (s21_wchar_t* tmp = src; *tmp != '\0'; tmp++, len++);
  char* tmp_res = calloc((len + 1), sizeof(char));
  tmp_res[len] = '\0';
  for (char* tmp = tmp_res; *src != '\0'; src++, tmp++) {
    *tmp = (char)*src;
  }
  char* res = tmp_res;
  return res;
}

size_t float_cat(char* dest, va_list args, int* flags, int accuracy, int width,
                 char specificator) {
  long double tmp = 0;
  if (*flags & L_LEN)
    tmp = va_arg(args, long double);
  else
    tmp = (long double)va_arg(args, double);
  char* num = doubleToStringWithAccuracy(tmp, accuracy, flags, specificator);
  size_t num_len = s21_strlen(num);
  char* dest_p = move_p(dest, flags, width, num_len);
  switch_sign_double(flags, tmp, dest_p, num, width, num_len);
  if (*flags & DOC_R) {
    s21_memcpy(dest_p, num, num_len);
    dest_p[width] = '\0';
  } else
    s21_strncpy(dest_p, num, num_len);
  free(num);
  return s21_strlen(dest);
}

size_t cat_number_system(int registry, char** dst, size_t len) {
  char* num_sys = add_number_system2(registry);
  size_t len_num_sys = s21_strlen(num_sys);
  num_sys = s21_realloc(num_sys, len_num_sys, len + len_num_sys + 1);
  s21_strncat(num_sys, *dst, len);
  *dst = s21_realloc(*dst, len, len + len_num_sys + 1);
  s21_strcpy(*dst, num_sys);
  len = s21_strlen(*dst);
  free(num_sys);
  return len;
}

size_t hex_cat(char* dest, va_list args, int width, int* flags, int registry) {
  unsigned long tmp = 0;
  if (*flags & l_LEN)
    tmp = va_arg(args, unsigned long);
  else
    tmp = va_arg(args, unsigned);
  if (*flags & h_LEN) tmp = (unsigned short)tmp;

  char* num = intToHexStr(tmp, registry, *flags);
  size_t num_len = s21_strlen(num);

  char* dest_p = move_p(dest, flags, width, num_len);
  if (*flags & SHOW_NUMBER_SYSTEM && *flags & FILL_WITH_ZEROS &&
      num_len > (size_t)width) {
    num_len = cat_number_system(registry, &num, num_len);
  }
  if (*flags & DOC_R) {
    int end = 0;
    s21_memcpy(dest_p, num, num_len);
    if (*flags & PREC)
      end = width;
    else
      end = num_len;
    dest_p[end] = '\0';
    dest = dest_p;
  } else {
    if (num_len < (size_t)width && *flags & SHOW_NUMBER_SYSTEM) {
      char sys_zero[3] = {'0', 'x', '\0'};
      if (registry == 1) s21_strncpy(sys_zero, "0X", 2);
      s21_memcpy(dest_p - (width - 1), sys_zero, 2);
    }
    // dest_p -= width - 1;
    s21_strncpy(dest_p, num, num_len);
  }
  free(num);
  return s21_strlen(dest);
}

size_t pointer_cat(char** dest, va_list args, int width, int* flags,
                   int registry) {
  void* void_p = va_arg(args, void*);
  unsigned long void_p_num = (unsigned long)void_p;
  char* num = S21_NULL;
  if (void_p) {
    // add_number_system(flags, dest, 'p');
    num = intToHexStr(void_p_num, registry, *flags);
  } else {
    num = calloc(6, sizeof(char));
    s21_sprintf(num, "%s", "(nil)");
  }
  size_t num_len = s21_strlen(num);
  char* dest_p = move_p(*dest, flags, width, num_len);
  if (*flags & DOC_R) {
    s21_memcpy(dest_p, num, num_len);
    dest_p[width] = '\0';
  } else
    s21_strncpy(dest_p, num, num_len);
  free(num);

  return s21_strlen(*dest);
}

size_t oct_cat(char* dest, va_list args, int width, int* flags) {
  unsigned long tmp = 0;
  if (*flags & l_LEN)
    tmp = va_arg(args, unsigned long);
  else
    tmp = va_arg(args, unsigned);
  if (*flags & h_LEN) tmp = (unsigned short)tmp;

  char* num = intToOctStr(tmp, *flags);
  size_t num_len = s21_strlen(num);
  char* dest_p = move_p(dest, flags, width, num_len);
  if (*flags & SHOW_NUMBER_SYSTEM && *flags & FILL_WITH_ZEROS &&
      num_len > (size_t)width) {
    num_len = cat_number_system(3, &num, num_len);
  }
  if (*flags & DOC_R) {
    int end = 0;
    s21_memcpy(dest_p, num, num_len);
    if (*flags & PREC)
      end = width;
    else
      end = num_len;
    dest_p[end] = '\0';
    dest = dest_p;
    // s21_memcpy(dest_p, num, num_len);
    // dest_p[width] = '\0';
  } else {
    if (num_len < (size_t)width && *flags & SHOW_NUMBER_SYSTEM) {
      char sys_zero[2] = {'0', '\0'};
      s21_memcpy(dest_p - (width), sys_zero, 1);
    }
    s21_strncpy(dest_p, num, num_len);
  }
  free(num);
  return s21_strlen(dest);
}

size_t exp_cat(char* dest, va_list args, int width, int* flags, int registry,
               int accuracy, char specificator) {
  long double tmp = 0;
  if (*flags & L_LEN)
    tmp = va_arg(args, long double);
  else
    tmp = (long double)va_arg(args, double);

  char* num = doubleToExpStr(tmp, accuracy, flags, registry, specificator);
  size_t num_len = s21_strlen(num);
  char* dest_p = move_p(dest, flags, width, num_len);
  switch_sign_double(flags, tmp, dest_p, num, width, num_len);
  if (*flags & DOC_R) {
    s21_memcpy(dest_p, num, num_len);
    dest_p[width] = '\0';
  } else
    s21_strncpy(dest_p, num, num_len);
  free(num);
  return s21_strlen(dest);
}

void fix_accuracy(char* num, int is_exp_form) {
  char* tmp_num = &num[s21_strlen(num) - 1];
  if (!is_exp_form) {
    for (; *tmp_num == '0'; tmp_num--) *tmp_num = '\0';
    if (*tmp_num == '.') *tmp_num = '\0';
  } else {
    char* exp_part = tmp_num - 3;
    tmp_num -= 4;
    for (; *tmp_num == '0'; tmp_num--) *tmp_num = '\0';
    tmp_num++;
    for (; *exp_part != '\0'; exp_part++, tmp_num++) *tmp_num = *exp_part;
    *tmp_num = '\0';
  }
}

size_t g_cat(char* dest, va_list args, int width, int* flags, int registry,
             int accuracy, char specificator) {
  char* num = S21_NULL;
  long double arg = 0;
  if (*flags & L_LEN)
    arg = va_arg(args, long double);
  else
    arg = (long double)va_arg(args, double);

  if (((arg >= 1000000 || arg <= 0.0001) && arg > 0) ||
      ((arg < -999999 || arg >= -0.0001) && arg < 0)) {
    num = doubleToExpStr(arg, accuracy, flags, registry, specificator);
    fix_accuracy(num, 1);
  } else {
    num = doubleToStringWithAccuracy(arg, accuracy, flags, specificator);
    fix_accuracy(num, 0);
  }
  size_t num_len = s21_strlen(num);
  char* dest_p = move_p(dest, flags, width, num_len);
  switch_sign_double(flags, arg, dest_p, num, width, num_len);
  if (*flags & DOC_R) {
    s21_memcpy(dest_p, num, num_len);
    dest_p[width] = '\0';
  } else
    s21_strncpy(dest_p, num, num_len);
  free(num);
  return s21_strlen(dest);
}

int parse_width(int* flags, const char* form_p, const char* prec_p, char** p,
                va_list argl, char parse_symbol) {
  *flags |= PREC;
  char width_p[s21_strlen(form_p) + 1];
  s21_strcpy(width_p, prec_p);
  int width = 0;
  if (parse_symbol == '*')
    width = va_arg(argl, int);
  else
    width = ParseWidth_sprintf(prec_p);
  mem_fill(&p, *flags, width);
  return width;
}

void mem_fill(char*** p, int flags, int width) {
  if (flags & FILL_WITH_ZEROS)
    s21_memset(**p, '0', width);
  else
    s21_memset(**p, ' ', width);
  **p = (char*)(**p + width);
}

// int parse_width2(int* flags, const char* form_p, const char* prec_p, va_list
// argl){

// }

void parse_flags(int* flags, const char** prec_p, const char** form_p) {
  ;
  *prec_p = *prec_p + 1;
  while (**prec_p == '-' || **prec_p == '+' || **prec_p == ' ' ||
         **prec_p == '#' || **prec_p == '0') {
    if (**prec_p == '-') *flags |= DOC_R;
    if (**prec_p == '+') *flags |= SHOW_SIGN;
    if (**prec_p == ' ' && !(*flags & SHOW_SIGN)) *flags |= SIGN_PLACE;
    if (**prec_p == '#') *flags |= SHOW_NUMBER_SYSTEM;
    if (**prec_p == '0') *flags |= FILL_WITH_ZEROS;
    *form_p = *form_p + 1;
    *prec_p = *prec_p + 1;
  }
  if (*flags & DOC_R) *flags &= ~FILL_WITH_ZEROS;
}

// void parse_accuracy(int* accuracy, va_list argl, const char** prec_p,
//                     const char** form_p) {
//   if (*(*prec_p + 1) == '.' || **(prec_p) == '.') {
//     if (*(*prec_p + 1) == '.') *prec_p = *prec_p + 1;
//     *prec_p = *prec_p + 1;
//     if (**(prec_p) == '*') {
//       *accuracy = va_arg(argl, int);
//       if (*(*prec_p - 2) == '%') *form_p = *form_p + 1;
//     } else {
//       if (**(prec_p) == '.') *prec_p = *prec_p + 1;
//       *accuracy = **prec_p - '0';
//       if (*(*prec_p - 2) == '%') *form_p = *form_p + 1;
//     }
//     *form_p = *form_p + 1;
//     ;
//   }
// }

void parse_accuracy2(const char** form_p, char** p, va_list argl, int* accuracy,
                     int* flags, int* width) {
  *flags |= ACC;
  if (**form_p == '*')
    *accuracy = va_arg(argl, int);
  else {
    if (**form_p >= '0' && **form_p <= '9') {
      *accuracy = ParseWidth_sprintf(*form_p);
    }
  }
  if (**form_p >= '0' && **form_p <= '9')
    if (*(*form_p + 1) == 'd') {
      *flags |= FILL_WITH_ZEROS;
      if (!(*flags & PREC)) {
        *flags |= PREC;
      } else {
        *p = (char*)*p - *width;
      }
      *width = *accuracy;
      mem_fill(&p, *flags, *width);
      *form_p = *form_p + (width_check(*form_p) - 1);
    }
}

int parse_length(const char** form_p, int* flags) {
  int move_status = 0;
  if (*(*form_p + 1) == 'h' || *(*form_p + 1) == 'l' || *(*form_p + 1) == 'L') {
    if (*(*form_p + 1) == 'h')
      *flags |= h_LEN;
    else if (*(*form_p + 1) == 'l')
      *flags |= l_LEN;
    else if (*(*form_p + 1) == 'L')
      *flags |= L_LEN;
    move_status = 1;
  }
  return move_status;
}

char* add_number_system2(int registry) {
  char* result = S21_NULL;
  if (registry == 0 || registry == 1) {
    result = malloc(3);
    if (registry == 0)
      s21_strncpy(result, "0x", 2);
    else if (registry == 1)
      s21_strncpy(result, "0X", 2);
  } else {
    result = malloc(2);
    s21_strncpy(result, "0", 1);
  }
  return result;
}

void parse_specif(char** dest_p, const char* form_p, va_list argl, int width,
                  int* flags, int accuracy, int* chars_count) {
  int num_len = 0, tmp_flags = *flags;
  switch (*form_p) {
    case '%':
      **dest_p = '%';
      (void)(*dest_p++);
      **dest_p = '\0';
      (void)(*dest_p++);
      break;
    case 'd':
      num_len = int_cat(*dest_p, argl, width, flags);
      break;
    case 's':
      num_len = charp_cat(*dest_p, argl, width, flags, accuracy);
      if ((*flags & ACC && *flags & PREC) || *flags & PREC)
        *dest_p = (char*)*dest_p - num_len;
      break;
    case 'f':
      num_len = float_cat(*dest_p, argl, flags, accuracy, width, 'f');
      break;
    case 'c':
      if (*flags & l_LEN) {
        char tmp = va_arg(argl, int);
        s21_strncpy(*dest_p, &tmp, 1);
      } else {
        char tmp = va_arg(argl, int);
        s21_strncpy(*dest_p, &tmp, 1);
      }
      if (!(**dest_p)) (*chars_count)++;
      (void)(*dest_p++);
      (void)(*dest_p++);
      break;
    case 'u':
      num_len = unsigned_cat(*dest_p, argl, width, flags);
      break;
    case 'x':
      num_len = hex_cat(*dest_p, argl, width, flags, 0);
      if (*flags & DOC_R && *flags & PREC) *dest_p = (char*)*dest_p - num_len;
      break;
    case 'X':
      num_len = hex_cat(*dest_p, argl, width, flags, 1);
      if (*flags & DOC_R && *flags & PREC) *dest_p = (char*)*dest_p - num_len;
      break;
    case 'p':
      *flags |= SHOW_NUMBER_SYSTEM;
      num_len = pointer_cat(dest_p, argl, width, flags, 0);
      *flags = tmp_flags;
      break;
    case 'o':
      // add_number_system(flags, dest_p, 'o');
      num_len = oct_cat(*dest_p, argl, width, flags);
      if (*flags & DOC_R && *flags & PREC) *dest_p = (char*)*dest_p - num_len;
      break;
    case 'e':
      num_len = exp_cat(*dest_p, argl, width, flags, 0, accuracy, 'e');
      break;
    case 'E':
      num_len = exp_cat(*dest_p, argl, width, flags, 1, accuracy, 'E');
      break;
    case 'g':
      num_len = g_cat(*dest_p, argl, width, flags, 0, accuracy, 'g');
      break;
    case 'G':

      *flags ^= SHOW_NUMBER_SYSTEM;
      num_len = g_cat(*dest_p, argl, width, flags, 1, accuracy, 'G');
      *flags = tmp_flags;
      break;
    default:
      break;
  }
  *dest_p = (char*)(*dest_p + (num_len - 1));
}

int width_check(const char* form_p) {
  int result = 0;
  if (*form_p == '*')
    result = 1;
  else {
    while (*form_p >= 48 && *form_p <= 48 + 9) {
      result++;
      form_p++;
    }
  }
  return result;
}

int ParseWidth_sprintf(const char* form_p) {
  int flag = 0;
  char* width = calloc(s21_strlen(form_p), sizeof(char));
  for (int i = 0; *form_p >= 48 && *form_p <= 57; (form_p)++, i++)
    width[i] = *form_p;
  for (int i = s21_strlen(width) - 1; i >= 0; i--)
    flag += (width[i] - 48) * pow(10, s21_strlen(width) - (i + 1));
  free(width);
  return flag;
}

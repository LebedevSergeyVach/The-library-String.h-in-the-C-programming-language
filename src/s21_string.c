#include "s21_string.h"

#include <stdio.h>
/*поиск первого вхождения с символа в первых n байтах строки
на которую указывает str */

void *s21_memchr(const void *str, int c, size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  void *res = S21_NULL;
  char done = 0;
  for (; 0 < n; n--, ptr++) {
    if (*ptr == (unsigned char)c && !done) {
      res = (void *)ptr;
      done = 1;
    }
  }
  return res;
}

// void* s21_memchr(const void* str, int c, size_t n){
//     const unsigned char* ptr = str;
//     for (; 0 < n; n--, ptr++){
//         if (*ptr == (unsigned char)c) return (void*) ptr;
//     }
//     return S21_NULL;
// }

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  const unsigned char *ptr1 = (const unsigned char *)str1;
  const unsigned char *ptr2 = (const unsigned char *)str2;
  int result = 0;
  char done = 0;
  for (; 0 < n; n--, ptr1++, ptr2++) {
    if (*ptr1 != *ptr2 && !done) {
      result = *ptr1 - *ptr2;
      done = 1;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {
  unsigned char *result = (unsigned char *)dest;
  unsigned char *ptrd = result;
  const unsigned char *ptrs = (const unsigned char *)src;
  for (; 0 < n; n--, ptrd++, ptrs++) {
    *ptrd = *ptrs;
  }
  return (void *)result;
}

void *s21_memset(void *str, int c, size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (; 0 < n; n--, ptr++) {
    *ptr = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, char *src, size_t n) {
  char *ptrd = dest;
  while (*ptrd != '\0') ptrd++;
  while (0 < n) {
    *ptrd++ = *src++;
    n--;
  }
  *ptrd = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  unsigned char *ptr = (unsigned char *)str;
  unsigned char f = (unsigned char)c;
  char nul = 1;
  while (nul && *ptr != f) {
    if (*ptr++ == '\0') {
      nul = 0;
      ptr = S21_NULL;
    }
  }
  return (char *)ptr;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int result = 0;
  int flag = 1;
  for (size_t i = 0; (i < n && flag) && (str1[i] || str2[i]); i++) {
    if (str1[i] != str2[i]) {
      result = (unsigned char)str1[i] - (unsigned char)str2[i];
      flag = 0;
    }
  }
  return result;
}

size_t s21_strcspn(const char *s, const char *reject) {
  int is_found = 0;
  const char *strp = s, *rejp;
  for (; *strp != '\0' && !is_found; strp++) {
    for (rejp = reject; *rejp != '\0' && !is_found; rejp++) {
      if (*strp == *rejp) {
        is_found = 1;
        strp--;
      }
    }
  }

  return strp - s;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  const char *sp = src;
  char *dp = dest;
  for (; n > 0; n--) {
    *dest++ = *sp++;
  }
  *dest++ = '\0';
  return dp;
}

size_t s21_strlen(const char *str) {
  size_t counter = 0;
  for (; str[counter] != '\0'; counter++);
  return counter;
}

char *s21_strerror(int errnum) {
  char *res = S21_NULL;
  static char res1[256] = {0};
  if (errnum > ERRORS_NUM || errnum < 0) {
    for (int i = 0; i < 256; i++) res1[i] = 0;
#ifdef __linux__
    s21_sprintf(res1, "Unknown error %d", errnum);
#else
    s21_sprintf(res1, "Unknown error: %d", errnum);
#endif
    res = res1;
  } else {
    res = (char *)ERRORS[errnum];
  }
  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int flag = 1;
  for (int i = 0; str1[i] && flag; i++) {
    for (int j = 0; str2[j] && flag; j++) {
      if (str1[i] == str2[j]) {
        result = (char *)str1 + i;
        flag = 0;
      }
    }
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;

  for (; *str; str++) {
    if (*str == c) result = (char *)str;
  }
  if (*str == c) result = (char *)str;
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  int flag = 1;
  for (int i = 0; haystack[i] && (flag == 1 || flag == 0); i++) {
    flag = 1;
    for (int j = 0; needle[j] && flag; j++) {
      if (haystack[i + j] != '\0' && (haystack[i + j] != needle[j])) flag = 0;
    }
    if (flag == 1) {
      result = (char *)haystack + (i);
      flag = 2;
    }
  }
  return result;
}

char *s21_strtok(char *string, const char *delim) {
  static char *last = S21_NULL;
  char *st = S21_NULL;
  if (string) {
    last = string;
  }
  if (last != 0 && *last != 0) {
    char *c = last;
    while (s21_strchr(delim, *c)) {
      ++c;
    }
    if (*c != 0) {
      st = c;
      while (*c && (s21_strchr(delim, *c) == 0)) {
        ++c;
      }
      if (*c == 0) {
        last = c;
      } else {
        *c = 0;
        last = c + 1;
      }
    }
  }
  return st;
}

char *s21_strcpy(char *destptr, const char *srcptr) {
  int i = 0;
  for (; srcptr[i] != '\0'; i++) {
    destptr[i] = srcptr[i];
  }
  destptr[i] = '\0';
  return destptr;
}

int s21_sprintf(char *dest, const char *dest_format, ...) {
  va_list argl;
  va_start(argl, dest_format);
  char *p = dest;
  int chars_count = 0;
  for (const char *form_p = dest_format; *form_p != '\0'; form_p++, p++) {
    int flags = 0, accuracy = 6, width = 0;
    ;
    *p = 0;
    if (*form_p == '%') {
      const char *prec_p = form_p;
      parse_flags(&flags, &prec_p, &form_p);

      if (((*prec_p >= '1' && *prec_p <= '9') || *prec_p == '*') &&
          *(prec_p - 1) != '.') {
        width = parse_width(&flags, form_p, prec_p, &p, argl, *prec_p);
        if (*(prec_p + width_check(prec_p)) == '.') {
          form_p += (width_check(prec_p) + 2);
          prec_p += (width_check(prec_p));
        } else {
          form_p += (width_check(prec_p));
          prec_p += (width_check(prec_p));
        }
      } else if (*prec_p == '.')
        form_p += 2;
      if (*prec_p == '%') {
        *p = *prec_p;
        p++;
        *p = '\0';
        p--;
        form_p++;
      } else {
        if (*prec_p == '.')
          parse_accuracy2(&form_p, &p, argl, &accuracy, &flags, &width);
        if (parse_length(&form_p, &flags)) form_p++;
        parse_specif(&p, ++form_p, argl, width, &flags, accuracy, &chars_count);
        flags = 0;
      }
    } else
      // *p = *form_p;
      s21_strncpy(p, form_p, 1);
  }
  int counter = s21_strlen(dest) + chars_count;
  va_end(argl);
  return counter;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list argv;
  va_start(argv, format);
  const char *clone_str = str;
  int len_str = s21_strlen(clone_str), num_activate_spec = 0;
  for (const char *form_p = format; *form_p != '\0'; form_p++) {
    if (*form_p == '%') {
      form_p++;
      num_activate_spec +=
          ActivateSpecifier(&clone_str, &form_p, argv, len_str,
                            ParseLenght(&form_p), ParseWidth(&form_p));
    }
  }
  va_end(argv);
  return num_activate_spec;
}
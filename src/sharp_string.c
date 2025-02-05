#include "sharp_string.h"

#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = S21_NULL;
  if (str != S21_NULL) {
    res = calloc(s21_strlen(str) + 1, sizeof(char));
    for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] >= 'a' && str[i] <= 'z')
        res[i] = str[i] - 32;
      else
        res[i] = str[i];
    }
  }
  return (void *)res;
}

void *s21_to_lower(const char *str) {
  char *res = S21_NULL;
  if (str != S21_NULL) {
    res = calloc(s21_strlen(str) + 1, sizeof(char));
    for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z')
        res[i] = str[i] + 32;
      else
        res[i] = str[i];
    }
  }
  return (void *)res;
}

void *s21_realloc(void *ptr, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(ptr);
    return S21_NULL;
  }
  void *new_pointer = calloc(new_size, 1);
  if (new_pointer == S21_NULL) {
    return S21_NULL;
  }
  s21_memcpy(new_pointer, ptr, old_size < new_size ? old_size : new_size);
  free(ptr);
  return new_pointer;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *srcp = S21_NULL;
  if (src != S21_NULL && str != S21_NULL && start_index <= s21_strlen(src)) {
    size_t full_len = s21_strlen(str) + s21_strlen(src) + 1;
    srcp = calloc(full_len, sizeof(char));
    for (size_t i = 0, p = 0; i < full_len; i++, p++) {
      if (i == start_index) {
        for (size_t j = 0, str_len = s21_strlen(str); j < str_len; j++, i++) {
          srcp[i] = str[j];
        }
      }
      srcp[i] = src[p];
    }
  }
  return (void *)srcp;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;
  if (src != S21_NULL && trim_chars != S21_NULL) {
    size_t src_len = s21_strlen(src), trim_len = s21_strlen(trim_chars),
           start = 0, end = 0, stop = 1;
    for (size_t i = 0; i < src_len && stop; i++) {
      stop = 1;
      for (size_t j = 0; j < trim_len && stop; j++) {
        if (src[i] == trim_chars[j]) {
          start++;
          stop = 2;
        }
      }
      if (stop != 2) stop = 0;
    }
    for (size_t i = src_len - 1, stop = 1; i >= start && stop; i--) {
      stop = 1;
      for (size_t j = 0; j < trim_len && stop; j++) {
        if (src[i] == trim_chars[j]) {
          end++;
          stop = 2;
        }
      }
      if (stop != 2) stop = 0;
    }
    res = calloc(src_len - start - end + 2, sizeof(char));
    for (size_t i = start, j = 0; i < src_len - end; i++, j++) res[j] = src[i];
  }
  return res;
}
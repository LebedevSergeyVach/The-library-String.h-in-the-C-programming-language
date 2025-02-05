#pragma once
#include <stddef.h>

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_realloc(void *ptr, size_t old_size, size_t new_size);
void *s21_trim(const char *src, const char *trim_chars);
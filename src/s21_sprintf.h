#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
// #include <wchar.h>

#include "converter.h"
#include "s21_string.h"

enum SPRF_FLAGS {
  PREC = 1 << 1,
  WIDTH = 1 << 2,
  DOC_R = 1 << 3,
  SHOW_SIGN = 1 << 4,
  SIGN_PLACE = 1 << 5,
  SHOW_NUMBER_SYSTEM = 1 << 6,
  FILL_WITH_ZEROS = 1 << 7,
  ITS_A_FLOAT = 1 << 8,
  h_LEN = 1 << 9,
  l_LEN = 1 << 10,
  L_LEN = 1 << 11,
  ACC = 1 << 12,
};

char* add_number_system2(int registry);
int width_check(const char* form_p);
size_t int_cat(char* dest, va_list args, int prec, int* flags);
void parse_specif(char** dest_p, const char* form_p, va_list argl, int prec,
                  int* flags, int accuracy, int* chars_count);
size_t charp_cat(char* dest, va_list args, int width, int* flags, int acc);
char* move_p(char* dest, const int* flags, int width, int len);
int parse_width(int* flags, const char* form_p, const char* prec_p, char** p,
                va_list argl, char parse_symbol);
void parse_flags(int* flags, const char** prec_p, const char** form_p);
void parse_accuracy(int* accuracy, va_list argl, const char** prec_p,
                    const char** form_p);
int parse_length(const char**, int*);
int ParseWidth_sprintf(const char* form_p);
char* wcharp_to_charp(va_list args);
void parse_accuracy2(const char** form_p, char** p, va_list argl, int* accuracy,
                     int* flags, int* width);
void mem_fill(char*** p, int flags, int width);
void fix_accuracy(char* num, int is_exp_form);
size_t cat_number_system(int registry, char** dst, size_t len);

#endif
#pragma once

typedef __WCHAR_TYPE__ s21_wchar_t;
#include "s21_string.h"

int ParseWidth(const char **form_p);
int ParseLenght(const char **form_p);
int ActivateSpecifier(const char **clone_str, const char **form_p, va_list argv,
                      int len_str, int lenght, int width);
void AddSignedInt(const char **clone_str, va_list argv, int width,
                  int lengh_flag, double system);
void AddUnsignedInt(const char **clone_str, va_list argv, int width,
                    int lengh_flag, double system);
void AddDouble(const char **clone_str, va_list argv, int width, int lenght);
void AddStr(const char **clone_str, va_list argv, int width, int lenght);
void GetString(const char **clone_str, int width, char **strp);
void GetLongString(const char **clone_str, int width, s21_wchar_t **strp);
long int CountingNumberODX(const char **clone_str, int width, double system);
void ActivateI(const char **clone_str, va_list argv, int width, int lenght);
long double CountingFloat(const char **clone_str, int width);
void CheckMinusAndPlus(const char **clone_str, int *width, int *minus);
int CheckINFAndNAN(const char **clone_str, long double *number);
long double GetFloatNumber(const char *str_number, const char *notation,
                           int index, int indexn, int minus, int sign);
int CheckingCondition(const char *clone_str, double system);
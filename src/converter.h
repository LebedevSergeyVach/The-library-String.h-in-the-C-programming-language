#pragma once

char* intToString(long long number, const int* flags);

#define doubleToString(num, flags) doubleToString_impl(num, 6, flags)
#define doubleToStringWithAccuracy(num, accuracy, flags, specificator) \
  doubleToString_impl(num, accuracy, flags, specificator)
char* doubleToString_impl(long double num, int accuracy, int* flags,
                          char specificator);
char* intToHexStr(unsigned long num, int registry, int flags);
char* intToOctStr(long long num, int flags);
char* doubleToExpStr(long double num, int accuracy, int* flags, int registry,
                     char specificator);

#ifndef UNIT_TEST_MAIN_H
#define UNIT_TEST_MAIN_H

#include "include_define.h"
#include "unit_tests_s21_sprintf.h"
#include "unit_tests_s21_sscanf.h"
#include "unit_tests_s21_string.h"

/**
 * @brief Главная функция для запуска unit-тестов.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return int Код завершения программы:
 *             - EXIT_SUCCESS, если все тесты прошли успешно.
 *             - EXIT_FAILURE, если хотя бы один тест не прошел.
 *
 * @details
 * Программа поддерживает следующие флаги:
 * - -string: Запуск тестов для библиотеки s21_string.
 * - -sprintf: Запуск тестов для библиотеки s21_sprintf.
 * - -sscanf: Запуск тестов для библиотеки s21_sscanf.
 * Если флаги не указаны, запускаются все тесты.
 */
int main(int argc, char *argv[]);

#endif

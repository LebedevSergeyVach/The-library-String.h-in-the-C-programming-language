#include "unit_tests_main.h"

int main(int argc, char *argv[]) {
  int number_failed = 0;
  Suite *s = S21_NULL;
  SRunner *sr = S21_NULL;

  int run_string = 0;
  int run_sprintf = 0;
  int run_sscanf = 0;

  if (argc == 1) {
    run_string = 1;
    run_sprintf = 1;
    run_sscanf = 1;
  } else {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-string") == 0) {
        run_string = 1;
      } else if (strcmp(argv[i], "-sprintf") == 0) {
        run_sprintf = 1;
      } else if (strcmp(argv[i], "-sscanf") == 0) {
        run_sscanf = 1;
      } else {
        printf("Неизвестный флаг: %s\n", argv[i]);
        printf("Используйте флаги: -string, -sprintf, -sscanf\n");

        return EXIT_FAILURE;
      }
    }
  }

  sr = srunner_create(S21_NULL);

  if (run_string) {
    s = s21_string_suite();
    srunner_add_suite(sr, s);
  }
  if (run_sprintf) {
    s = s21_sprintf_suite();
    srunner_add_suite(sr, s);
  }
  if (run_sscanf) {
    s = s21_sscanf_suite();
    srunner_add_suite(sr, s);
  }

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

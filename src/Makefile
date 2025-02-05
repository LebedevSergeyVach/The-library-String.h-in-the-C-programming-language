TARGET=s21_string.a
CC=gcc
DFLAGS=-o 0 -g3
CFLAGS=-Wall -Wextra -std=c11 # -Werror
# -Wall -Wextra -std=c11 -Werror
OS=$(shell uname)
TEST_TARGET=tests
EXECUTABLE=s21_string

TEST_DIR=tests
SRC_DIR=
RUN_DIR=run
BUILD_DIR=obj
BIN_DIR=bin

MODULES=$(filter-out main.c, $(wildcard *.c))
OBJECTS=$(MODULES:%.c=%.o)
MODULES_TEST=$(shell find "$(TEST_DIR)" -name "*.c")
OBJECTS_TEST=$(MODULES_TEST:%.c=%.o)
MODULES_RUN = $(wildcard *.c)
OBJECTS_RUN = $(MODULES_RUN:%.c=%.o)

IS_UBUNTU = $(shell grep -i 'ubuntu' /etc/os-release 2>/dev/null)

ifeq ($(OS), Linux)
    ifneq ($(IS_UBUNTU),)
        LDLIBS = -lcheck -lsubunit -lm
    else
        LDLIBS = -lcheck -lm
    endif
else
    LDLIBS = -lcheck -lm
endif

.PHONY: all run build rebuild clean test gcov_report style_check valgrind_check $(TARGET)

all: clean $(TARGET) test gcov_report

debug: clean
	$(CC)  $(DFLAGS) *.c -lm -o $@

vg_debug: debug
	valgrind --track-origins=yes --leak-check=full ./debug

build: $(TARGET)

rebuild: clean $(TARGET)

$(TARGET): create_dir $(OBJECTS)
	@ar rcs $(BUILD_DIR)/$(TARGET) $(shell find "$(BUILD_DIR)/$(SRC_DIR)" -name "*.o" -not -name "main.o")
	@ar rcs $(TARGET) $(shell find "$(BUILD_DIR)/$(SRC_DIR)" -name "*.o" -not -name "main.o")

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $^

run: clean create_dir_run $(OBJECTS_RUN)
	@$(CC) $(CFLAGS) $(shell find "$(BUILD_DIR)" -name "*.o") -o $(BIN_DIR)/$(EXECUTABLE) -lm
	@./$(BIN_DIR)/$(EXECUTABLE)

test: $(TARGET) $(OBJECTS_TEST)
	@$(CC) $(CFLAGS) $(wildcard $(BUILD_DIR)/$(TEST_DIR)/*.o) $(BUILD_DIR)/$(TARGET) $(LDLIBS) -L. $(BUILD_DIR)/$(TARGET) -o $(BIN_DIR)/$(TEST_TARGET)
	@./$(BIN_DIR)/$(TEST_TARGET)
	
gcov_report: $(TARGET)
	@$(CC) --coverage $(CFLAGS) $(wildcard $(TEST_DIR)/*.c) $(LDLIBS) $(MODULES) -o $(BIN_DIR)/$(TEST_TARGET)_gcov
	@./$(BIN_DIR)/$(TEST_TARGET)_gcov
	@lcov -t "test_coverage" -o test_coverage.info -c -d .
	@genhtml -o report test_coverage.info
	@rm -rf */*.gcda */*.gcno report/test_coverage.info *.info

format_style:
	@cp ../materials/linters/.clang-format .
	@clang-format -n */*.c */*.h
	@clang-format -i */*.c */*.h
	@ # rm ./.clang-format

valgrind_check: test
	@CK_FORK=no valgrind --vgdb=no --tool=memcheck --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="valgrind.log" -v --verbose -q --quiet -s ./$(BIN_DIR)/$(TEST_TARGET)

run_and_valgrind: run
	valgrind --track-origins=yes --leak-check=full ./$(BIN_DIR)/$(EXECUTABLE)

clean:
	@echo "Deleting unnecessary files..."
	@rm -rf **/*.dSYM **/*.dSYM **/*.log **/*.log test_coverage.info obj bin report *.a *.log

# Установка check.h

install_check_arch:
	@sudo pacman -S check

install_check_debian:
	@sudo apt install check

install_check_macos:
	@/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

install_check_macos_brew:
	@brew install check

create_dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	@mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	@mkdir -p $(BIN_DIR)

create_dir_run:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	@mkdir -p $(BIN_DIR)
	

# ═══════════════════════════════════════════════════════════════════════════
#  HUNTER PROTOCOL 2.0 — DAY 11: STRINGS DEEP DIVE
#  Makefile
# ═══════════════════════════════════════════════════════════════════════════

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c17 -O2
DEBUG_FLAGS = -g -fsanitize=address,undefined

.PHONY: all clean test debug valgrind exercises

# Default: build everything
all: test_strings exercises_bin

# Reference implementation tests
test_strings: my_string.c test_my_string.c my_string.h
	$(CC) $(CFLAGS) -o $@ my_string.c test_my_string.c

# Your exercises
exercises_bin: exercises.c
	$(CC) $(CFLAGS) -o $@ exercises.c

# Run tests
test: test_strings
	@echo "\n━━━ Running Reference Tests ━━━"
	./test_strings

# Run your exercises
exercises: exercises_bin
	@echo "\n━━━ Running Your Exercises ━━━"
	./exercises_bin

# Debug build with sanitizers
debug: my_string.c test_my_string.c my_string.h
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o test_strings_debug my_string.c test_my_string.c
	./test_strings_debug

# Memory check with Valgrind
valgrind: test_strings
	valgrind --leak-check=full --error-exitcode=1 ./test_strings

# Clean build artifacts
clean:
	rm -f test_strings test_strings_debug exercises_bin

# Help
help:
	@echo "Available targets:"
	@echo "  make all       - Build everything"
	@echo "  make test      - Run reference implementation tests"
	@echo "  make exercises - Run YOUR exercise implementations"
	@echo "  make debug     - Build with sanitizers"
	@echo "  make valgrind  - Run with memory checking"
	@echo "  make clean     - Remove built files"

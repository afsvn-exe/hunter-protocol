#
# Makefile — The System: Hunter Protocol
# 
# Phase 1: The Seed
#
# Learning Focus:
#   - Make build system basics
#   - Compiler flags
#   - Dependencies
#   - Phony targets
#
# Usage:
#   make        - Build the project
#   make clean  - Remove build artifacts
#   make run    - Build and run
#   make debug  - Build with debug symbols
#

# ============================================================================
# CONFIGURATION
# ============================================================================

# Compiler
CC := gcc

# Base compiler flags
#   -Wall:     Enable all common warnings
#   -Wextra:   Enable extra warnings
#   -std=c99:  Use C99 standard (matches Effective C recommendations)
#   -pedantic: Strictly follow the standard
CFLAGS := -Wall -Wextra -std=c99 -pedantic

# Additional safety flags (from Effective C)
#   -Werror=implicit-function-declaration: Error on missing prototypes
#   -Wformat=2: Extra format string checks
#   -Wconversion: Warn on implicit type conversions
CFLAGS += -Werror=implicit-function-declaration
CFLAGS += -Wformat=2

# Debug flags (used with 'make debug')
DEBUG_FLAGS := -g -O0 -DDEBUG

# Release flags (used with 'make release')
RELEASE_FLAGS := -O2 -DNDEBUG

# Output binary name
TARGET := hunter

# ============================================================================
# SOURCE FILES
# ============================================================================

# All .c files in current directory
SOURCES := main.c hunter.c quest.c save.c display.c

# Object files (replace .c with .o)
OBJECTS := $(SOURCES:.c=.o)

# Header files (for dependency tracking)
HEADERS := hunter.h quest.h save.h display.h

# ============================================================================
# TARGETS
# ============================================================================

# Default target: build the executable
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo ""
	@echo "╔═══════════════════════════════════════════╗"
	@echo "║   BUILD COMPLETE: ./$(TARGET)              ║"
	@echo "║   Run with: make run                      ║"
	@echo "╚═══════════════════════════════════════════╝"

# Compile .c files to .o files
# The pattern rule: any .o depends on its .c and all headers
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all
	@echo "Debug build complete (with symbols for gdb)"

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: clean all
	@echo "Release build complete (optimized)"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Cleaned."

# Remove save data (use with caution!)
clean-save:
	rm -rf ~/.hunter-protocol
	@echo "Save data deleted."

# Reset everything
reset: clean clean-save
	@echo "Full reset complete."

# ============================================================================
# DEVELOPMENT HELPERS
# ============================================================================

# Check for memory leaks (requires valgrind)
memcheck: debug
	valgrind --leak-check=full ./$(TARGET)

# Static analysis (requires cppcheck)
analyze:
	cppcheck --enable=all --std=c99 $(SOURCES)

# Format code (requires clang-format)
format:
	clang-format -i $(SOURCES) $(HEADERS)

# Count lines of code
loc:
	@wc -l $(SOURCES) $(HEADERS) | tail -1

# Show what would be built
info:
	@echo "Target:  $(TARGET)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Headers: $(HEADERS)"
	@echo "CC:      $(CC)"
	@echo "CFLAGS:  $(CFLAGS)"

# ============================================================================
# PHONY TARGETS
# ============================================================================

# These targets don't create files with these names
.PHONY: all clean debug release run memcheck analyze format loc info clean-save reset

# ============================================================================
# NOTES FOR THE HUNTER
# ============================================================================
#
# This Makefile follows Effective C best practices:
#
# 1. We use -std=c99 for portable, standard-compliant code
# 2. -Wall -Wextra catches common bugs at compile time
# 3. -pedantic ensures we don't use compiler extensions
# 4. Debug vs Release builds have different optimization levels
#
# Common commands:
#   make         Build the project
#   make run     Build and run
#   make clean   Remove build files
#   make debug   Build with debug info for gdb
#
# As you learn more, try:
#   make memcheck   Run valgrind to find memory leaks
#   make analyze    Run static analysis
#

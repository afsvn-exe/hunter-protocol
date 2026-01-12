/**
 * ═══════════════════════════════════════════════════════════════════════════
 *  HUNTER PROTOCOL 2.0 — DAY 11: STRINGS DEEP DIVE
 *  test_my_string.c — Test Driver
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  "Test ruthlessly. Trust nothing."
 *
 *  Compile: gcc -Wall -Wextra -std=c17 -o test_strings \
 *               my_string.c test_my_string.c
 *  Run:     ./test_strings
 *  Valgrind: valgrind --leak-check=full ./test_strings
 * ═══════════════════════════════════════════════════════════════════════════
 */

#include <stdio.h>
#include <string.h>  /* For comparing against standard library */
#include <stdlib.h>
#include "my_string.h"

/* Test result tracking */
static int tests_passed = 0;
static int tests_failed = 0;

/* Test assertion macro */
#define TEST(condition, name) do { \
    if (condition) { \
        printf("  ✓ %s\n", name); \
        tests_passed++; \
    } else { \
        printf("  ✗ %s — FAILED!\n", name); \
        tests_failed++; \
    } \
} while (0)

/* Test group header */
#define TEST_GROUP(name) printf("\n━━━ %s ━━━\n", name)


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  strlen Tests
 * ──────────────────────────────────────────────────────────────────────────
 */
void test_strlen(void)
{
    TEST_GROUP("my_strlen");
    
    /* Basic cases */
    TEST(my_strlen("") == 0, "empty string");
    TEST(my_strlen("a") == 1, "single character");
    TEST(my_strlen("hello") == 5, "typical string");
    TEST(my_strlen("hello world") == 11, "string with space");
    
    /* Edge cases */
    TEST(my_strlen("\0hidden") == 0, "string starting with null");
    TEST(my_strlen("abc\0def") == 3, "embedded null");
    
    /* Compare against standard library */
    const char *test_strings[] = {"", "a", "test", "longer string here", NULL};
    for (int i = 0; test_strings[i] != NULL; i++) {
        char name[64];
        snprintf(name, sizeof(name), "matches stdlib for \"%s\"", test_strings[i]);
        TEST(my_strlen(test_strings[i]) == strlen(test_strings[i]), name);
    }
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  strcpy Tests
 * ──────────────────────────────────────────────────────────────────────────
 */
void test_strcpy(void)
{
    TEST_GROUP("my_strcpy");
    
    char dest[64];
    char std_dest[64];
    
    /* Basic copy */
    my_strcpy(dest, "hello");
    TEST(strcmp(dest, "hello") == 0, "basic copy");
    
    /* Empty string */
    my_strcpy(dest, "");
    TEST(strcmp(dest, "") == 0, "empty string copy");
    
    /* Return value is dest */
    char *ret = my_strcpy(dest, "test");
    TEST(ret == dest, "returns destination pointer");
    
    /* Compare against standard library */
    const char *sources[] = {"", "a", "hello world", "test\tstring\n", NULL};
    for (int i = 0; sources[i] != NULL; i++) {
        my_strcpy(dest, sources[i]);
        strcpy(std_dest, sources[i]);
        char name[64];
        snprintf(name, sizeof(name), "matches stdlib for \"%s\"", 
                 sources[i][0] ? sources[i] : "(empty)");
        TEST(strcmp(dest, std_dest) == 0, name);
    }
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  strncpy Tests
 * ──────────────────────────────────────────────────────────────────────────
 */
void test_strncpy(void)
{
    TEST_GROUP("my_strncpy");
    
    char dest[10];
    
    /* Source shorter than n — should pad with nulls */
    memset(dest, 'X', sizeof(dest));
    my_strncpy(dest, "Hi", 5);
    TEST(dest[0] == 'H' && dest[1] == 'i', "copies characters");
    TEST(dest[2] == '\0' && dest[3] == '\0' && dest[4] == '\0', "pads with nulls");
    TEST(dest[5] == 'X', "doesn't write beyond n");
    
    /* Source longer than n — NO null terminator! */
    memset(dest, 'X', sizeof(dest));
    my_strncpy(dest, "HelloWorld", 5);
    TEST(memcmp(dest, "Hello", 5) == 0, "copies exactly n chars");
    TEST(dest[5] == 'X', "doesn't add null when src >= n");
    
    /* n = 0 */
    memset(dest, 'X', sizeof(dest));
    my_strncpy(dest, "test", 0);
    TEST(dest[0] == 'X', "n=0 copies nothing");
    
    /* Exact fit */
    memset(dest, 'X', sizeof(dest));
    my_strncpy(dest, "Hi", 3);
    TEST(strcmp(dest, "Hi") == 0, "exact fit works");
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  strcmp Tests
 * ──────────────────────────────────────────────────────────────────────────
 */
void test_strcmp(void)
{
    TEST_GROUP("my_strcmp");
    
    /* Equal strings */
    TEST(my_strcmp("", "") == 0, "empty strings equal");
    TEST(my_strcmp("hello", "hello") == 0, "identical strings");
    TEST(my_strcmp("abc", "abc") == 0, "short identical");
    
    /* First string smaller */
    TEST(my_strcmp("abc", "abd") < 0, "abc < abd");
    TEST(my_strcmp("abc", "abcd") < 0, "abc < abcd (prefix)");
    TEST(my_strcmp("", "a") < 0, "empty < non-empty");
    TEST(my_strcmp("A", "a") < 0, "A < a (ASCII)");
    
    /* First string larger */
    TEST(my_strcmp("abd", "abc") > 0, "abd > abc");
    TEST(my_strcmp("abcd", "abc") > 0, "abcd > abc (prefix)");
    TEST(my_strcmp("a", "") > 0, "non-empty > empty");
    TEST(my_strcmp("a", "A") > 0, "a > A (ASCII)");
    
    /* Compare against standard library */
    struct { const char *s1; const char *s2; } pairs[] = {
        {"", ""}, {"a", "a"}, {"abc", "abd"}, {"xyz", "xy"}, {NULL, NULL}
    };
    for (int i = 0; pairs[i].s1 != NULL; i++) {
        int my_result = my_strcmp(pairs[i].s1, pairs[i].s2);
        int std_result = strcmp(pairs[i].s1, pairs[i].s2);
        /* Compare signs, not exact values */
        int same_sign = (my_result < 0 && std_result < 0) ||
                        (my_result > 0 && std_result > 0) ||
                        (my_result == 0 && std_result == 0);
        char name[64];
        snprintf(name, sizeof(name), "matches stdlib sign for \"%s\" vs \"%s\"",
                 pairs[i].s1, pairs[i].s2);
        TEST(same_sign, name);
    }
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  strncmp Tests
 * ──────────────────────────────────────────────────────────────────────────
 */
void test_strncmp(void)
{
    TEST_GROUP("my_strncmp");
    
    /* n = 0 always returns 0 */
    TEST(my_strncmp("abc", "xyz", 0) == 0, "n=0 returns 0");
    
    /* Compare prefixes */
    TEST(my_strncmp("hello", "helicopter", 3) == 0, "hel == hel");
    TEST(my_strncmp("hello", "helicopter", 4) > 0, "hell > heli");
    
    /* Full comparison when n > strlen */
    TEST(my_strncmp("abc", "abc", 100) == 0, "full compare when n > len");
    TEST(my_strncmp("abc", "abd", 100) < 0, "full compare finds difference");
    
    /* Compare against standard library */
    TEST(my_strncmp("abc", "abd", 2) == strncmp("abc", "abd", 2), 
         "matches stdlib n=2");
    TEST((my_strncmp("abc", "abd", 3) < 0) == (strncmp("abc", "abd", 3) < 0),
         "matches stdlib n=3 (sign)");
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  strcat Tests
 * ──────────────────────────────────────────────────────────────────────────
 */
void test_strcat(void)
{
    TEST_GROUP("my_strcat");
    
    char dest[64];
    
    /* Basic concatenation */
    strcpy(dest, "Hello");
    my_strcat(dest, " World");
    TEST(strcmp(dest, "Hello World") == 0, "basic concat");
    
    /* Concat to empty string */
    dest[0] = '\0';
    my_strcat(dest, "test");
    TEST(strcmp(dest, "test") == 0, "concat to empty");
    
    /* Concat empty string */
    strcpy(dest, "hello");
    my_strcat(dest, "");
    TEST(strcmp(dest, "hello") == 0, "concat empty string");
    
    /* Return value */
    strcpy(dest, "a");
    char *ret = my_strcat(dest, "b");
    TEST(ret == dest, "returns destination pointer");
    
    /* Multiple concats */
    dest[0] = '\0';
    my_strcat(dest, "one");
    my_strcat(dest, " ");
    my_strcat(dest, "two");
    TEST(strcmp(dest, "one two") == 0, "multiple concats");
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  Main
 * ──────────────────────────────────────────────────────────────────────────
 */
int main(void)
{
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  HUNTER PROTOCOL 2.0 — DAY 11: STRING FUNCTION TESTS          ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    test_strlen();
    test_strcpy();
    test_strncpy();
    test_strcmp();
    test_strncmp();
    test_strcat();
    
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("  RESULTS: %d passed, %d failed\n", tests_passed, tests_failed);
    printf("═══════════════════════════════════════════════════════════════\n");
    
    if (tests_failed == 0) {
        printf("\n  🏆 ALL TESTS PASSED — SKILL UNLOCKED!\n\n");
        printf("  [SKILL: String Implementation] acquired\n");
        printf("  +150 XP — You now own the abstractions.\n\n");
    } else {
        printf("\n  💀 YOU DIED — %d tests failed\n", tests_failed);
        printf("  Analyze your failures. Respawn stronger.\n\n");
    }
    
    return tests_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

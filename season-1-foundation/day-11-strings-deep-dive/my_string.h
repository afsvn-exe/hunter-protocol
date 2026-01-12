/**
 * ═══════════════════════════════════════════════════════════════════════════
 *  HUNTER PROTOCOL 2.0 — DAY 11: STRINGS DEEP DIVE
 *  my_string.h — Custom String Function Declarations
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  "Own the abstractions. Implement what you use."
 *
 *  Following Effective C 2nd Edition best practices:
 *  - Use size_t for sizes and lengths (never negative)
 *  - const-correctness for read-only parameters
 *  - Clear documentation of preconditions/postconditions
 *  - Restrict pointers where aliasing is undefined
 * ═══════════════════════════════════════════════════════════════════════════
 */

#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>  /* size_t */

/**
 * my_strlen - Calculate the length of a null-terminated string
 *
 * @param s: Pointer to null-terminated string (must not be NULL)
 *
 * @return: Number of characters before the null terminator
 *
 * Precondition:  s points to a valid null-terminated string
 * Postcondition: Return value is the count of chars before '\0'
 *
 * Time:  O(n) where n is string length
 * Space: O(1)
 */
size_t my_strlen(const char *s);

/**
 * my_strcpy - Copy a string including the null terminator
 *
 * @param dest: Destination buffer (must have sufficient space)
 * @param src:  Source string (must be null-terminated)
 *
 * @return: Pointer to dest (for chaining)
 *
 * Precondition:  dest has space for strlen(src) + 1 bytes
 *                src is null-terminated
 *                dest and src do NOT overlap (restrict)
 * Postcondition: dest contains exact copy of src including '\0'
 *
 * WARNING: This is UNSAFE — no bounds checking!
 *          Use my_strncpy for safer alternative.
 *
 * Time:  O(n) where n is strlen(src)
 * Space: O(1)
 */
char *my_strcpy(char * restrict dest, const char * restrict src);

/**
 * my_strncpy - Copy at most n characters from src to dest
 *
 * @param dest: Destination buffer
 * @param src:  Source string
 * @param n:    Maximum characters to copy
 *
 * @return: Pointer to dest
 *
 * Precondition:  dest has space for at least n bytes
 * Postcondition: If strlen(src) < n: dest is null-terminated, padded with '\0'
 *                If strlen(src) >= n: dest contains n chars, NO null terminator!
 *
 * WARNING: dest may NOT be null-terminated if strlen(src) >= n!
 *          Always ensure null termination after calling.
 *
 * Time:  O(n)
 * Space: O(1)
 */
char *my_strncpy(char * restrict dest, const char * restrict src, size_t n);

/**
 * my_strcmp - Compare two strings lexicographically
 *
 * @param s1: First string (null-terminated)
 * @param s2: Second string (null-terminated)
 *
 * @return: < 0 if s1 < s2 (lexicographically)
 *          = 0 if s1 == s2
 *          > 0 if s1 > s2
 *
 * Precondition:  Both s1 and s2 are null-terminated
 * Postcondition: Neither string is modified
 *
 * Note: Comparison is done byte-by-byte as unsigned char values
 *       (per C standard, to handle extended character sets)
 *
 * Time:  O(min(len(s1), len(s2)))
 * Space: O(1)
 */
int my_strcmp(const char *s1, const char *s2);

/**
 * my_strncmp - Compare at most n characters of two strings
 *
 * @param s1: First string
 * @param s2: Second string
 * @param n:  Maximum characters to compare
 *
 * @return: Same semantics as my_strcmp, but stops after n chars
 *
 * Time:  O(min(n, len(s1), len(s2)))
 * Space: O(1)
 */
int my_strncmp(const char *s1, const char *s2, size_t n);

/**
 * my_strcat - Concatenate src onto the end of dest
 *
 * @param dest: Destination string (must have space for result)
 * @param src:  Source string to append
 *
 * @return: Pointer to dest
 *
 * Precondition:  dest has space for strlen(dest) + strlen(src) + 1
 *                Neither string is NULL
 * Postcondition: src is appended to dest with null terminator
 *
 * WARNING: UNSAFE — no bounds checking! Use bounded alternative.
 *
 * Time:  O(len(dest) + len(src))
 * Space: O(1)
 */
char *my_strcat(char * restrict dest, const char * restrict src);

#endif /* MY_STRING_H */

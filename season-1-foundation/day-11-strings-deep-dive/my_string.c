/**
 * ═══════════════════════════════════════════════════════════════════════════
 *  HUNTER PROTOCOL 2.0 — DAY 11: STRINGS DEEP DIVE
 *  my_string.c — Custom String Function Implementations
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  "Walk the bytes. Own every step."
 *
 *  Each implementation is deliberately simple and explicit.
 *  No clever tricks — just clear, correct code.
 * ═══════════════════════════════════════════════════════════════════════════
 */

#include "my_string.h"

/*
 * ──────────────────────────────────────────────────────────────────────────
 *  my_strlen — The Length Counter
 * ──────────────────────────────────────────────────────────────────────────
 *
 *  Algorithm (spoken aloud):
 *  "Start at the beginning. Count steps until I see '\0'. Return count."
 *
 *  Memory visualization:
 *  
 *      s → [ 'H' ][ 'e' ][ 'l' ][ 'l' ][ 'o' ][ '\0' ]
 *           len=0  len=1  len=2  len=3  len=4   STOP!
 *
 *  Return: 5
 */
size_t my_strlen(const char *s)
{
    size_t len = 0;
    
    /*
     * Walk the string byte-by-byte.
     * The condition s[len] != '\0' is equivalent to s[len] (since '\0' is 0).
     * But we write it explicitly for clarity — explicit is better than implicit.
     */
    while (s[len] != '\0') {
        len++;
    }
    
    return len;
}

/*
 * Alternative pointer-style implementation (for understanding):
 *
 * size_t my_strlen_ptr(const char *s)
 * {
 *     const char *p = s;       // Save starting position
 *     while (*p != '\0') {     // Walk until null
 *         p++;                 // Advance pointer
 *     }
 *     return p - s;            // Pointer arithmetic: distance traveled
 * }
 */


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  my_strcpy — The Copyist
 * ──────────────────────────────────────────────────────────────────────────
 *
 *  Algorithm (spoken aloud):
 *  "Copy each byte from source to destination. Include the null terminator."
 *
 *  Memory visualization:
 *
 *  BEFORE:
 *      src  → [ 'H' ][ 'i' ][ '\0' ]
 *      dest → [ ? ][ ? ][ ? ][ ? ]  (uninitialized)
 *
 *  DURING (i=0):
 *      dest[0] = src[0] = 'H'
 *  DURING (i=1):
 *      dest[1] = src[1] = 'i'
 *  DURING (i=2):
 *      dest[2] = src[2] = '\0' ← Loop exits AFTER copying this!
 *
 *  AFTER:
 *      dest → [ 'H' ][ 'i' ][ '\0' ][ ? ]
 *
 *  The 'restrict' keyword tells the compiler that dest and src
 *  don't overlap, enabling optimizations. If they DO overlap,
 *  behavior is undefined.
 */
char *my_strcpy(char * restrict dest, const char * restrict src)
{
    size_t i = 0;
    
    /*
     * Copy bytes including the null terminator.
     * 
     * The loop condition is AFTER the assignment (post-check),
     * ensuring we copy '\0' before stopping.
     * 
     * Equivalent idiom: while ((dest[i] = src[i]) != '\0') i++;
     * But we split it for clarity.
     */
    do {
        dest[i] = src[i];
    } while (src[i++] != '\0');
    
    return dest;  /* Return dest for chaining: strcpy(d, strcpy(d2, s)) */
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  my_strncpy — The Bounded Copyist
 * ──────────────────────────────────────────────────────────────────────────
 *
 *  Algorithm:
 *  "Copy up to n bytes. If source ends early, pad with '\0'.
 *   If source is longer, DON'T add '\0' — caller must handle it!"
 *
 *  This function has QUIRKY SEMANTICS (historical reasons):
 *  - If strlen(src) < n: dest is padded with '\0' bytes
 *  - If strlen(src) >= n: dest is NOT null-terminated!
 *
 *  Example (n=4):
 *      src = "Hi"
 *      dest = [ 'H' ][ 'i' ][ '\0' ][ '\0' ]  ← Padded
 *
 *      src = "Hello"
 *      dest = [ 'H' ][ 'e' ][ 'l' ][ 'l' ]   ← NO null terminator!
 */
char *my_strncpy(char * restrict dest, const char * restrict src, size_t n)
{
    size_t i;
    
    /* Phase 1: Copy from src until we hit '\0' or reach n */
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    
    /* Phase 2: If we stopped early, pad the rest with '\0' */
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    
    return dest;
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  my_strcmp — The Comparator
 * ──────────────────────────────────────────────────────────────────────────
 *
 *  Algorithm (spoken aloud):
 *  "Compare character by character. If they differ, return the difference.
 *   If both reach '\0' at the same time, they're equal (return 0)."
 *
 *  Why cast to unsigned char?
 *  The C standard specifies that string comparison should treat
 *  characters as unsigned char to handle extended character sets
 *  correctly. Without this, negative char values could cause
 *  incorrect ordering.
 *
 *  Example:
 *      "abc" vs "abd"
 *      'a' == 'a' → continue
 *      'b' == 'b' → continue
 *      'c' vs 'd' → 'c' (99) - 'd' (100) = -1 → s1 < s2
 *
 *      "abc" vs "abc"
 *      'a' == 'a' → continue
 *      'b' == 'b' → continue
 *      'c' == 'c' → continue
 *      '\0' == '\0' → return 0 (equal)
 *
 *      "abc" vs "ab"
 *      'a' == 'a' → continue
 *      'b' == 'b' → continue
 *      'c' vs '\0' → 'c' (99) - '\0' (0) = 99 → s1 > s2
 */
int my_strcmp(const char *s1, const char *s2)
{
    /* Walk both strings in lockstep */
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    
    /*
     * At this point, either:
     * 1. *s1 == '\0' (end of s1)
     * 2. *s1 != *s2 (found difference)
     *
     * Either way, return the difference of current characters.
     * Cast to unsigned char per C standard for correct ordering.
     */
    return (unsigned char)*s1 - (unsigned char)*s2;
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  my_strncmp — The Bounded Comparator
 * ──────────────────────────────────────────────────────────────────────────
 *
 *  Same as strcmp, but stop after n characters.
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    if (n == 0) {
        return 0;  /* Nothing to compare */
    }
    
    /* Walk both strings, but stop at n characters */
    while (n > 1 && *s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
        n--;
    }
    
    return (unsigned char)*s1 - (unsigned char)*s2;
}


/*
 * ──────────────────────────────────────────────────────────────────────────
 *  my_strcat — The Concatenator
 * ──────────────────────────────────────────────────────────────────────────
 *
 *  Algorithm:
 *  "Find the end of dest (its '\0'). Copy src there."
 *
 *  Memory visualization:
 *
 *  BEFORE:
 *      dest → [ 'H' ][ 'i' ][ '\0' ][ ? ][ ? ][ ? ]
 *      src  → [ '!' ][ '!' ][ '\0' ]
 *
 *  Step 1: Find end of dest
 *      dest + 2 → [ '\0' ]
 *
 *  Step 2: Copy src starting there
 *      dest → [ 'H' ][ 'i' ][ '!' ][ '!' ][ '\0' ][ ? ]
 *
 *  DANGER: If dest doesn't have enough space, we overflow!
 */
char *my_strcat(char * restrict dest, const char * restrict src)
{
    /* Find the end of dest */
    char *end = dest;
    while (*end != '\0') {
        end++;
    }
    
    /* Copy src to the end (including null terminator) */
    while (*src != '\0') {
        *end++ = *src++;
    }
    *end = '\0';  /* Ensure null termination */
    
    return dest;
}

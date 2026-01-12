/**
 * ═══════════════════════════════════════════════════════════════════════════
 *  HUNTER PROTOCOL 2.0 — DAY 11: YOUR TURN
 *  exercises.c — Implement These Yourself
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  RULES OF ENGAGEMENT:
 *  1. Do NOT look at my_string.c until you've tried each function
 *  2. Think through the algorithm FIRST (speak it aloud)
 *  3. Write the code, then test
 *  4. Only peek at reference if stuck for >15 minutes
 *
 *  Compile: gcc -Wall -Wextra -std=c17 -o exercises exercises.c
 *  Run:     ./exercises
 * ═══════════════════════════════════════════════════════════════════════════
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* For verification only */
#include <stddef.h>

/* ═══════════════════════════════════════════════════════════════════════════
 *  EXERCISE 1: Implement hunter_strlen
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM (say it aloud before coding):
 *  "Walk the string. Count steps. Stop at null. Return count."
 *
 *  HINT: What type should you use for the counter? (Think: can length be negative?)
 */
size_t hunter_strlen(const char *s)
{
    if(s == NULL){
    	return 0; 
    }
    size_t count = 0; 
    while(s[count] != '\0'){
    	count++; 
    }
    return count; 
}


/* ═══════════════════════════════════════════════════════════════════════════
 *  EXERCISE 2: Implement hunter_strcpy
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM (say it aloud before coding):
 *  "Copy each byte. Include the null. Return destination."
 *
 *  HINT: You need to copy the '\0' too! Loop should run until AFTER copying it.
 */
char *hunter_strcpy(char *dest, const char *src)
{
    if(src == NULL){
    	return NULL; 
    }
    
    size_t count = 0; 
    while(src[count] != '\0'){
    	dest[count] = src[count]; 
    	count++; 
    }
    dest[count] = '\0'; 
    return dest;
}


/* ═══════════════════════════════════════════════════════════════════════════
 *  EXERCISE 3: Implement hunter_strcmp
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM (say it aloud before coding):
 *  "Compare byte by byte. Stop if different OR if either hits null.
 *   Return difference of current bytes."
 *
 *  HINT: Cast to unsigned char when computing the difference (why?)
 */
int hunter_strcmp(const char *s1, const char *s2)
{
    while(*s1 != '\0' && *s1 == *s2){
    	s1++; 
	s2++; 
    }
    return (unsigned char)*s1 - (unsigned char)*s2; 
}


/* ═══════════════════════════════════════════════════════════════════════════
 *  EXERCISE 4: Implement hunter_strcat
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM (say it aloud before coding):
 *  "Find end of dest. Copy src there. Return dest."
 *
 *  HINT: This is strlen + strcpy combined. But think about the order!
 */
char *hunter_strcat(char *dest, const char *src)
{
    char *end = dest; 
    while(*end != '\0'){
    	end++; 
    }
	
    while(*src != '\0'){
    	*end++ = *src++; 
    }
    *end = '\0';

    return dest;
}


/* ═══════════════════════════════════════════════════════════════════════════
 *  BONUS EXERCISE: Implement hunter_strrev (Reverse a string IN-PLACE)
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM:
 *  "Swap first and last, move inward, repeat until pointers meet."
 *
 *  Example: "hello" → "olleh"
 *
 *  HINT: Use two pointers. One from start, one from end. Swap and advance.
 *        Be careful with empty strings!
 */
char *hunter_strrev(char *s)
{
    if(s == NULL || *s == '\0'){
	return s; 
    }
	
    char *start = s; 
    char *end = s; 

    while(*(end + 1) != '\0'){
	    end++; 
    }

    while(start < end){
    	char temp = *start; 
	*start = *end;
	*end = temp; 

	start++; 
	end--; 
    }

    return s;
}


/* ═══════════════════════════════════════════════════════════════════════════
 *  BOSS EXERCISE: Implement hunter_strstr (Find substring)
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  Find first occurrence of needle in haystack.
 *  Return pointer to start of match, or NULL if not found.
 *
 *  Example: hunter_strstr("hello world", "wor") → pointer to "world"
 *           hunter_strstr("hello world", "xyz") → NULL
 *
 *  ALGORITHM (think carefully!):
 *  "For each position in haystack, try to match needle.
 *   If all needle chars match, return that position.
 *   If mismatch, try next position in haystack."
 *
 *  HINT: Empty needle returns haystack (convention).
 *        This is O(n*m) — not optimal, but correct.
 */
char *hunter_strstr(const char *haystack, const char *needle)
{
    /* YOUR CODE HERE */
    
    (void)haystack; (void)needle; /* Remove when implemented */
    return NULL;
}


/* ═══════════════════════════════════════════════════════════════════════════
 *  TEST HARNESS
 * ═══════════════════════════════════════════════════════════════════════════
 */

#define TEST(cond, name) do { \
    if (cond) { printf("  ✓ %s\n", name); passed++; } \
    else { printf("  ✗ %s — FAILED\n", name); failed++; } \
} while(0)

int main(void)
{
    int passed = 0, failed = 0;
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  HUNTER PROTOCOL — DAY 11 EXERCISES                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    /* strlen tests */
    printf("━━━ hunter_strlen ━━━\n");
    TEST(hunter_strlen("") == 0, "empty string");
    TEST(hunter_strlen("a") == 1, "single char");
    TEST(hunter_strlen("hello") == 5, "basic string");
    TEST(hunter_strlen("hello world") == 11, "string with space");
    
    /* strcpy tests */
    printf("\n━━━ hunter_strcpy ━━━\n");
    char buf[64];
    hunter_strcpy(buf, "hello");
    TEST(strcmp(buf, "hello") == 0, "basic copy");
    hunter_strcpy(buf, "");
    TEST(strcmp(buf, "") == 0, "empty copy");
    TEST(hunter_strcpy(buf, "test") == buf, "returns dest");
    
    /* strcmp tests */
    printf("\n━━━ hunter_strcmp ━━━\n");
    TEST(hunter_strcmp("abc", "abc") == 0, "equal strings");
    TEST(hunter_strcmp("abc", "abd") < 0, "abc < abd");
    TEST(hunter_strcmp("abd", "abc") > 0, "abd > abc");
    TEST(hunter_strcmp("", "") == 0, "empty equal");
    TEST(hunter_strcmp("a", "") > 0, "non-empty > empty");
    
    /* strcat tests */
    printf("\n━━━ hunter_strcat ━━━\n");
    strcpy(buf, "Hello");
    hunter_strcat(buf, " World");
    TEST(strcmp(buf, "Hello World") == 0, "basic concat");
    buf[0] = '\0';
    hunter_strcat(buf, "test");
    TEST(strcmp(buf, "test") == 0, "concat to empty");
    
    /* BONUS: strrev tests */
    printf("\n━━━ hunter_strrev [BONUS] ━━━\n");
    strcpy(buf, "hello");
    hunter_strrev(buf);
    TEST(strcmp(buf, "olleh") == 0, "reverse 5-char");
    strcpy(buf, "a");
    hunter_strrev(buf);
    TEST(strcmp(buf, "a") == 0, "reverse single char");
    buf[0] = '\0';
    hunter_strrev(buf);
    TEST(strcmp(buf, "") == 0, "reverse empty");
    strcpy(buf, "ab");
    hunter_strrev(buf);
    TEST(strcmp(buf, "ba") == 0, "reverse 2-char");
    
    /* BOSS: strstr tests */
    printf("\n━━━ hunter_strstr [BOSS] ━━━\n");
    TEST(hunter_strstr("hello world", "wor") != NULL, "finds substring");
    if (hunter_strstr("hello world", "wor") != NULL) {
        TEST(strcmp(hunter_strstr("hello world", "wor"), "world") == 0, 
             "returns correct position");
    }
    TEST(hunter_strstr("hello", "xyz") == NULL, "returns NULL if not found");
    TEST(hunter_strstr("hello", "") == (char*)"hello", "empty needle returns haystack");
    TEST(hunter_strstr("hello", "hello") == (char*)"hello", "exact match");
    TEST(hunter_strstr("hello", "helloworld") == NULL, "needle longer than haystack");
    
    /* Results */
    printf("\n═══════════════════════════════════════════════════════════════\n");
    printf("  RESULTS: %d passed, %d failed\n", passed, failed);
    printf("═══════════════════════════════════════════════════════════════\n\n");
    
    if (failed == 0) {
        printf("  🏆 PERFECT CLEAR — ALL EXERCISES COMPLETE!\n\n");
        printf("  [SKILL: String Mastery] upgraded to Lv. 2\n");
        printf("  +300 XP — You wrote the standard library.\n\n");
    } else if (failed <= 5) {
        printf("  ⚔️ GOOD PROGRESS — %d tests remaining\n", failed);
        printf("  Keep grinding. Analyze your failures.\n\n");
    } else {
        printf("  💀 YOU DIED — Review the algorithms, respawn.\n\n");
    }
    
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

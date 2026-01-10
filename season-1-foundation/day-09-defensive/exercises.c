/**
 * ═══════════════════════════════════════════════════════════════════════════
 * HUNTER PROTOCOL 2.0 — DAY 9: SHADOW QUESTS
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * DIFFICULTY: ★★☆☆☆ to ★★★★☆
 * 
 * Complete these exercises to level up your defensive programming skills.
 * Each exercise has clear preconditions, postconditions, and test cases.
 * 
 * Compile: gcc -Wall -Wextra -g -o exercises exercises.c
 * Test: ./exercises
 * Valgrind: valgrind --leak-check=full ./exercises
 * 
 * ═══════════════════════════════════════════════════════════════════════════
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "defensive.h"

/* Test framework */
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST_SECTION(name) printf("\n═══ %s ═══\n", name)
#define CHECK(cond, desc) do { \
    if (cond) { printf("  ✓ %s\n", desc); tests_passed++; } \
    else { printf("  ✗ %s\n", desc); tests_failed++; } \
} while(0)

/* ═══════════════════════════════════════════════════════════════════════════
 * EXERCISE 1: SAFE STRING LENGTH (★★☆☆☆)
 * 
 * Implement a bounds-checked string length function.
 * 
 * Preconditions:
 *   - str may be NULL (handle gracefully)
 *   - max_len is the maximum characters to check
 *   - out_len must not be NULL
 * 
 * Postconditions:
 *   - Returns ERR_OK on success, writes length to *out_len
 *   - Returns ERR_NULL_PTR if str is NULL
 *   - Returns ERR_NULL_PTR if out_len is NULL
 *   - Returns ERR_OVERFLOW if string exceeds max_len (no null terminator found)
 *   - Never reads beyond max_len characters
 * 
 * HINT: This is like strnlen() but with explicit error handling.
 * ═══════════════════════════════════════════════════════════════════════════ */

error_t safe_strlen(const char *str, size_t max_len, size_t *out_len) {
    //Step 1: Check if out_len is not NULL
    if(out_len == NULL){
    	return ERR_NULL_PTR; 
    }

    //Step 2: Check if str is not NULL 
    if(str == NULL){
    	return ERR_NULL_PTR; 
    }

    //Step 3: Count Characters up to max_len 
    size_t count = 0; 
    while(count <= max_len && str[count]){
    	count++; 
    }

    //Step 4: If max_len is reached without finding null terminator, overflow has occurred 
    if(count > max_len){
    	return ERR_OVERFLOW; 
    }

    //Step 5: Success - write result
   *out_len = count; 
   return ERR_OK; 

}

void test_exercise_1(void) {
    TEST_SECTION("EXERCISE 1: safe_strlen");
    
    size_t len;
    error_t err;
    
    /* Normal strings */
    err = safe_strlen("hello", 100, &len);
    CHECK(err == ERR_OK && len == 5, "\"hello\" has length 5");
    
    err = safe_strlen("", 100, &len);
    CHECK(err == ERR_OK && len == 0, "Empty string has length 0");
    
    err = safe_strlen("abc", 3, &len);
    CHECK(err == ERR_OK && len == 3, "\"abc\" with max_len=3 works");
    
    /* Error cases */
    err = safe_strlen(NULL, 100, &len);
    CHECK(err == ERR_NULL_PTR, "NULL string returns ERR_NULL_PTR");
    
    err = safe_strlen("test", 100, NULL);
    CHECK(err == ERR_NULL_PTR, "NULL out_len returns ERR_NULL_PTR");
    
    /* Overflow case - string longer than max_len */
    err = safe_strlen("this is long", 4, &len);
    CHECK(err == ERR_OVERFLOW, "String exceeding max_len returns ERR_OVERFLOW");
}

/* ═══════════════════════════════════════════════════════════════════════════
 * EXERCISE 2: CHECKED INTEGER ADDITION (★★★☆☆)
 * 
 * Implement overflow-safe integer addition.
 * 
 * Preconditions:
 *   - result must not be NULL
 *   - a and b are arbitrary signed integers
 * 
 * Postconditions:
 *   - Returns ERR_OK if a + b doesn't overflow, writes result
 *   - Returns ERR_OVERFLOW if a + b would overflow (positive)
 *   - Returns ERR_UNDERFLOW if a + b would overflow (negative)
 *   - Does NOT perform undefined behavior
 * 
 * HINT: Check BEFORE adding. Consider signs of operands.
 *       INT_MAX and INT_MIN from <limits.h> are useful.
 * ═══════════════════════════════════════════════════════════════════════════ */

error_t checked_add(int a, int b, int *result){
    //Step 1: Validate Output Pointer
    if(result == NULL){
    	return ERR_NULL_PTR; 
    }
    //Step 2: Check for positive overflow
    //if b > 0, overflow happens when a > INT_MAX - b
    if(b > 0 && a > INT_MAX - b){
    	return ERR_OVERFLOW; 
    }
    //Step 3: Check for negative underflow
    //if b < 0, underflow happens when a < INT_MIN - b
    if(b < 0 && a < INT_MIN - b){
    	return ERR_UNDERFLOW; 
    }
    //Safe to add
    *result = a + b; 
    return ERR_OK; 
}

void test_exercise_2(void) {
    TEST_SECTION("EXERCISE 2: checked_add");
    
    int result;
    error_t err;
    
    /* Normal addition */
    err = checked_add(5, 3, &result);
    CHECK(err == ERR_OK && result == 8, "5 + 3 = 8");
    
    err = checked_add(-5, -3, &result);
    CHECK(err == ERR_OK && result == -8, "-5 + -3 = -8");
    
    err = checked_add(100, -50, &result);
    CHECK(err == ERR_OK && result == 50, "100 + -50 = 50");
    
    /* Overflow cases */
    err = checked_add(INT_MAX, 1, &result);
    CHECK(err == ERR_OVERFLOW, "INT_MAX + 1 overflows");
    
    err = checked_add(INT_MAX - 10, 20, &result);
    CHECK(err == ERR_OVERFLOW, "(INT_MAX - 10) + 20 overflows");
    
    /* Underflow cases */
    err = checked_add(INT_MIN, -1, &result);
    CHECK(err == ERR_UNDERFLOW, "INT_MIN + -1 underflows");
    
    err = checked_add(INT_MIN + 10, -20, &result);
    CHECK(err == ERR_UNDERFLOW, "(INT_MIN + 10) + -20 underflows");
    
    /* Edge cases that DON'T overflow */
    err = checked_add(INT_MAX, 0, &result);
    CHECK(err == ERR_OK && result == INT_MAX, "INT_MAX + 0 is safe");
    
    err = checked_add(INT_MIN, 0, &result);
    CHECK(err == ERR_OK && result == INT_MIN, "INT_MIN + 0 is safe");
    
    /* NULL check */
    err = checked_add(1, 1, NULL);
    CHECK(err == ERR_NULL_PTR, "NULL result returns ERR_NULL_PTR");
}

/* ═══════════════════════════════════════════════════════════════════════════
 * EXERCISE 3: SAFE BUFFER COPY (★★★☆☆)
 * 
 * Implement a bounds-checked memory copy.
 * 
 * Preconditions:
 *   - dest and src may be NULL (handle gracefully)
 *   - dest_size is the total size of destination buffer
 *   - count is number of bytes to copy
 * 
 * Postconditions:
 *   - Returns ERR_OK if copy succeeds
 *   - Returns ERR_NULL_PTR if dest or src is NULL
 *   - Returns ERR_OUT_OF_BOUNDS if count > dest_size
 *   - Returns ERR_INVALID_ARG if count is 0
 *   - Never writes beyond dest_size
 * 
 * HINT: This is like memcpy_s from C11 Annex K.
 * ═══════════════════════════════════════════════════════════════════════════ */

error_t safe_memcpy(void *dest, size_t dest_size, 
                    const void *src, size_t count) {
    
    /* Step 1: Check pointers */
       if(dest == NULL || src == NULL){
       	return ERR_NULL_PTR; 
       }	
    /* Step 2: Check for zero count (invalid operation) */
       if(count == 0){
       	return ERR_INVALID_ARG; 
       }
    /* Step 3: Check bounds - will count fit in dest? */
       if(count > dest_size){
       	return ERR_OUT_OF_BOUNDS; 
       }
    /* Step 4: Perform the copy */
       memcpy(dest, src, count);
       return ERR_OK; 
}

void test_exercise_3(void) {
    TEST_SECTION("EXERCISE 3: safe_memcpy");
    
    char dest[20];
    const char *src = "Hello, World!";
    error_t err;
    
    /* Normal copy */
    memset(dest, 0, sizeof(dest));
    err = safe_memcpy(dest, sizeof(dest), src, 13);
    CHECK(err == ERR_OK && strcmp(dest, "Hello, World!") == 0, 
          "Normal copy works");
    
    /* Exact fit */
    char small[5];
    err = safe_memcpy(small, sizeof(small), "test", 4);
    CHECK(err == ERR_OK && memcmp(small, "test", 4) == 0,
          "Exact fit copy works");
    
    /* Error cases */
    err = safe_memcpy(NULL, 20, src, 5);
    CHECK(err == ERR_NULL_PTR, "NULL dest returns ERR_NULL_PTR");
    
    err = safe_memcpy(dest, 20, NULL, 5);
    CHECK(err == ERR_NULL_PTR, "NULL src returns ERR_NULL_PTR");
    
    err = safe_memcpy(dest, 5, src, 13);
    CHECK(err == ERR_OUT_OF_BOUNDS, "Copy too large returns ERR_OUT_OF_BOUNDS");
    
    err = safe_memcpy(dest, 20, src, 0);
    CHECK(err == ERR_INVALID_ARG, "Zero count returns ERR_INVALID_ARG");
}

/* ═══════════════════════════════════════════════════════════════════════════
 * EXERCISE 4: SAFE ARRAY FIND (★★★★☆)
 * 
 * Implement a search function for SafeArray that finds the first occurrence
 * of a value and returns its index.
 * 
 * Preconditions:
 *   - arr must not be NULL
 *   - arr must be initialized (data != NULL)
 *   - out_index must not be NULL
 * 
 * Postconditions:
 *   - Returns ERR_OK if value found, writes index to *out_index
 *   - Returns ERR_NULL_PTR if arr or out_index is NULL
 *   - Returns ERR_UNINITIALIZED if arr->data is NULL
 *   - Returns ERR_INVALID_ARG if value not found (not really an error,
 *     but we need to signal "not found" somehow)
 * 
 * BOSS CHALLENGE: Also implement safe_array_find_all that returns a new
 * SafeArray containing ALL indices where value appears.
 * ═══════════════════════════════════════════════════════════════════════════ */

error_t safe_array_find(const SafeArray *arr, int value, size_t *out_index) { 
    /* Step 1: Validate arr pointer */
	if(arr == NULL){
	 return ERR_NULL_PTR; 
	}

    /* Step 2: Validate arr is initialized */
	if(arr->data == NULL){
	 return ERR_UNINITIALIZED; 
	}
    /* Step 3: Validate out_index pointer */
        if(out_index == NULL){
	 return ERR_NULL_PTR; 
	}
    /* Step 4: Linear search through arr->data[0..length) */
        for(size_t i = 0; i < arr -> length; i++){
	  if(arr->data[i] == value){
	     *out_index = i; 
	     return ERR_OK; 
	  }
	}
    /* Step 5: If not found, return ERR_INVALID_ARG (or could define ERR_NOT_FOUND) */
	return ERR_INVALID_ARG; 
}

/* BOSS CHALLENGE: Implement this for extra XP! */
error_t safe_array_find_all(const SafeArray *arr, int value, SafeArray *results) {
    /* TODO: Implement this for +200 bonus XP */
    (void)arr; (void)value; (void)results;
    return ERR_UNINITIALIZED;
}

void test_exercise_4(void) {
    TEST_SECTION("EXERCISE 4: safe_array_find");
    
    SafeArray arr = SAFE_ARRAY_INIT;
    size_t index;
    error_t err;
    
    /* Setup test array: [10, 20, 30, 20, 40, 20] */
    safe_array_create(&arr, 8);
    safe_array_push(&arr, 10);
    safe_array_push(&arr, 20);
    safe_array_push(&arr, 30);
    safe_array_push(&arr, 20);
    safe_array_push(&arr, 40);
    safe_array_push(&arr, 20);
    
    /* Find existing values */
    err = safe_array_find(&arr, 10, &index);
    CHECK(err == ERR_OK && index == 0, "Find 10 returns index 0");
    
    err = safe_array_find(&arr, 20, &index);
    CHECK(err == ERR_OK && index == 1, "Find 20 returns first occurrence (index 1)");
    
    err = safe_array_find(&arr, 40, &index);
    CHECK(err == ERR_OK && index == 4, "Find 40 returns index 4");
    
    /* Not found */
    err = safe_array_find(&arr, 99, &index);
    CHECK(err == ERR_INVALID_ARG, "Find 99 (not in array) returns not-found");
    
    /* Error cases */
    err = safe_array_find(NULL, 10, &index);
    CHECK(err == ERR_NULL_PTR, "NULL arr returns ERR_NULL_PTR");
    
    err = safe_array_find(&arr, 10, NULL);
    CHECK(err == ERR_NULL_PTR, "NULL out_index returns ERR_NULL_PTR");
    
    SafeArray empty = SAFE_ARRAY_INIT;
    err = safe_array_find(&empty, 10, &index);
    CHECK(err == ERR_UNINITIALIZED, "Uninitialized array returns ERR_UNINITIALIZED");
    
    safe_array_destroy(&arr);
    
    /* BOSS CHALLENGE TEST (uncomment when implemented) */
    /*
    SafeArray arr2 = SAFE_ARRAY_INIT;
    SafeArray indices = SAFE_ARRAY_INIT;
    
    safe_array_create(&arr2, 8);
    for (int i = 0; i < 6; i++) {
        safe_array_push(&arr2, (i % 2 == 0) ? 42 : 99);
    }
    // arr2: [42, 99, 42, 99, 42, 99]
    
    err = safe_array_find_all(&arr2, 42, &indices);
    CHECK(err == ERR_OK && indices.length == 3, "find_all returns 3 indices for 42");
    
    int idx;
    safe_array_get(&indices, 0, &idx);
    CHECK(idx == 0, "First 42 at index 0");
    safe_array_get(&indices, 1, &idx);
    CHECK(idx == 2, "Second 42 at index 2");
    safe_array_get(&indices, 2, &idx);
    CHECK(idx == 4, "Third 42 at index 4");
    
    safe_array_destroy(&arr2);
    safe_array_destroy(&indices);
    */
}

/* ═══════════════════════════════════════════════════════════════════════════
 * MAIN
 * ═══════════════════════════════════════════════════════════════════════════ */

int main(void) {
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  HUNTER PROTOCOL 2.0 — DAY 9: SHADOW QUESTS                   ║\n");
    printf("║  \"Errors handled are battles won.\"                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    test_exercise_1();
    test_exercise_2();
    test_exercise_3();
    test_exercise_4();
    
    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("  SHADOW QUEST RESULTS: %d passed, %d failed\n", tests_passed, tests_failed);
    printf("═══════════════════════════════════════════════════════════════════\n");
    
    if (tests_failed == 0) {
        printf("\n  🔥 SHADOW LORD DEFEATED! +1000 XP 🔥\n");
        printf("  RANK UP: E+ → D-\n\n");
    } else {
        printf("\n  YOU DIED. %d challenges remain. Respawn and retry.\n\n", tests_failed);
    }
    
    return 0;
}

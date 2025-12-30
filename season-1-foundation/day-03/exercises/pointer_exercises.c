/*
 * pointer_exercises.c — Day 3 Pointer Arithmetic Trials
 * Hunter Protocol: Season 1
 * 
 * Rules:
 *   - No [] operator in exercises 1 and 2
 *   - Always pass size_t len with arrays
 *   - Use const where not modifying
 *   - Compile: gcc -Wall -Wextra -std=c17 -o exercises pointer_exercises.c
 *   - Zero warnings allowed
 */

#include <stdio.h>
#include <stddef.h>   /* for size_t */
#include <stdbool.h>  /* for bool */

/* ========================================================================
 * EXERCISE 1: Reverse Array In-Place
 * 
 * Two pointers: one at start, one at end.
 * Swap, then walk toward each other.
 * NO [] operator allowed.
 * ======================================================================== */
void reverse_array(int *arr, size_t len)
{
	if (arr == NULL) return;
	if (len == 0) return; 
	int *left = arr; 
	int *right = arr + len - 1; 
	int temp = 0; 

	while(left < right){
	temp = *left; 
	*left = *right; 
	*right = temp; 
	
	left++; 
	right --; 
	}
}

/* ========================================================================
 * EXERCISE 2: Find Maximum (Return Pointer)
 * 
 * Return a POINTER to the max element, not the value.
 * NO [] operator allowed.
 * ======================================================================== */
int *find_max(int *arr, size_t len)
{
	if (arr == NULL) return NULL; 
	if (len == 0) return NULL; 
	int *max; 
	max = arr; 

	for(size_t i = 0; i < len; i++){
		if(*(arr + i) > *max){
			max = arr + i; 
		}

	}
	return max; 
}

/* ========================================================================
 * EXERCISE 3: Array Equality Check
 * 
 * Return true if arrays have same elements in same order.
 * Use const — you're promising not to modify.
 * ======================================================================== */
bool arrays_equal(const int *a, const int *b, size_t len)
{
	if (a == NULL || b == NULL) return false; 
	if (len == 0) return false; 
	
	for(size_t i = 0; i < len; i++){
		if(a[i] != b[i]) return false; 
	}
   return true; 
}

/* ========================================================================
 * EXERCISE 4: Pointer Distance Calculator
 * 
 * Prove: pointer subtraction gives element count, not bytes.
 * ======================================================================== */
void pointer_distance_demo(void)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t len = 10; 
    int *first_element = arr; 
    int *second_element = arr + len - 1;
    ptrdiff_t distance = second_element - first_element; 

    printf("Distance between first and last element: %td\n", distance);
    printf("Expected (len - 1): %zu\n", len - 1);

    if(distance == (ptrdiff_t)(len - 1)){puts("Success");}
    /* Get pointers to first and last elements */
    /* Calculate distance using pointer subtraction */
    /* Verify it equals (len - 1) */
}

/* ========================================================================
 * TEST HARNESS
 * ======================================================================== */
int main(void)
{
    /* Test Exercise 1 */
    printf("=== Exercise 1: Reverse Array ===\n");
    int arr1[] = {1, 2, 3, 4, 5};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Before: ");
    for (size_t i = 0; i < len1; i++) printf("%d ", arr1[i]);
    printf("\n");
    
    reverse_array(arr1, len1);
    
    printf("After:  ");
    for (size_t i = 0; i < len1; i++) printf("%d ", arr1[i]);
    printf("\n\n");
    
    /* Test Exercise 2 */
    printf("=== Exercise 2: Find Maximum ===\n");
    int arr2[] = {10, 45, 23, 78, 5};
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int *max_ptr = find_max(arr2, len2);
    if (max_ptr != NULL) {
        printf("Max value: %d at address: %p\n\n", *max_ptr, (void *)max_ptr);
    }
    
    /* Test Exercise 3 */
    printf("=== Exercise 3: Array Equality ===\n");
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {1, 2, 3, 4, 6};
    size_t len3 = 5;
    
    printf("a == b: %s\n", arrays_equal(a, b, len3) ? "true" : "false");
    printf("a == c: %s\n\n", arrays_equal(a, c, len3) ? "true" : "false");
    
    /* Test Exercise 4 */
    printf("=== Exercise 4: Pointer Distance ===\n");
    pointer_distance_demo();
    
    return 0;
}

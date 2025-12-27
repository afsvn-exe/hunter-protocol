/* 
* Hunter Protocol 2.0 - Day 3 
* array_pointer_demo.c 
* 
* Purpose: Demonstrate the relationship between arrays and pointers. 
* Insight: Array names dacay into a pointer to its first element.
*	   Array indexing is syntactic sugar for pointer arithmetic.
*/

#include <stdio.h>
#include <stdlib.h>

void print_size(int arr[]){
	printf("Inside function: sizeof(arr) = %zu\n", sizeof(arr));
}

int main(void){
	int scores[5] = {10, 20, 30, 40, 50};
	
	puts("=== PART 1: Memory Layout ===\n");
	for (int i = 0; i < 5; i++){
	    printf("scores[%d] = %2d | Address: %p\n", i, scores[i], (void *)&scores[i]);	
	}
	
	printf("\nsizeof(int) = %zu bytes\n", sizeof(int));
	printf("Address difference between elements: %zu bytes\n",(size_t)(&scores[1] - &scores[0])*sizeof(int));
	
	puts("\n=== PART 2: Array-Pointer Relationship ===\n");
	
	/* These addresses are the same */
	
	printf("Address of scores[0]: %p\n", (void *)&scores[0]);
	printf("Address of scores: %p\n", (void *)&scores);	
 	
	/* The name of the array is the pointer to the first element */
	
	printf("Are they equivalent? %s\n", (scores == &scores[0] ? "YES" : "NO"));

	puts("\n=== PART 3: Pointer Arithmetic - Walking the Ladder ===\n");
	
	/* When you add 1 to a pointer, you are adding sizeof(datatype pointed to)*/
	
	int *ptr = scores; 
	printf("ptr starts at:	   %p (value: %d)\n", (void *)ptr, *ptr);
	printf("ptr + 1 points to: %p (value: %d)\n", (void *)(ptr + 1), *(ptr + 1));
	printf("ptr + 2 points to: %p (value: %d)\n", (void *)(ptr + 2), *(ptr + 2));
	printf("ptr + 3 points to: %p (value: %d)\n", (void *)(ptr + 3), *(ptr + 3));
	printf("ptr + 4 points to: %p (value: %d)\n", (void *)(ptr + 4), *(ptr + 4)); 

	puts("\n=== PART 4: Sacred Equivalence ===\n");
	
	/*
	 * array[i] is exactly the same as *(array + i)
	 * the [] operator is pointer arithmetic + dereference 
	*/
	
	puts("Proving: array[i] == *(array + i)");
	for(int i = 0; i < 5; i++){
		printf("scores[%d] == %d | *(scores + %d) = %d | Match: %s\n", 
		i, scores[i], i, *(scores + i), (scores[i] == *(scores + i)) ? "YES" : "NO");
	} 
	
	puts("\n=== PART 5: The Danger Zone (Array Out-of-Bounds) ===\n");
	
	printf("Array size: %lu elements\n", sizeof(scores)/sizeof(scores[0]));
	printf("scores[4] = %d (last valid element)\n", scores[4]); 
	printf("scores[5] = ??? (UNDEFINED BEHAVIOR - READING GARBAGE)\n");
	/*printf("scores[5] = %d (UNDEFINED BEHAVIOR - READING GARBAGE)\n", scores[5]);*/

	puts("\n=== PART 6: The Divergence ===\n");
	
	printf("sizeof(scores) = %zu bytes\n", sizeof(scores)); 
	printf("sizeof(ptr) = %zu bytes\n", sizeof(ptr)); 
	
	puts("\n=== PART 7: The Decay (Passing Arrays to Functions)");
	
	printf("Outside function: sizeof(scores) = %zu bytes\n", sizeof(scores));
	print_size(scores);
	puts("[!] Arrays decay to pointers when passed. Size is LOST");
	puts("	  Always pass size as a separate parameter.");	

	return EXIT_SUCCESS; 

}

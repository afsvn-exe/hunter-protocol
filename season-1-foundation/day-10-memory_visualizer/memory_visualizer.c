// memory_visualizer.c
// Purpose: Demonstrate memory layout by printing addresses from each region

#include <stdio.h>
#include <stdlib.h>

// ══════════════════════════════════════════════════════════
// ATOM 3 & 4: Global variables (Data & BSS segments)
// ══════════════════════════════════════════════════════════
int global_init = 5; 
int global_uninit; 

// ══════════════════════════════════════════════════════════
// ATOM 5: A function whose address we can print (TEXT segment)
// ══════════════════════════════════════════════════════════
void helper_function(void) {
    // Empty — we just want its address
}

int main(void) {
    // ══════════════════════════════════════════════════════
    // ATOM 1: Stack variables
    // ══════════════════════════════════════════════════════
    // OBSERVE: Which direction does the stack grow?
	int local_a = 1;  
	int local_b = 2; 
	static int static_local = 42; 
	int arr[4] = {10, 20, 30, 40};

	puts("=== STACK ===");
	printf("local_a: %p\n", (void *)&local_a);
	printf("local_b: %p\n",(void *)&local_b); 
	
	puts("=== STATIC LOCAL ===");
	printf("static_local: %p\n",(void *)&static_local);

	puts("=== ARRAY CONTIGUITY ===");
	for(int i = 0; i < 4; i++){
		printf("arr[%d]: %p (value: %d)\n", i, (void *)&arr[i], arr[i]);
	}
    // ══════════════════════════════════════════════════════
    // ATOM 2: Heap allocations
    // ══════════════════════════════════════════════════════
    // OBSERVE: Which direction does the heap grow?
    
	int *malloc_1 = malloc(sizeof(int)*4);
	int *malloc_2 = malloc(sizeof(int)*4); 
	puts("=== HEAP ===");
	printf("malloc_1: %p\n", malloc_1);
	printf("malloc_2: %p\n", malloc_2);
	
	puts("=== REGION DISTANCES ===");
	printf("Stack to Heap gap: %td bytes\n", (char *)&local_a - (char *)malloc_1);
	printf("Heap to Data gap: %td bytes\n", (char *)malloc_1 - (char *)&global_init);
	printf("Data to Text gap: %td bytes\n", (char *)&global_init - (char *)main); 

	free(malloc_1); 
	malloc_1 = NULL; 
	free(malloc_2);
	malloc_2 = NULL; 


    // ══════════════════════════════════════════════════════
    // ATOM 3 & 4: Print global/static addresses
    // ══════════════════════════════════════════════════════
	puts("=== DATA ===");
	printf("global_init: %p\n", (void *)&global_init);
	puts("=== BSS ===");
	printf("global_uninit: %p\n", (void *)&global_uninit);
    // ══════════════════════════════════════════════════════
    // ATOM 5: Text segment (function addresses)
    // ══════════════════════════════════════════════════════
    	puts("=== TEXT ===");
	printf("main: %p\n", (void *)&main); 
	printf("helper_function: %p\n", (void *)&helper_function); 

    return 0;
}

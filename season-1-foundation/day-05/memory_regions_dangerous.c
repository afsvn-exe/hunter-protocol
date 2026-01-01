/*
* Day-05: Visualizing Memory Addresses - DANGEROUS version
*/
#include <stdio.h>
#include <stdlib.h>

int g_initialized = 42; /*DATA - stores initialized variables*/
int g_uninitialized; /*BSS - stores uninitialized variables*/

void show_stack_address(void){
     int stack_var = 100; 
     printf("Stack (inside function): %p\n", (void*)&stack_var);
}

int *dangerous_function(void){
    int local = 777; 
    printf("Inside Function, local = %d at %p\n", local, (void *)&local);
    return &local; /*WARNING: returning address of local variable*/ 
}

void clobber_stack(void){
     int a = 111, b = 222, c = 333, d = 444; 
     printf("Clobbering stack: %d %d %d %d\n", a, b, c, d);
}

int main(void){
    int stack_var = 10; 
    int *heap_ptr = malloc(sizeof(heap_ptr));

    puts("=== MEMORY ADDRESSES ===");
    puts("\n[TEXT - Code]");
    printf("main() function: %p\n", (void *)&main);

    puts("\n[DATA - Initialized Globals]");
    printf("g_initialized: %p\n", (void *)&g_initialized);

    puts("\n[BSS - Uninitialized Globals]");
    printf("g_uninitialized: %p\n", (void *)&g_uninitialized);

    puts("\n[HEAP - Dynamic Allocation]");
    printf("heap_ptr: %p\n", (void *)&heap_ptr);

    puts("\n[STACK - Local Variables]");
    printf("stack_var: %p\n", (void *)&stack_var);
    show_stack_address();
    
    printf("\n[DANGER ZONE]");
    int *bad_ptr = dangerous_function(); 
    clobber_stack();
    printf("After return, *bad_ptr = %d\n", *bad_ptr);

    free(heap_ptr); 
    
    return EXIT_SUCCESS;
}

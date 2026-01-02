/*
* Day 6: Manual memory management with malloc/realloc/free 
*/

#include <stdio.h>
#include <stdlib.h> 

int main(void){
    size_t capacity = 4; 
    size_t size = 0; 
    
    /*Allocate initial array*/
    int *arr = malloc(capacity * sizeof(int));
    if(arr == NULL){
       fprintf(stderr, "malloc failed\n");
       return EXIT_FAILURE; 
    }
    printf("Allocated %zu slots at %p\n", capacity, (void *)arr);
    
    for(int i = 1; i <= 10; i++){
	if(size == capacity){
	   capacity *= 2; 
   	   printf("Growing %zu slots... ", capacity);

	   int *temp = realloc(arr, capacity * sizeof(int));
	   if(temp == NULL){
	      fprintf(stderr, "realloc failed\n"); 
	      free(arr); 
	      return 1; 
	   }
	   arr = temp; 
	   printf("now at %p\n", (void *)arr);
	}
	arr[size] = i * 10; 
	size++; 
    }
    printf("\nArray contents (%zu elements)\n", size);
    for (size_t i = 0; i < size; i++){
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    free(arr); 
    arr = NULL; 
    puts("\nMemory Freed.");
    return EXIT_SUCCESS; 
}

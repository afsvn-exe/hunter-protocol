#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

void swap(int32_t *pA, int32_t *pB){

	int32_t temp; 
	temp = *pA;
	*pA = *pB; 
	*pB = temp; 
} 


int main(void){
	int32_t a = 10; 
	int32_t b = 20; 

	printf("Before: a = %d, b = %d\n", a, b);

	swap(&a, &b);

	printf("After: a = %d, b = %d\n", a, b);

	return EXIT_SUCCESS;  

}

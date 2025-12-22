#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*Exercise 1.1 Fixed-Width Types*/

int main(void){

	uint8_t num1; 
	uint16_t num2; 
	uint32_t num3; 
	uint64_t num4; 


	printf("Size of uint8_t: %zu bytes\n", sizeof(num1));
        printf("Size of uint16_t: %zu bytes\n", sizeof(num2)); 
	printf("Size of uint32_t: %zu bytes\n", sizeof(num3));
 	printf("Size of uint64_t: %zu bytes\n", sizeof(num4)); 	


	return EXIT_SUCCESS; 
}

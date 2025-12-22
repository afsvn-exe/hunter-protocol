#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

/*Exercise 1.3: Endianness - Store 0xDEADBEEF in a uint32_t. Cast its address to uint8_t * and print each byte*/

int main(void){

	uint32_t beef = 0xDEADBEEF;
	uint8_t *ptr = (uint8_t *)&beef;

	for(size_t i = 0; i < sizeof(beef); i++){
		printf(" %02x ", ptr[i]);
	}

	return EXIT_SUCCESS;



}

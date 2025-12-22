#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void){
	puts("=== Day 1: Memory Model ===\n\n");

	/*Section 1: Variables have addresses*/
	int x = 42; 
	printf("Variable x\n");
	printf("Value: %d\n", x);
	printf("Address: %p\n", (void *)&x);
	printf("Size: %zu\n", sizeof(x));

	/*Section 2: Different types and sizes*/
	char c = 'A';
	short s = 1000; 
	long l = 123456789L;

	puts("Type sizes on this system:\n");
	printf("char: %zu bytes (c = '%c' at %p)\n", sizeof(char), c, (void *)&c);
	printf("short: %zu bytes (s = '%d' at %p)\n", sizeof(short), s, (void *)&s);
	printf("int: %zu bytes\n", sizeof(int));
	printf("long: %zu bytes (l = '%ld' at %p)\n", sizeof(long), l, (void *)&l);
	printf("pointer: %zu bytes\n\n", sizeof(void *));

	/*Section 3: Addresses are sequential*/
	int num[4] = {10, 20, 30, 40};
	for(int i = 0; i < 4; i++){
		printf("num[%d] = %2d at address %p\n", i, num[i], (void *)&num[i]);
	}
	printf("\n");

	/*Section 4: The pointer - a variable that holds an address*/
	int *ptr = &x; 
	printf("ptr holds the address: %p\n", (void *)ptr);
	printf("*ptr dereferences to: %d\n", *ptr); 
	printf("ptr itself lives at: %p\n\n", (void *)&ptr);

	/*Section 5: Modifying through a pointer*/
	printf("Modifying x through ptr...\n");
	printf("Before: x = %d\n", x);
	*ptr = 99; 
	printf("After: x = %d\n\n", x);
	printf("End of Day 1\n");

	return EXIT_SUCCESS;
	
}

#include <stdio.h>
#include <stdlib.h>

void level_up_broken(int32_t power){
	power += 10; 
	printf("Inside function: %d\n", power);
}

void level_up_works(int32_t *power){
	*power += 10; 
	printf("Inside function: %d\n", *power);
}

int main(void){
	int32_t hunter = 50; 

	printf("=== Broken (pass by value)===\n");
	printf("Before: %d\n", hunter);
	level_up_broken(hunter);
	printf("After: %d\n", hunter);

	printf("\n=== Works (pass by pointer)===\n");
	printf("Before: %d\n", hunter);
	level_up_works(&hunter);
	printf("After: %d\n", hunter);

	return EXIT_SUCCESS;

}

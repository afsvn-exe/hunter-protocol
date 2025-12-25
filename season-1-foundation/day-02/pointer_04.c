#include <stdio.h>
#include <stdlib.h> 

void level_up(int32_t *power){
	*power += 10; 
}

int main(void){
	int32_t hunter_power = 50; 
	printf("Before: %d\n", hunter_power);

	level_up(&hunter_power);

	printf("After: %d\n", hunter_power);

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*Exercise 1.2 - Address Arithmetic: calculate the byte offset between &nums[0] and &nums[4]*/


int main(void){

	int num[5] = {10, 20, 30, 40, 50};
	printf("%td\n", (char *)&num[4] - (char *)&num[0]);

	return EXIT_SUCCESS; 
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *Day 8: The Four Horsemen of Undefined Behavior 
 *WARNING: Code is intentionally vulnerable to demonstrate their impact!
 */

void buffer_overflow(void){
	/*What happens when you write beyond allocated bounds?*/
	int *arr = malloc(sizeof(int)*5); 
	if(arr == NULL){
		return ;
	}
	for(size_t i = 0; i <= 5; i++){
		arr[i] = i; 
	}
	free(arr);

}

void use_after_free(){
	char *str = malloc(sizeof(char) * 32);
	if(str == NULL){
		return ;
	}
	strcpy(str, "This is a vulnerability");
	free(str); 
	printf("Trying to print after freed %s\n", str);
	strcpy(str, "Attempt after free");
}

void memory_leak(void){
	for(int i = 0; i < 5; i++){
		char *vuln = malloc(1024);
		if(vuln == NULL){
		  return ;
		}

		vuln[0] = 'A'; 
	}
}

void double_free(void){
	char *df_vuln = malloc(64);
	if(df_vuln == NULL){
		return; 
	}
	strcpy(df_vuln, "super vuln");
	free(df_vuln);
	free(df_vuln);
}

int main(void){
	buffer_overflow(); 
	use_after_free(); 
	memory_leak();
	double_free();
	return EXIT_SUCCESS;

}

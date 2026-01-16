#include <stdio.h>
#include <stddef.h> 

size_t safe_copy(char *dest, const char *src, size_t dest_size){
	
	if(dest == 0){
	   return 0;
	}
	
	size_t i = 0; 
	while(src[i] != '\0' && i < dest_size - 1){
	    dest[i] = src[i]; 
	    i++; 
	}
	dest[i] = '\0'; 

	return i; 
}

int main(void){
	char buffer[8]; 
	size_t copied; 

	// Test 1: Normal Copy
	copied = safe_copy(buffer, "hello", 8); 
	printf("Test 1: \"%s\" (copied %zu)\n", buffer, copied);
	
	// Test 2: Truncation 
	copied = safe_copy(buffer, "Hello, World!!", 8);
	printf("Test 2: \"%s\" (copied %zu)\n", buffer, copied);

	// Test 3: Empty source 
	copied = safe_copy(buffer, "", 8);
	printf("Test 3: \"%s\" (copied %zu)\n", buffer, copied);

	return 0; 	
}

#include <stdio.h>
#include <stddef.h>

size_t safe_concat(char *dest, const char *src, size_t dest_size){
	if(dest_size == 0){
		return 0; 
	}
	
	size_t dest_len = 0; 
	while(dest[dest_len] != '\0'){
		dest_len++; 
	}

	if(dest_len >= dest_size - 1){
		return dest_len; 
	}

	size_t i = 0; 
	while(src[i] != '\0' && dest_len + i < dest_size - 1){
		dest[dest_len + i] = src[i]; 
		i++; 
	}
	dest[dest_len + i] = '\0'; 

	return dest_len + i; 
}


int main(void){

	char buffer[12] = "Hello";
	size_t len; 

	// Test 1: Normal concat
	len = safe_concat(buffer, " World", 12);
	printf("Test 1: \"%s\" (len %zu)\n", buffer, len);
        
	//Test 2: Truncation
	char small[8] = "Hi"; 
	len = safe_concat(small, " World!", 8);
	printf("Test 2: \"%s\" (len %zu)\n", small, len);
	
	//Test 3: Empty Append
	char empty_test[8] = "Test"; 
	len = safe_concat(empty_test, "", 8); 
	printf("Test 3: \"%s\" (len %zu)\n", empty_test, len);

	return 0;	
}

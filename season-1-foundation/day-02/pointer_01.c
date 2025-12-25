#include <stdio.h>
#include <stdlib.h>

int main(void){
    int32_t treasure = 42; 
    
    printf("Value of treasure: %d\n", treasure);
    printf("Address of treasure: %p\n", (void *)&treasure);

    return EXIT_SUCCESS; 
}

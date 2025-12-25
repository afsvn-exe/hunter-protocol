#include <stdio.h>
#include <stdlib.h>

int main(void){
    int32_t treasure = 42; 
    int32_t *map = &treasure; 

    printf("Before: treasure = %d\n", treasure);
    
    *map = 100; 

    printf("After: treasure = %d\n", treasure);

    return EXIT_SUCCESS;

}

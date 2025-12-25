#include <stdio.h>
#include <stdlib.h>

int main(void){
    int32_t treasure = 42; 
    int32_t *map = &treasure; 

    printf("Value of treasure: %d\n", treasure);
    printf("Address of treasure: %p\n", (void *)&treasure);
    printf("Value of map: %p\n", (void *)map);
    printf("What map points to: %d\n", *map);

    return EXIT_SUCCESS;

}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

#define ARRAY_SIZE 64

int main(void) {
    int array[ARRAY_SIZE] = {0};                        // array allocated on the stack
    int *ptr = (int*) malloc(ARRAY_SIZE * sizeof(int)); // array allocated on the heap

    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("The array is located in memory in the range %p - %p\n", (void*)&array[0], (void*)&array[ARRAY_SIZE]);
    // TODO: Print the memory range of the array allocated on the heap
    printf("The malloc-ed array is located in memory in the range %p - %p\n", (void*)ptr, (void*)((char*)ptr + ARRAY_SIZE * sizeof(int)));  // Cast to char* for byte arithmetic
    
    free(ptr);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(void) {
    printf("How many integers should be allocated on the heap? ");
    int size = read_int();
    while (size < 0) {
        printf("The size must be non-negative. Try again: ");
        size = read_int();
    }

    int *ptr = (int*) malloc(size * sizeof(int)); // allocate memory to store integers //size * sizeof(int) to ensure enough memory is allocated for size integers.
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Memory allocated successfully\nFilling array with random integers...\n");
    
    for (int i = 0; i < size; i++) {
        ptr[i] = random_int(0, 100);
    }
    free(ptr); // if missing could lead to memory leak
    return 0;
}

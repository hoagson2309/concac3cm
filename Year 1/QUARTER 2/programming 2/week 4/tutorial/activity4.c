#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(void) {
    printf("How many bytes of memory should be allocated on the heap? ");
    int size = read_int();
    while (size < 0) {
        printf("The size must be non-negative. Try again: ");
        size = read_int();
    }
    void *ptr = malloc(size); // allocate memory

    if (ptr != NULL) {
        printf("Memory allocated on the heap in the range %p - %p\n", ptr, (char*) ptr + size - 1);
    } else {
        printf("Memory allocation failed\n");
    }
}

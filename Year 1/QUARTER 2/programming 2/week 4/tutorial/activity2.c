#include <stdio.h>
#include <string.h>
#include "functions.h"

#define ARRAY_SIZE 1024

void recursive_function(int n, int max_depth) {
    int values[ARRAY_SIZE]; // allocate 4KB of memory on the stack (assuming an integer is 4 bytes)

    if (n >= max_depth) {
        return; // stop recursion, unwind the call stack
    }

    // Do something "useful" with the array
    for (int i = 0; i < 1024; i++) {
        values[i] = i;
    }

    printf("n = %2d - values stored in memory in range %p - %p\n", n, (void*) &values[0], (void*) &values[ARRAY_SIZE]);
    recursive_function(n + 1, max_depth);
}

int main(void) {
    printf("This program demonstrates the stack memory usage of recursive functions.\n");
    printf("What should be the maximum depth of the recursion? ");
    int max_depth = read_int();
    recursive_function(0, max_depth);
}

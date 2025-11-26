#include <stdio.h>

int main() {
    int x;
    int y[5];

    printf("Size of an integer: %zu\n", sizeof(x));
    printf("Size of an array of 5 integers: %zu\n", sizeof(y));

    return 0;
}
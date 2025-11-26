#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the number of rows: ");
    int rows = read_int();

    // TODO: include code to print a 5x5 grid of numbers
    int a = 1;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            printf("%3d", a);
            a++;
        }
        printf("\n");  
    }
    return 0;
}
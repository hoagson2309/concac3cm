#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the number of rows: ");
    int rows = read_int();
    for (int i = rows; i >= 1; i--) {
        // print the i-th row of the triangle
        for (int j = i; j >= 1; j--) {
            // print an asterisk
            printf("%3d", j);
        }
        printf("\n");   // newline after each row
    }

    return 0;
}
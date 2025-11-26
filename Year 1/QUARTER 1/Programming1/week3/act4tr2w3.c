#include <stdio.h>      // for printf
#include "functions.h"  // for random_int

int main(void) {
    int count = 0;
    printf("enter number: ");
        int number = read_int();  
    for (int i = 0; i < number; i++) {
        int a = random_int(1, 6);
        if (a == 6) {
            count++;
        }
    }
    printf("Number of sixes: %d\n", count);

    return 0;
}
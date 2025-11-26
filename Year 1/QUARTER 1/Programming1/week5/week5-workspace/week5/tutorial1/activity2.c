#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number[10];
    for(int i = 0; i < 10; i++){
        number[i] = read_int();
    }
    for(int i = 0; i < 10; i++){
    printf("You entered the numbers: %d\n", number[i]);
    }
    return 0;
}

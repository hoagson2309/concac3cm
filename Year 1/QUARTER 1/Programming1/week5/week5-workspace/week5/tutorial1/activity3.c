#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number[100];
    int count = 0;
    printf("Enter the numbers: ");
    int numberss = read_int();
    while (numberss > 0) {
        number[count] = numberss;
        count++;
        printf("Enter the numbers: ");
        numberss = read_int();
    }
    for(int i = 0; i < count; i++){
    printf("You entered the numbers: %d\n", number[i]);
    }
    return 0;
}

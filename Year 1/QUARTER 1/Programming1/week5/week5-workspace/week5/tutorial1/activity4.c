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
    printf("%d", number[0]);
    for(int i = 1; i < count; i++){
    printf(", %d", number[i]);
    }
    printf(".\n");
    return 0;
}

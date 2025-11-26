#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number[100];
    int count = 0;
    bool printed_first = false;
    printf("Enter the numbers: ");
    int numberss = read_int();
    while (numberss > 0) {
        number[count] = numberss;
        count++;
        printf("Enter the numbers: ");
        numberss = read_int();
    }
    printf("You entered the following values: ");
    for(int i = 0; i < count; i++) {
        if (number[i] > 5) {
        if (printed_first) printf(", ");    // print separator if not the first number
        printed_first = true;               // the first number has been printed
        printf("%d", number[i]);
        }
    }
        printf(".\n");
    return 0;
}

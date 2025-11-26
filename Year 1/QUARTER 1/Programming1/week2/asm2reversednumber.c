#include <stdio.h>
#include "functions.h"

int main() {
    printf("Please enter a three-digit number: ");
    int num = read_int();
    if (num < 100 || num > 999) {
        printf("Sorry, that's not a three-digit number! Aborting...\n");
        return 1; 
    }
    
    int orgNum = num;
    int reversed = 0;
    
    while (num > 0) {
        int digit = num % 10;
        reversed = reversed * 10 + digit;
        num /= 10;
    } 
    printf("The reverse of %d is %03d.\n", orgNum, reversed);

    return 0;
}
    

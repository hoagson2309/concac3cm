#include <stdio.h>     
#include "functions.h"
int read_number(void){
    printf("Enter a number between 1 and 10: ");
    int number = read_int();
    while (number < 1 || number > 10) {
        printf("The number must be between 1 and 10, try again!\n");
        printf("Enter a number between 1 and 10: ");
        number = read_int();
    }
    return number;
}

int main(void) {
    int number = read_number();
    printf("You entered the number %d\n", number);
    return 0;
}
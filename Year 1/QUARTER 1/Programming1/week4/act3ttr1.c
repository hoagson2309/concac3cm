#include <stdio.h>     
#include "functions.h"
int read_number(int min, int max){
    printf("Enter the number between %d and %d: ", min, max);
    int number = read_int();
    while(number < min || number > max){
        printf("Please try again!\n");
        printf("Enter the number between %d and %d: ", min, max);
        number = read_int();
    }
    return number;
}

int main(void) {
    int number = read_number(1, 10);
    printf("You entered the number %d\n", number);
    number = read_number(10, 20);
    printf("You entered the number %d\n", number);
    number = read_number(-42, 42);
    printf("You entered the number %d\n", number);
    return 0;
}
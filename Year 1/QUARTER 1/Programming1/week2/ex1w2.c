#include <stdio.h>
#include "functions.h"

int main(void)
{
    printf("Please enter the first number: ");
    int number1 = read_int();
    printf("Please enter the second number: ");
    int number2 = read_int();
    int product = number1 * number2;
    printf("The product of %d and %d is %d.\n", number1, number2, product);
    return 0;
}


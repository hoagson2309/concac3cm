#include <stdio.h>
#include "functions.h"
int main(void)
{
    printf("Enter the first number: ");
    int a = read_int();
    printf("Enter the second number: ");
    int b = read_int();
    int sum = a + b;
    printf("The sum of %d and %d is %d\n", a, b, sum);
    return 0;
}
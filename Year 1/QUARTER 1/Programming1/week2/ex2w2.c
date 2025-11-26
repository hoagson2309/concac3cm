#include <stdio.h>
#include "functions.h"

int main(void)
{
    printf("Please enter the first number: ");
    float number1 = read_float();
    printf("Please enter the second number: ");
    float number2 = read_float();
    float quotient = number1 / number2;
    printf("The quotient of %.2f and %.2f is %.2f.\n", number1, number2, quotient);
    return 0;
}

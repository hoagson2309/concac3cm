#include <stdio.h>     // for printf
#include "functions.h" // for read_int

int main(void)
{
    printf("Enter a positive odd number: ");
    int number = read_int();
    while (number % 2 == 0 || number < 1)
    {
        printf("That's even or negative, please enter a positive odd number: ");
        number = read_int();
    }

    int i, sum = 0;
    for (i = 1; i <= number; i += 2)
    {
        sum += i;
    }
    printf("The sum of odd numbers from 1 to %d is: %d\n", number, sum);

    return 0;
}
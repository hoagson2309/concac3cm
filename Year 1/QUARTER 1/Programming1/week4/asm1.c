#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "functions.h"
//Function to check valid operators.
char read_operator(void)
{
    printf("Please enter an operator (+, -, *, /, ^): ");
    char op = read_char();
    while (op != '+' && op != '-' && op != '*' && op != '/' && op != '^'){
            printf("Invalid operator. Please try again.\n");
            printf("Please enter an operator (+, -, *, /, ^): ");
            op = read_char();
        } 
    return op;
}
// CALCULATOR.
float apply_operator(float num1, float num2, char op)
{
    float res;
    switch (op)
    {
    case '+':
        res = num1 + num2;
        break;
    case '-':
        res = num1 - num2;
        break;
    case '*':
        res = num1 * num2;
        break;
    case '/':
        if (num2 != 0)
        {
            res = num1 / num2;
        }
        else
        {
            printf("Error: Division by zero is not allowed.\n");
        }
        break;
    case '^':
        res = pow(num1, num2);
        break;
    default:
        printf("Unexpected error in operator application.\n");
        break;
    }

    return res;
}
// Function to ask the user whether to perform another calculation.
bool perform_another_calculation(void)
{
    bool valid = false;

    while (!valid)
    {
        printf("Do you want to perform another calculation? (y/n): ");
        char ans = read_char();

        if (ans == 'y' || ans == 'Y')
        {
            return true;
        }
        else if (ans == 'n' || ans == 'N')
        {
            return false;
        }
        else
        {
            printf("Invalid input. Please enter 'y' for yes or 'n' for no.\n");
        }
    }

    return false;
}

int main()
{
    float num1, num2, res;
    char op;
    bool another_calculation = true;

    while (another_calculation)
    {
        printf("Please enter a number: ");
        float num1 = read_float();

        printf("Please enter another number: ");
        float num2 = read_float();

        op = read_operator();

        res = apply_operator(num1, num2, op);
        printf("%.4f %c %.4f = %.4f\n", num1, op, num2, res);

        another_calculation = perform_another_calculation();
    }

    printf("Bye!\n");
    return 0;
}
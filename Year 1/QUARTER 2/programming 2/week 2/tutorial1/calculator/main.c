#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"

#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'

#define ALLOWED_OPERATORS "+-*/"

char read_operator(void) {
    printf("Enter an operator (%c, %c, %c, %c): ", ADD, SUBTRACT, MULTIPLY, DIVIDE);
    char operator = read_char();
    while (strchr(ALLOWED_OPERATORS, operator) == NULL) {
        printf("Invalid operator. Try again.\n");
        printf("Enter an operator (%c, %c, %c, %c): ", ADD, SUBTRACT, MULTIPLY, DIVIDE);
        operator = read_char();
    }
    return operator;
}

int read_choice(int min, int max) {
    int choice;
    printf("Enter your choice: ");
    choice = read_int();
    while (choice < min || choice > max) {
        printf("Invalid choice. Try again.\n");
        printf("Enter your choice: ");
        choice = read_int();
    }
    return choice;
}

double read_operand(const char *prompt) {
    double operand;
    printf("%s", prompt);
    operand = read_double();
    return operand;
}

bool another_calculation(void) {
    char response;
    printf("Do you want to perform another calculation? (y/n) ");
    response = read_char();
    while (strchr("ynYN", response) == NULL) {
        printf("Invalid response. Try again.\n");
        printf("Do you want to perform another calculation? (y/n) ");
        response = read_char();
    }
    return tolower(response) == 'y';
}

double calculate(char operator, double operand1, double operand2) {
    switch (operator) {
        case ADD:
            return operand1 + operand2;
        case SUBTRACT:
            return operand1 - operand2;
        case MULTIPLY:
            return operand1 * operand2;
        case DIVIDE:
            if (operand2 == 0) {
                printf("\nDivision by zero is not allowed.\n");
                return 0.0;
            }
            else return operand1 / operand2;
        default:
            return 0.0;
    }
}

int main(void) {
    do {
        char operator = read_operator();
        double operand1 = read_operand("Enter the first operand: ");
        double operand2 = read_operand("Enter the second operand: ");
        double result = calculate(operator, operand1, operand2);
        printf("%.4f %c %.4f = %.4f\n", operand1, operator, operand2, result);
    }
    while (another_calculation());

    printf("Goodbye!\n");

    return 0;
}

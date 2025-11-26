 #include <stdio.h>
#include <stdbool.h>
#include "stringfun.h"

/// @brief Parses a computation (i.e. 3.5 * -2.7) from a string.
/// @param line the string to parse.
/// @param left address to store the left operand
/// @param right address to store the right operand
/// @param op address to store the operator
/// @return true if the computation was parsed successfully, and false otherwise.
bool parse_computation(const char* line, float *left, float *right, char *op) {
    if (line == NULL) return false;
    *left = *right = 0.0f;

    if(sscanf(line, " %f %c %f", left, op, right) == 3){
        if (*op != '+' && *op != '-' && *op != '*' && *op != '/') return false; // check if operator is valid
    }
    return true;
}

/// @brief Calculates the result of a computation.
/// @param left left operand
/// @param right right operand
/// @param op operation to perform
/// @return the result
float calculate(float left, float right, char op){
    if (op == '+') return left + right;
    else if (op == '-') return left - right;
    else if (op == '*') return left * right;
    else if (op == '/') return left / right;
    else return 0.0f;
}

int main(void) {
    char buffer[100];
    float left, right;
    char op;

    printf("Enter a computation: ");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (parse_computation(buffer, &left, &right, &op)) {
            fprintf(stdout, "%.2f %c %.2f = %.2f\n", left, op, right, calculate(left, right, op));
        }
        else {
            printf("Invalid computation. Try again: ");
        }
    }
    return 0;
}

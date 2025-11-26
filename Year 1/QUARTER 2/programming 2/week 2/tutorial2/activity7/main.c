#include <stdio.h>
#include "functions.h"
#include "parser.h"

#define MAX_STR_LENGTH 100

int main(void) {
    printf("Calculator: can calculate expressions like \"2 + 3 * (4 - 1)\"\n");
    printf("Supported operations: +, -, *, /\n");
    printf("Enter a calculation: ");

    // An array to store the user's expression in
    char expression[MAX_STR_LENGTH];

    // Read the user's expression
    read_string(expression, sizeof(expression));

    // variable to store the result of the calculation
    double result;

    // variable to store whether an error occurred
    bool error = false;

    // calculate the result of the expression, and check for errors
    // the `end` pointer should point to the null terminator of the string if the whole string was parsed
    const char *end = calculate_sum(expression, &result, &error);

    if (*end != '\0') {
        printf("Invalid expression. Could not parse the whole string.\n");
    }
    else if (error) {
        printf("Invalid expression.\n");
    }
    else {
        printf("Result: %.4f\n", result);
    }
    return 0;
}

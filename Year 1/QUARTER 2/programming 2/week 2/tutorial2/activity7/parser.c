#include <stdlib.h> // for strtod()
#include <ctype.h>  // for isspace()
#include <stdbool.h> // for bool
#include "parser.h"

const char *skip_whitespace(const char *calculation) {
    while (isspace(*calculation)) {
        calculation++;
    }
    return calculation;
}

const char *calculate_sum(const char *calculation, double *result, bool *error) {
    // A sum is a product followed by zero or more products with + or - in between
    // like 2 * 3 + 4 * 5 - 6 (note that a product can consist of a single number)

    // left is the value of the first product
    double left;

    // calculate the first product and move the calculation pointer to the next character (skipping whitespace)
    calculation = calculate_product(calculation, &left, error);

    // while there is a + or - after the product, calculate the next product and add or subtract it
    while (*calculation == '+' || *calculation == '-') {
        char op = *calculation; // the operator (+ or -)
        double right;        // the value of the next product

        // calculate the next product and move the calculation pointer to the next character (skipping whitespace)
        calculation = calculate_product(calculation + 1, &right, error);

        // add or subtract the next product from the left value
        if (op == '+') left += right; else left -= right;
    }

    // we've calculated the entire sum, so the result is in left.
    // store the result in the result pointer and return the calculation pointer
    *result = left;

    return calculation;
}

const char *calculate_product(const char *calculation, double *result, bool *error) {
    // A product is a number followed by zero or more numbers (or expressions in parentheses), with * or / in between

    // left is the value of the first number / expression
    double left;

    // calculate the first number / expression and move the calculation pointer to the next character (skipping whitespace)
    calculation = parse_number_or_pexpression(calculation, &left, error);

    // while there is a * or / after the number / expression, calculate the next number / expression and multiply or divide
    while (*calculation == '*' || *calculation == '/') {
        char op = *calculation; // the operator (* or /)
        double right;     // the value of the next number / expression

        // calculate the next number / expression and move the calculation pointer to the next character (skipping whitespace)
        calculation = parse_number_or_pexpression(calculation + 1, &right, error);

        // multiply or divide the next number / expression with the left value
        if (op == '*') left *= right; else left /= right;
    }

    // we've calculated the entire product, so the result is in left.
    // store the result in the result pointer and return the calculation pointer
    *result = left;
    return calculation;
}

const char *parse_number_or_pexpression(const char *calculation, double *result, bool *error) {
    // skip whitespace
    calculation = skip_whitespace(calculation);

    // check if this is a parenthesized expression or a number
    if (*calculation == '(') {
        // if it's a parenthesized expression, calculate the sum inside the parentheses
        calculation = calculate_sum(calculation + 1, result, error);

        // next, skip any whitespace
        calculation = skip_whitespace(calculation);

        // there should now be a closing parenthesis. If it's missing, set the error flag and return the calculation pointer
        if (*calculation != ')') {
            *error = true;
            return calculation;
        }

        // move the calculation pointer past the closing parenthesis, skipping any trailing whitespace
        return skip_whitespace(calculation + 1);
    }
    else {
        // if it's not a parenthesized expression, it should be a number
        // use the strtod() function to parse the number
        // this function modifies a pointer to the first character that couldn't be parsed as a number
        char *end;  // will point to the first character that couldn't be parsed as a number
        *result = strtod(calculation, &end);    // parse the number

        // if end is pointing to the beginning of the string, then no number was found, so it's an error
        if (end == calculation) *error = true; 

        // return the calculation pointer, skipping any trailing whitespace
        return skip_whitespace(end);
    }
}

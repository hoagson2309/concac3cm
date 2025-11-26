#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

/// @brief Parses the string as a product of numbers and parenthesized expressions.
/// @param calculation The string to parse.
/// @param result pointer to where the result of the calculation is to be stored
/// @param error pointer to a boolean variable that will be set to true if an error occurs
/// @return a pointer to the first character after the parsed expression
const char *calculate_product(const char *calculation, double *result, bool *error);

/// @brief Parses the string as a sum of products.
/// @param calculation The string to parse.
/// @param result pointer to where the result of the calculation is to be stored
/// @param error pointer to a boolean variable that will be set to true if an error occurs
/// @return a pointer to the first character after the parsed expression
const char *calculate_sum(const char *calculation, double *result, bool *error);

/// @brief Parses the string as a number or a parenthesized expression.
/// @param calculation The string to parse.
/// @param result pointer to where the result of the calculation is to be stored
/// @param error pointer to a boolean variable that will be set to true if an error occurs
const char *parse_number_or_pexpression(const char *calculation, double *result, bool *error);

/// @brief Skips whitespace characters in the string that appear at the beginning.
/// @param calculation the string to skip whitespace in.
/// @return a pointer to the first non-whitespace character in the string
const char *skip_whitespace(const char *calculation);

#endif // PARSER_H

#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <string.h>

/// @brief Prints a string to the console.
/// @param string The string to print.
void print_string(const char string[]);

/// @brief Converts a string to uppercase.
/// @param string the string to convert to uppercase.
void to_uppercase(char string[]);

/// @brief Returns the length of a string.
/// @param string The string to determine the length of.
/// @return The length of the string.
size_t string_length(const char string[]);

/// @brief Prints a string in reverse to the console.
/// @param string The string to print in reverse.
void print_string_reverse(const char string[]);

#endif // TUTORIAL_H

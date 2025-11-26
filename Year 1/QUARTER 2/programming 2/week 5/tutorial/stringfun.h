#ifndef STRINGFUN_H
#define STRINGFUN_H

#include <stdbool.h>

/// @brief Reverses a string in place.
/// @param string the string to reverse.
void reverse(char *string);

/// @brief Checks if a string is a palindrome, ignoring non-alphabetic characters.
/// @param string the string to check.
/// @return true if the string is a palindrome, and false otherwise.
bool is_palindrome(const char *string);

#endif // STRINGFUN_H
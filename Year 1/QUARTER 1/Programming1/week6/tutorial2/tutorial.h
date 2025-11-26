#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <string.h>
#include <stdbool.h>

/// @brief Copies the contents of one string to another.
/// @param destination The string to copy to (it is assumed that the destination string is large enough to hold the source string).
/// @param source The string to copy from.
/// @param destination_index The index in the destination string where the copying should start.
void copy_string(char destination[], const char source[], size_t destination_index);

/// @brief Concatenates two strings.
/// @param destination The string to concatenate to (it is assumed that the destination string is large enough to hold both strings).
/// @param source The string to concatenate to the destination string.
void concatenate_strings(char destination[], const char source[]);

/// @brief Reverses a string.
/// @param string The string to reverse.
void reverse_string(char string[]);

/// @brief Checks if a string is a palindrome.
/// @param string The string to check.
/// @return true if the string is a palindrome, false otherwise.
bool is_palindrome(const char string[]);

#endif // TUTORIAL_H

#ifndef MOREFUNS_H
#define MOREFUNS_H

#include <stdio.h>
#include <stdbool.h>

/// @brief Returns the number of digits in number that match digit
/// @param number The number to count digits in
/// @param digit A digit (0-9) to count in number
/// @return The number of times digit appears in number
int count_digits(int number, int digit);

/// @brief Checks if a character is a vowel (a, e, i, o, u).
/// @param c The character to check.
/// @return True if the character is a vowel, false otherwise.
bool is_vowel(char c);

/// @brief Reads integers from a file into a dynamically allocated array.
/// @param file The file to read from.
/// @param count The number of integers read.
/// @return The integers read from the file, or NULL if no integers were read.
int *read_integers(FILE *file, size_t *count);

/// @brief Reads lines from a file into a dynamically allocated array.
/// @param file The file to read from.
/// @param count The number of lines read.
/// @return The lines read from the file, or NULL if no lines were read.
char **read_lines(FILE *file, size_t *count);

/// @brief Frees the memory allocated for the strings in an array of strings.
/// @param lines The array of strings.
/// @param count The number of strings in the array.
void free_strings(char *lines[], size_t count);

/// @brief Prints an array of integers.
/// @param array The array of integers.
/// @param count The number of integers in the array.
void print_integers(const int array[], size_t count);

/// @brief Prints an array of strings.
/// @param lines The array of strings.
/// @param count The number of strings in the array.
void print_lines(char *lines[], size_t count);

#endif // MOREFUNS_H
#ifndef WEEK7_H
#define WEEK7_H

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "functions.h"

/// @brief Determines if an array of integers contains a specific value.
/// @param numbers the array of integers
/// @param size the number of elements in the array
bool contains_int(const int numbers[], size_t size, int value);

/// @brief Determines if an array of integers contains any duplicates.
/// @param numbers the array of integers
/// @param size the number of elements in the array
bool has_duplicates(const int numbers[], size_t size);

/// @brief Prints an array of integers.
/// @param values the array to print
/// @param size the number of elements in the array
void print_int_array(const int values[], size_t size);

/// @brief Reads an integer from the user and ensures it is a valid index.
/// @param size the size of the array for which to read an index
/// @return the valid index
int read_valid_index(size_t size);

/// @brief Determines if a character is a vowel.
/// @param c the character to check
/// @return true if the character is a vowel, false otherwise
bool isvowel(char c);

/// @brief Counts the number of vowels in a string.
/// @param str the string to count vowels in
/// @return the number of vowels in the string
size_t count_vowels(const char str[]);

/// @brief Counts the number of non-space characters in a string.
/// @param str the string to count non-space characters in
/// @return the number of non-space characters in the string
size_t count_nonspace(const char str[]);

/// @brief Swaps two strings. It is assumed that the strings are stored in
///      arrays of the same size.
/// @param string1 The first string to swap
/// @param string2 The second string to swap
void swap_strings(char string1[], char string2[]);

/// @brief Bubbles the longest string to the end of the array.
/// @param strings the array of strings
/// @param size the number of strings in the array
/// @return The number of swaps made
int bubble_longest_string(char strings[][100], size_t size);

/// @brief Sorts an array of strings using the bubble sort algorithm,
///        comparing the strings by length.
/// @param strings the array of strings to sort
/// @param size the number of strings in the array
/// @return the number of swaps made
int bubble_sort_strings(char strings[][100], size_t size);

/// @brief Finds the string with the fewest vowels.
/// @param strings the array of strings
/// @param size the number of strings in the array
/// @return the index of the string with the fewest vowels
size_t find_string_with_fewest_vowels(const char strings[][100], size_t start, size_t size);

/// @brief Sorts an array of strings using the selection sort algorithm,
///        by comparing the strings by the number of vowels they contain.
/// @param strings the array of strings to sort
/// @param size the number of strings in the array
/// @return the number of swaps made
int selection_sort_strings(char strings[][100], size_t size);


/// @brief Removes an element from an array by index.
/// @param values the array of values
/// @param size the number of elements in the array
/// @param index the index of the element to remove
/// @return the number of elements remaining in the array
int remove_by_index(int values[], size_t size, size_t index);


/// @brief remove all vowels from a string
/// @param str the string of characters
void remove_vowels(char str[]);

#endif // WEEK7_H

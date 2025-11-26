#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/// @brief Prints an array of integers
/// @param array The array to print.
/// @param count The number of elements in the array.
void print_ints(const int *array, size_t count);

/// @brief Prints an array of floats
/// @param array The array to print.
/// @param count The number of elements in the array.
void print_floats(const float *array, size_t count);

/// @brief Prints an array of characters
/// @param array The array to print.
/// @param count The number of elements in the array.
void print_chars(const char *array, size_t count);

/// @brief Fills an array with random values.
/// @param array The array to fill.
/// @param count The number of elements in the array.
/// @param size The size of each element in bytes.
/// @param min The minimum byte value of the random number.
/// @param max The maximum byte value of the random number.
void fill_random(void *array, size_t count, size_t size, unsigned char min, unsigned char max);

#endif // UTILS_H

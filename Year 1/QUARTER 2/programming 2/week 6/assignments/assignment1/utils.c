#include "utils.h"
#include <stdio.h>
#include "functions.h"

/// @brief Fills an array with random values.
/// @param array The array to fill.
/// @param count The number of elements in the array.
/// @param size The size of each element in bytes.
/// @param min The minimum byte value of the random number.
/// @param max The maximum byte value of the random number.
void fill_random(void *array, size_t count, size_t size, unsigned char min, unsigned char max) {
    char *array_ptr = (char *)array;
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < size; ++j)
            array_ptr[i * size + j] = random_int(min, max);
    }
}

void print_ints(const int *array, size_t count) {
    if (count > 0) printf("%d", array[0]);
    for (size_t i = 1; i < count; ++i)
        printf(", %d", array[i]);
    printf("\n");
}

void print_floats(const float *array, size_t count) {
    if (count > 0) printf("%f", array[0]);
    for (size_t i = 1; i < count; ++i)
        printf(", %f", array[i]);
    printf("\n");
}

void print_chars(const char *array, size_t count) {
    if (count > 0) printf("%c", array[0]);
    for (size_t i = 1; i < count; ++i)
        printf(", %c", array[i]);
    printf("\n");
}

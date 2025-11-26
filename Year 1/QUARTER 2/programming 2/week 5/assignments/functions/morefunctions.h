#ifndef MOREFUNCTIONS_H
#define MOREFUNCTIONS_H

#include <stdbool.h>
#include <stddef.h>

/// Shuffles an array of elements.
/// @param array The array to shuffle.
/// @param count The number of elements in the array.
/// @param element_size The size of each element in the array.
void shuffle(void *array, size_t count, size_t element_size);

#endif // MOREFUNCTIONS_H

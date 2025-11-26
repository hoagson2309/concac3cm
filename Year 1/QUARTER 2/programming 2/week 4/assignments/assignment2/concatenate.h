#ifndef CONCATENATE_H
#define CONCATENATE_H

#include <stddef.h>     // for size_t

typedef struct {
    char *data;     // The string data - the actual characters in the string, followed by a null terminator.
    size_t length;  // The length of the string, excluding the null terminator.
} string_t;

/// Creates a new string by copying the given string.
/// @return A new string.
string_t new_string(const char *initial);

/// Appends a string to another string.
/// @param string The string to append to.
/// @param to_append The string to append.
void append_string(string_t *string, const char *to_append);

/// Deallocate the memory used by a string.
/// @param string The string to deallocate.
void free_string(string_t *string);

#endif // CONCATENATE_H
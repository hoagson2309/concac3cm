#ifndef SPLIT_H
#define SPLIT_H

#include <stddef.h>

typedef char * string_t;

typedef struct {
    string_t *strings;
    size_t count, capacity;
} string_array_t;

/// Copies a string to a new memory location, using dynamic memory allocation.
/// @param string The string to copy.
/// @return A pointer to the copy of the string.
string_t copy_string(const char *string);

/// Adds a string to a string array.
/// @param array The string array to add the string to.
/// @param string The string to add.
void add_string(string_array_t *array, string_t string);

/// Splits a string into words.
/// @param string The string to split.
/// @return An array of strings that are the words in the input string.
string_array_t split(const char *string);

/// Finds the first word in a string, or NULL if no words are found.
/// @param string The string to search for the next word.
/// @return A pointer to the start of the first word in the string, or NULL if no words are found.
const char *find_first_word(const char *string);

/// Finds the next word in a string, or NULL if no more words are found.
/// @param string The string to search for the next word.
/// @return A pointer to the start of the next word in the string, or NULL if no more words are found.
const char *find_next_word(const char *string);

/// Frees the memory used by a string array.
/// @param array The string array to free.
void free_string_array(string_array_t *array);

#endif // SPLIT_H
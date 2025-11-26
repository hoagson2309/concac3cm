#ifndef WORDS_H
#define WORDS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef char* string_t;  // string_t is an alias for char*

typedef struct {
    string_t *data;      // Array of strings (using string_t)
    size_t size;         // Number of words currently stored
    size_t capacity;     // Maximum number of words that can be stored
} words_t;

// Assignment 1: Find a word in the collection
const char *find(const char *word, const words_t *words);

// Assignment 2: Resize the word collection
bool set_capacity(words_t *words, size_t desired_capacity);

// Assignment 3: Add a unique word to the collection
bool add_unique_word(words_t *words, const char *word);

// Assignment 4: Read unique words from a file
words_t read_words(FILE *file);

// Assignment 5a: Comparison function for sorting
int compare_words(const void *a, const void *b);

#endif // WORDS_H
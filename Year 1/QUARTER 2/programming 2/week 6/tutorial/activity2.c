#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <ctype.h>

/// @brief Applies a function to (the address of) each element of an array.
/// @param array The array to apply the function to.
/// @param size The size of the array
/// @param function The function to apply to each element of the array.
void apply(int *array, size_t size, void (*function)(int *));

/// @brief Checks if a string contains only characters that satisfy a condition.
/// @param string The string to check.
/// @param function The function that checks if a character satisfies a condition.
/// @return true if all characters in the string satisfy the condition, and false otherwise.
bool all(const char *string, bool (*function)(char));

// some functions that could be passed to the "apply" function
void times_two(int *number) { *number *= 2; }
void plus_one(int *number) { *number += 1; }

// some functions that could be passed to the "all" function
bool is_digit(char c) { return isdigit(c); }
bool is_vowel(char c) { return strchr("aeiouAEIOU", c) != NULL; }

//typedef for function pointers
typedef void (*int_function)(int *); //if typedef void int_function(int *); => int_function *pointer = some_function;
typedef bool (*char_function)(char);

int main(void) {
    // TODO: introduce two `typedef`s to simplify the function pointers
    
    // function pointers that can be passed to the "all" function
    char_function vowel_checker = is_vowel;
    char_function digit_checker = is_digit;

    // function pointers that can be passed to the "apply" function
    int_function multiplier = times_two;
    int_function adder = plus_one;

    // array of integers
    int numbers[] = {1, 2, 3, 4, 5};

    // array of strings
    const char *strings[] = {"hello", "world", "123", "abc", "AEIOU"};

    // apply the multiplier function to each element of the "numbers" array
    apply(numbers, sizeof(numbers) / sizeof(numbers[0]), multiplier);

    // apply the adder function to each element of the "numbers" array
    apply(numbers, sizeof(numbers) / sizeof(numbers[0]), adder);

    // go over the strings and run the "all" function on each of them
    for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
        if (all(strings[i], vowel_checker)) {
            printf("All characters in \"%s\" are vowels.\n", strings[i]);
        } else if (all(strings[i], digit_checker)) {
            printf("All characters in \"%s\" are digits.\n", strings[i]);
        } else {
            printf("The characters in \"%s\" are neither all vowels nor all digits.\n", strings[i]);
        }
    }
}

void apply(int *array, size_t size, void (*function)(int *)) {
    for (size_t i = 0; i < size; i++) {
        function(&array[i]);
    }
}   

/// @brief Checks if a string contains only characters that satisfy a condition.
/// @param string The string to check.
/// @param function The function that checks if a character satisfies a condition.
/// @return true if all characters in the string satisfy the condition, and false otherwise.
bool all(const char *string, bool (*function)(char)) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!function(string[i])) return false; // if the function returns false, return false
    }
    return true;    // if the function never returns false, return true
}

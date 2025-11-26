#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"
#include "morefuns.h"

/// @brief Comparison function.
/// @param a The first element to compare.
/// @param b The second element to compare.
/// @return A negative value if `a` is less than `b`, a positive value if `a` is greater than `b`, and zero if `a` is equal to `b`.
typedef int compare_fn(const void *a, const void *b);

/// @brief Returns the index of the "maximum" element in an array.
/// @param array The array to search.
/// @param count The number of elements in the array.
/// @param size The size of each element in the array.
/// @param compare A function that compares two elements.
/// @return Index of the "maximum" element in the array, or -1 if the array is empty.
int index_of_max(const void *array, size_t count, size_t size, compare_fn *compare) {
    if (count == 0) {
        return -1;
    }

    // TODO: Implement this function.

    int max_index = 0;
    const void *max_element = array;

    for(size_t i = 1; i < count; i++){
        const void *current_element = (const char *)array + i * size;
        if(compare(current_element, max_element) > 0){
            max_index = i;
            max_element = current_element;
        }
    }
    return max_index;
}

int compare_digit_count(const void *a, const void *b){
    int digit = 5; //change if needed for other digits
    int num_a = *(const int *)a;
    int num_b = *(const int *)b;

    int count_a = count_digits(num_a, digit);
    int count_b = count_digits(num_b, digit);

    return count_a - count_b;
}

int compare_punctuation_count(const void *a, const void *b){
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    
    int count_a = 0, count_b = 0;
    while (*str_a) count_a += ispunct((unsigned char)*str_a++);
    while (*str_b) count_b += ispunct((unsigned char)*str_b++);

    return count_a - count_b;
}

int compare_vowel_count(const void *a, const void *b){
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;

    int count_a = 0, count_b = 0;
    while (*str_a) count_a += is_vowel((unsigned char)*str_a++);
    while (*str_b) count_b += is_vowel((unsigned char)*str_b++);
    return count_a - count_b;
}

// TODO: implement a number of functions that can be passed to index_of_max (see description in main function)

int main(void) {
    // Read integers from file "integers.txt"
    FILE *file = fopen("integers.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open integers.txt.\n");
        return 1;
    }
    size_t integer_count;
    int *integers = read_integers(file, &integer_count);
    fclose(file);

    // Read lines from file "text.txt"
    file = fopen("text.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open text.txt.\n");
        return 1;
    }
    size_t line_count;
    char **lines = read_lines(file, &line_count);
    fclose(file);

    // print the integers
    print_integers(integers, integer_count);

    // TODO: Use the function index_of_max to find and print the following:
    //  - the integer that contains the most fives in its digits (e.g., 5555 has more fives than 5545) - use the count_digits function from morefuns.h
    int max_five_index = index_of_max(integers, integer_count, sizeof(int), compare_digit_count);
    printf("\nThe integer with the most fives is %d.\n\n", integers[max_five_index]);

    // print the lines
    print_lines(lines, line_count);

    // TODO: Use the function index_of_max to find and print the following:
    //  - the string that has the most punctuation characters (e.g., "Hello, world!" has 2 punctuation characters) - use ispunct from <ctype.h>
    //  - the string that has the most vowels (e.g., "Hello, world!" has 3 vowels) - use the is_vowel function from morefuns.h
    int max_punctuation_index = index_of_max(lines, line_count, sizeof(char *), compare_punctuation_count);
    printf("\nThe line with the most punctuation characters is:\n \"%s\".\n", lines[max_punctuation_index]);

    int max_vowels_index = index_of_max(lines, line_count, sizeof(char *), compare_vowel_count);
    printf("\nThe line with the most vowels is:\n \"%s\".\n", lines[max_vowels_index]);

    free_strings(lines, line_count);
    free(integers);
    free(lines);
}


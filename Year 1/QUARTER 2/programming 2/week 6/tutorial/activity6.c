#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/// @brief Reads strings from a file into an array of strings.
/// @param file The file to read from (must be open for reading).
/// @param strings The array of strings to read into.
/// @param maxsize The maximum number of strings to read.
/// @return The number of strings actually read.
size_t read_words(FILE *file, char *strings[], size_t maxsize);

/// @b  rief Prints an array of strings, breaking lines to keep the line length below a given limit.
/// @param strings The array of strings to print.
/// @param count The number of strings in the array.
/// @param linelength The maximum line length.
void print_strings(char *strings[], size_t count, size_t linelength);

/// @brief Comparison function for qsort to sort strings by length.
/// @param a Pointer to the first string.
/// @param b Pointer to the second string.
/// @return A negative value if the first string is shorter, a positive value if it is longer, or 0 if they are equal in length.
int compare_string_lengths(const void *a, const void *b);

int main(void) {
    char *strings[100] = {NULL}; // array of strings, all initialized to NULL
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file.\n");
        return 1;
    }

    size_t count = read_words(file, strings, sizeof(strings) / sizeof(strings[0]));
    fclose(file);

    // TODO: sort the strings using qsort, so that the shortest strings come first
    qsort(strings, count, sizeof(char *), compare_string_lengths);
    
    print_strings(strings, count, 80);

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
}

size_t read_words(FILE *file, char *strings[], size_t maxsize) {
    char buffer[200];   // buffer for reading strings
    size_t count = 0;
    while (fscanf(file, "%99s", buffer) == 1 && count < maxsize) {
        strings[count] = (char*) malloc(strlen(buffer) + 1);
        if (strings[count] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return count;
        }
        strcpy(strings[count], buffer); // copy the string to the allocated memory
        count++;
    }
    return count;
}

/// @brief Prints an array of strings, breaking lines to keep the line length below a given limit.
/// @param strings The array of strings to print.
/// @param count The number of strings in the array.
/// @param linelength The maximum line length.
void print_strings(char *strings[], size_t count, size_t linelength) {
    size_t end = 0;
    bool first = true;
    for (size_t i = 0; i < count; i++) {
        end += strlen(strings[i]) + 2;
        if (end > linelength) {
            printf("\n");
            end = strlen(strings[i]) + 2;
            first = true;
        }
        if (!first) printf(", ");
        printf("%s", strings[i]);
        first = false;
    }
}


/// @brief Comparison function for qsort to sort strings by length.
/// @param a Pointer to the first string.
/// @param b Pointer to the second string.
/// @return A negative value if the first string is shorter, a positive value if it is longer, or 0 if they are equal in length.
int compare_string_lengths(const void *a, const void *b) {
    const char *const *str_a = (const char *const *)a;
    const char *const *str_b = (const char *const *)b;

    size_t len_a = strlen(*str_a);
    size_t len_b = strlen(*str_b);

    return (int)(len_a - len_b);
    }



//The array stores pointers to strings (char *), so each element of the array is of type char *.
//qsort passes the address of each element to the comparison function, which is of type char **.
//To correctly interpret the data passed by qsort, you need to cast void * to char **.
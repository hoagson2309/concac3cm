#include <stdio.h>
#include "functions.h"
#include "split.h"

int main(void) {
    char string[200];

    // Read a string from the user
    printf("Enter a string: ");
    read_string(string, sizeof(string));

    // Split the string into words
    string_array_t words = split(string);

    // Print the words
    printf("There are %zu words in the string:\n", words.count);
    for (size_t i = 0; i < words.count; i++) {
        printf("\"%s\"\n", words.strings[i]);
    }

    // Free the memory used by the words
    free_string_array(&words);
}

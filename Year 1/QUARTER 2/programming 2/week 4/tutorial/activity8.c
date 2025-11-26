#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

#define NUM_STRINGS 3
#define STRING_CAPACITY 200

int main(void) {
    // FIXME: change this program so that it does not use *ANY* arrays, only pointers
    //single pointer variable that points to array of strings
    char **strings = malloc(NUM_STRINGS * sizeof(char *));
    if (strings == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    //allocate memory for each string
    for (int i = 0; i < NUM_STRINGS; i++) {
        strings[i] = malloc(STRING_CAPACITY * sizeof(char));
        if (strings[i] == NULL) {
            printf("Memory allocation failed\n");
            // free already allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }
    }

    // Read strings
    printf("Hi, what's your name? ");
    read_string(strings[0], STRING_CAPACITY);

    printf("Where are you from? ");
    read_string(strings[1], STRING_CAPACITY);

    printf("What's your favorite color? ");
    read_string(strings[2], STRING_CAPACITY);

    printf("Hello, %s from %s! Your favorite color is %s.\n", strings[0], strings[1], strings[2]);
    
    // Free memory
    for (int i = 0; i < NUM_STRINGS; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}
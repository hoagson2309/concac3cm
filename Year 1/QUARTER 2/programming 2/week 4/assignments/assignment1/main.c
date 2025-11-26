#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

/// Creates a new string that is the reverse of the given string.
/// @param string The string to reverse.
/// @return A new string that is the reverse of the given string.
char *reverse_string(const char *string);

int main(void) {
    char line[200];
    printf("Enter a line of text: ");

    // Read a line of text from the user.
    read_string(line, sizeof(line));

    // Obtain a reversed copy of the string.
    char *reversed = reverse_string(line);

    // Print the original and the reversed string.
    printf("Output: %s %s\n", line, reversed);

    free(reversed); // Free the memory allocated by reverse_string.
    return 0;
}

char *reverse_string(const char *string) {
    size_t length = strlen(string);

    //allocating memory for reversed string, including the null terminator
    char *reverse = (char*) malloc(length * sizeof(char));

    if(reverse == NULL){
        printf("Memory allocation failed\n");
        exit(1); //exit if there's allocation failure
    }

    for(size_t i = 0; i < length; i++){
        reverse[i] = string[length - 1 - i]; //create a new string that is the reverse of the original string
    }

    reverse[length] = '\0';

    return reverse;
}
# Assignments - Week 4

You must complete two out of the three assignments, but you are encouraged to complete all three.
Below you will find, per assignment, instructions on what you need to include in this markdown file.

## Assignment 1 - Mirroring a string

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
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
```

## Assignment 2 - Dynamic string building

In this assignment you will work with three files: `main.c` and `concatenate.c`.

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
#include <stdio.h>
#include "functions.h"
#include "concatenate.h"

int main(void) {
    char line[200];
    printf("Enter a line of text: ");

    // Create a new string_t structure that contains an empty string.
    string_t string = new_string("");

    // Read a line of text from the user.
    read_string(line, sizeof(line));

    // repeat while the line is not empty
    while (line[0] != '\0') {
        // TODO: Append the line to the string by calling append_string.
        append_string(&string, line);
        printf("Enter a line of text: ");
        read_string(line, sizeof(line));
    }

    printf("The concatenated string is: %s\n", string.data);
    
    // TODO: free the memory used by the string by calling free_string.
    free_string(&string);
    return 0;
}

```

Include the definitions for the functions you wrote in `concatenate.c` here:

```c
// TODO: Include the definitions for the functions you wrote in `concatenate.c` here
#include "concatenate.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// TODO: Implement the functions listed in concatenate.h.


string_t new_string(const char *initial) {
    const size_t len = strlen(initial);
    string_t new_string = {
         .data = (char*) malloc(len + 1),   // allocate memory for the string
         .length = 0 };                     // set the length of the string to 0 for now

    if (new_string.data == NULL) return new_string; // return the string if the memory allocation fails

    // memory allocation successful, copy the string and set the length
    strcpy(new_string.data, initial);
    new_string.length = len;

    return new_string;
}

//appends a string to another string
void append_string(string_t *string, const char *to_append){
    size_t append_length = strlen(to_append);
    size_t new_length = string->length + append_length; //add more length

    //reallocate memory of string->data to fit the new concanated string
    char *new_data = (char*) realloc(string->data, new_length + 1);
    if(new_data == NULL){
        printf("Memory reallocation failed");
        exit(1);
    }
    
    string->data = new_data; //update the pointer to the memory
    strcat(string->data, to_append); //append the new string
    string->length = new_length; //update the length
}

//Deallocate the memory used by a string
void free_string(string_t *string){
    free(string->data); //free the dynamically allocated memory
    string->data = NULL; //set pointer to NULL
    string->length = 0; //reset the length
}
```

## Assignment 3 - String splitting

In this assignment you will work with three files: `main.c` and `split.c`.

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
```

Include the contents of your `split.c` file here:

```c
// TODO: Include the contents of your `split.c` file here
```


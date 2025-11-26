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
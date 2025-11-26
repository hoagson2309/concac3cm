#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"
/// Replaces all the occurrences of the given string in the given text with the given replacement character.
/// Each string is replaced by a number of replacement characters equal to the length of the string.
/// The function does not print anything to the console.
/// @param text The text to search.
/// @param string The string to search for.
/// @param replacement The character to replace the string with.
void censor(char *text, const char *string, char replacement);
void censor(char *text, const char *string, char replacement){
    int size = strlen(string);
    char *occurences = strstr(text, string);
    while(occurences != NULL){
        for(size_t i = 0; i < size; i++){
            *(occurences + i) = replacement;
        }
        occurences = strstr(text, string);
    }
}

int main(){
    char text[300];
    char string[300];
    char replacement = '*';
    printf("Please enter a line of text: ");
    read_string(text, 300);
    printf("Please enter a string to search for: ");
    read_string(string, 300);
    censor((void*)text, (void*)string, replacement);
    printf("%s ", text);
}

///int *(array+1) == &array[1]



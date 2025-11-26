#include "tutorial.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// TODO: put your function definitions in here
void print_string(const char string[]){
    int i = 0;
    while(string[i] != '\0'){
        printf("%c\n", string[i]);
        i++;
    }
}

void to_uppercase(char string[]){
    int i;
    while(string[i] != '\0'){
        string[i] = toupper(string[i]);
        i++;
    }
}

size_t string_length(const char string[]){
    size_t length = 0;
    while(string[length] != '\0'){
        length++;
    }
    return length;
}

void print_string_reverse(const char string[]){
    int length = string_length(string);

    for(int i = length; i >= 0; i--){
        printf("%c", string[i]);
    }
}



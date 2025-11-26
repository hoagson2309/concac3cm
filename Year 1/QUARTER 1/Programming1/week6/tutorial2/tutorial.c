#include "tutorial.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// TODO: put your function definitions in here
void copy_string(char destination[], const char source[], size_t destination_index){
    for(int i = 0; i < strlen(source); i ++){
        destination[destination_index + i] = source[i];
    }    
}


void concatenate_strings(char destination[], const char source[]){
    size_t length_destination = strlen(destination);
    copy_string(destination, source, length_destination);
}


void reverse_string(char string[]){
    size_t length = strlen(string);
    size_t i = 0;
    while(i < length){
        char temp = string[i];
        string[i] = string[length - 1];
        string[length - 1] = temp;
        i++;
        length--;
    }
}

bool is_palindrome(const char string[]){
    size_t length = strlen(string);
    for (size_t i = 0; i < length; i++){
        if(string[i] != string[length - 1]){
            return false;
        }
        length--;
    }
    return true;
}
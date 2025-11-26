#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

/// @brief Changes all characters in the given string that matches (regardless of their case) the given character to uppercase,
/// and all other characters to lowercase.
/// @param string The string to modify.
/// @param character The character to change to uppercase.
void change_case(char string[], char character){

    int i = 0;

    while (string[i] != '\0') {
        
        if (string[i] != character){

            string [i] = tolower(string[i]);
        }

        else if (string[i] == character && islower(string[i])){

            string[i] = toupper(string[i]);
        }

        i++;
    }



}

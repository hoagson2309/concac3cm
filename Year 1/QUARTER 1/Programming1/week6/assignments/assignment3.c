#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

/// @brief Compares two strings in a case-insensitive way and returns a value less than, equal to, or greater than zero if the first string should come before, is equal to, or should come after the second string
/// when sorting them alphabetically.
/// @param string1 The first string to compare.
/// @param string2 The second string to compare.
/// @return A value less than, equal to, or greater than zero if the first string should come before, is equal to, or should come after the second string in alphabetical order.
int compare_strings(const char string1[], const char string2[]){
    int i = 0;
    while (string1[i] != '\0' && string2[i] != '\0') {
        if (string1[i] != string2[i]) {
            return string1[i] - string2[i];
        }
        i++;
    }

    return string1[i] - string2[i];
}

/// @brief Swaps the contents of two strings, assuming that both strings are stored in arrays of the same size.
/// @param string1 The first string to swap.
/// @param string2 The second string to swap.
void swap_strings(char string1[], char string2[]){
    int i = 0;
    while(string1[i] != '\0' && string2[i] != '\0'){
        char temp = string1[i];
        string1[i] = string2[i];
        string2[i] = temp;
        i++;
    }

    while (string1[i] != '\0')
    {
        char temp = string1[i];
        string1[i] = string2[i];
        string2[i] = temp;
        i++;
    }

    while (string2[i] != '\0')
    {
        char temp = string1[i];
        string1[i] = string2[i];
        string2[i] = temp;
        i++;
    }
    
}

int main(void) {
    char string1[300];
    char string2[300];
    char string3[300];

    printf("Enter the first string: ");
    read_string(string1, 300);

    printf("Enter the second string: ");
    read_string(string2, 300);
    
    printf("Enter the third string: ");
    read_string(string3, 300);

    int compare1 = compare_strings(string1, string2);
    if(compare1 > 0){
    swap_strings(string1, string2);
    }

    int compare2 = compare_strings(string2, string3);
    if(compare2 > 0){
    swap_strings(string2, string3);
    }

    int compare3 = compare_strings(string1, string2);
    if(compare3 > 0){
    swap_strings(string1, string2);
    }

    printf("The strings in alphabetical order are: \n%s\n%s\n%s\n", string1, string2, string3);

}

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

/// @brief Checks if the given string contains only whitespace characters.
/// @param string The string to check.
/// @return True if the string contains only whitespace characters, false otherwise.
bool contains_only_whitespace(const char string[]){
    for(int i = 0; i < strlen(string); i++){
        if(!isspace(string[i])){
            return false;
        }
    }
    return true;
}

/// @brief Changes all characters in the given string that matches (regardless of their case) the given character to uppercase,
/// and all other characters to lowercase.
/// @param string The string to modify.
/// @param character The character to change to uppercase.
void change_case(char string[], char character){
    char target = tolower(character);
    for (int i = 0; string[i] != '\0'; i++){
        if(isalpha(string[i])){
            if(tolower(string[i]) == target){
                string[i] = toupper(string[i]);
            }
            else{
                string[i] = tolower(string[i]);
            }
        }
    }
}

/// @brief Counts the number of occurrences of each character (regardless of their case) in the given string.
/// @param string The string to count the occurrences in.
/// @param occurrences An array of 26 integers to store the number of occurrences of each alphabet character.
void count_occurrences(const char string[], int occurrences[]){
    for(int i = 0; i < 26; i++){
        occurrences[i] = 0;
    }
    for(int i = 0; string[i] != '\0'; i++){
        if(isalpha(string[i])){
            char index = tolower(string[i]) - 'a';
            occurrences[index]++;
        }
    }
}

/// @brief Finds the most frequent character in the given array of occurrences.
/// @param occurrences An array of 26 integers that store the number of occurrences of each alphabet character.
/// @return The most frequent character.
char most_frequent_character(const int occurrences[]){
    int maxcount = 0;
    int maxindex = 0;
    for(int i = 0; i < 26; i++){
        if(occurrences[i] > maxcount){
            maxcount = occurrences[i];
            maxindex = i;
        }
    }
    return 'a' + maxindex; //convert the index back to its corresponding alphabet character
}

int main(void) {
    char sentence[300];
    size_t size = sizeof(sentence) / sizeof(sentence[0]);
    printf("Enter a sentence (or whitespace to stop): ");
    read_string(sentence, size);

    while(!contains_only_whitespace(sentence)){
    
    int occurrences[26];
    count_occurrences(sentence, occurrences);

    char mostfrequentchar = most_frequent_character(occurrences);
    change_case(sentence, mostfrequentchar);

    printf("Modified sentence: %s\n", sentence);

    printf("Enter a sentence (or whitespace to stop): ");
    read_string(sentence, 300);
    }
}


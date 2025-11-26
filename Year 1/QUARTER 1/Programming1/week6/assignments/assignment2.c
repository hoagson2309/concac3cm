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

/// @brief Counts the number of vowels in the given string.
/// @param string The string to count the vowels in.
/// @return The number of vowels in the string.
int count_vowels(const char string[]){
    int count = 0;
    for(int i = 0; string[i] != '\0'; i++){
        if(isalpha(string[i])){
            if((string[i] == 'a' || string[i] == 'A') || (string[i] == 'e' || string[i] == 'E') || (string[i] == 'i' || string[i] == 'I') || (string[i] == 'o' || string[i] == 'O') || (string[i] == 'u' ||  string[i] == 'U')){
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    char sentence[100][300];
    int num = sizeof(sentence) / sizeof(sentence[0]);
    int max_vowels_count = 0;
    int i = 0;
    int index_of_sentence_with_most_vowels;
    
    
    printf("Enter a sentence (or whitespace to stop): ");
    read_string(sentence[i], num);

    while(!contains_only_whitespace(sentence[i])){ 
        int vowel_count = count_vowels(sentence[i]);
        if (vowel_count > max_vowels_count){
            max_vowels_count = vowel_count;
            index_of_sentence_with_most_vowels = i;
        }
        i++;
        printf("Enter a sentence (or whitespace to stop): ");
        read_string(sentence[i], num);
    }

    printf("The sentence with the most vowels is: %s\n", sentence[index_of_sentence_with_most_vowels]);
    printf("Number of vowels: %d\n", max_vowels_count);

    return 0;
}


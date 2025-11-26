# Week XX - Assignments

Name: SON CAO

Group: ETI1V.IA

Date: 10/10/2024

**NOTE**: if you'd like to have syntax highlighting in your markdown file, install the "Markdown Preview Github Styling" extension in VS Code.

## First assignment

The first assignment I completed is assignment 1 - Most frequent alphabet characters.
This is the code I wrote:

```c
// TODO: Write your code here
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


```

## Second assignment

The second assignment I completed is assignment 2 - Which sentence has the most vowels?.
This is the code I wrote:

```c
// TODO: Write your code here
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
    int index_of_sentence_with_most_vowels;
    int i = 0;
    
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



```

## Third assignment (optional)

I've actually made three assignments this week! The third assignment I completed is assignment 3 - Sorting three strings.
This is the code I wrote:

```c
// TODO: Write your code here
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

```

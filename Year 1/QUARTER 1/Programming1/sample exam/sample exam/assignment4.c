#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

/// @brief Finds the index of the maximum element in an array.
/// @param arr The array to search.
/// @param size The number of elements in the array.
/// @return The index of the maximum element in the array.
int index_of_max(const int arr[], int size);

/// @brief 
/// @param string 
/// @param frequency 
void count_frequency_of_char(const char string[], int frequency[]);

/// @brief 
/// @param string 
/// @param size 
/// @param letter 
void remove_letter(char string[],int size, char letter);

int main(void) {
    // Write your program for assignment 4 here
    char string[300];
    size_t size = sizeof(string) / sizeof(string[0]);
    
    printf("Enter a sentence: ");
    read_string(string, size);

    int frequency[26];
    count_frequency_of_char(string, frequency);

    int max_index = index_of_max(frequency, 26); // find the max_index of the frequency 
    char max_char = 'a' + max_index;

    remove_letter(string, size, max_char);

    printf("Modified sentence: %s\n", string);
    return 0;
}

int index_of_max(const int arr[], int size) {
    int maxindex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[maxindex]) {
            maxindex = i;
        }
    }
    return maxindex;
}

void count_frequency_of_char(const char string[], int frequency[]){
    for(int i = 0; i < 26; i++){ //assign all of the value in frequency array to 0
        frequency[i] = 0;
    }

    for(int i = 0; string[i] != '\0'; i++){
        if(isalpha(string[i])){
            int index = tolower(string[i]) - 'a'; //index corresponding to that character
            frequency[index]++; //initialize that index to the frequency array to start counting the frequency
        }
    }
}

void remove_letter(char string[], int size, char letter){
    for(int i = 0; i < size; i++){
        if(tolower(string[i]) == tolower(letter)){
            for(int j = i; j < size - 1; j++ ){ //start moving the character to the left if string[i] == provided letter
                string[j] = string[j + 1];
            }
            size--; //reduce the size of that string after removing the letter
        }
    }
    string[size] = '\0'; //updating the null of the string after removing letter
}

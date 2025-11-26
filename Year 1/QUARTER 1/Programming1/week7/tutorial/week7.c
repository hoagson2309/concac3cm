#include "week7.h"

bool contains_int(const int numbers[], size_t size, int value) {
    // TODO: implement reduction algorithm:
    //  1. Initialize the accumulator variable
    //  2. Loop through the array and update the accumulator variable
    //  3. Return the accumulator variable
    for(size_t i = 0; i < size; i++){
        if(numbers[i] == value){
            return true;
        }
    }
    return false;
}

bool has_duplicates(const int numbers[], size_t size) {
    // TODO: implement reduction algorithm:
    //  1. Initialize the accumulator variable
    //  2. Loop through the array and update the accumulator variable
    //      (use the contains_int function!)
    //  3. Return the accumulator variable
    bool contains_duplicates = false;
    for(size_t i = 0; i < size && !contains_duplicates; i++){
        if(contains_int(numbers, size, numbers[i])){
            contains_duplicates = true;
        }             
    }
    return contains_duplicates;
}

void print_int_array(const int values[], size_t size) {
    printf("[");
    if (size > 0) {
        printf("%d", values[0]);
        for (size_t i = 1; i < size; i++) {
            printf(", %d ", values[i]);
        }
    }
    printf("]\n");
}

int read_valid_index(size_t size) {
    int index = read_int();
    while (index < 0 || index >= size) {
        printf("Invalid index. Please enter a number between 0 and %zu: ", size - 1);
        index = read_int();
    }
    return index;
}

void swap_strings(char string1[], char string2[]) {
    size_t i = 0;
    while (string1[i] != '\0' && string2[i] != '\0') {
        char temp = string1[i];
        string1[i] = string2[i];
        string2[i] = temp;
        i++;
    }
    while (string1[i] != '\0') {
        string2[i] = string1[i];
        string1[i] = '\0';
        i++;
    }
    while (string2[i] != '\0') {
        string1[i] = string2[i];
        string2[i] = '\0';
        i++;
    }
 }

bool isvowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

size_t count_vowels(const char str[]) {
    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isvowel(str[i])) {
            count++;
        }
    }
    return count;
}

size_t count_nonspace(const char str[]) {
    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!isspace(str[i])) {
            count++;
        }
    }
    return count;
}

void remove_vowels(char str[]){
    int new = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if(!isvowel(str[i])){
            str[new] = str[i];
            new++;
        } 
    }
    str[new] = '\0';
}

int bubble_longest_string(char strings[][100], size_t size){
    int swaps = 0;
    for(size_t i = 0; i < size - 1; i++){
        if(strlen(strings[i]) > strlen(strings[i + 1]) ){
            swap_strings(strings[i + 1], strings[i]);
            swaps++;
        }
    }
    return swaps;
}

int bubble_sort_strings(char strings[][100], size_t size){
    int total_swaps = 0;
    int swaps;
    for (size_t i = 0; i < size - 1; i++) {
        swaps = bubble_longest_string(strings, size - i);
        total_swaps += swaps;
    }
    return total_swaps;
}

size_t find_string_with_fewest_vowels(const char strings[][100], size_t start, size_t size){
    int min_index = start;
    for(int i = start + 1; i < size; i++){
        if(count_vowels(strings[i]) < count_vowels(strings[min_index]) ){
            min_index = i;
        }
    }
    return min_index;      
}  //gan cai dau = 0, chay tu 1 toi het sau do gan vo 0; gan cai thu 2 = 1, chay tu 2 toi het sau do gan vo 1;...


int selection_sort_strings(char strings[][100], size_t size){
    size_t total_swaps = 0;

    for(int i = 0; i < size; i++){
        int fewest_vowels_strings = find_string_with_fewest_vowels(strings, size, i);
        //gan cai dau = 0, chay tu 1 toi het sau do gan vo 0; gan cai thu 2 = 1, chay tu 2 toi het sau do gan vo 1;...
        swap_strings(strings[fewest_vowels_strings], strings[i]);
        total_swaps++;
    }
    return total_swaps;
}
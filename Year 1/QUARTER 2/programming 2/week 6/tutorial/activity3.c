#include <stdio.h>
#include "functions.h"
#include <ctype.h>

typedef bool (*character_checker_fun)(char);

/// @brief Counts the number of characters in a string that satisfy a condition.
/// @param string The string to count the characters in.
/// @param checker Function that checks if a character satisfies a condition.
/// @return The number of characters in the string that satisfy the condition.
size_t count_characters(const char *string, character_checker_fun checker);

bool is_lower(char c) {
    return islower(c);
}

bool is_vowel(char c){
    char lower = tolower(c);
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}

bool is_consonant(char c){
    char lower = tolower(c);
    return isalpha(lower) && !is_vowel(lower);
}

int main(void) {
    char line[100];
    printf("Enter a string: ");
    read_string(line, sizeof(line));

    printf("Number of lowercase characters: %zu\n", count_characters(line, is_lower));

    // FIXME: use the count_characters function to count the number of vowels in the string
    printf("Number of vowels: %zu\n", count_characters(line, is_vowel));

    // FIXME: use the count_characters function to count the number of consonants in the string
    printf("Number of consonants: %zu\n", count_characters(line, is_consonant));

    return 0;
}

size_t count_characters(const char *string, character_checker_fun checker) {
    size_t count = 0;
    for (const char *c = string; *c != '\0'; c++) {
        if (checker(*c)) count++;
    }
    return count;
}

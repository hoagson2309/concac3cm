#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
int main(void) {

    char string_array [300][300] = {};
    char string [300] = {};

    int vowel_array [300] = {0};
    int highest_count_index = 0;
    
    int i = 0;
    int string_len;


    printf ("Please enter an input: ");
    read_string(string, sizeof(string) / sizeof(string[0]));
    
    string_len = strlen(string);


    while (contains_only_whitespace(string) == false){

        strcpy (string_array[i], string);

        vowel_array [i] = count_vowels(string);

        i++;

        highest_count_index = most_frequent_vowel(vowel_array, i);

        printf ("Please enter another input: ");
        read_string(string, sizeof(string) / sizeof(string[0]));

        string_len = strlen(string);
    }

    printf("The sentence with the most vowels is: %s\n", string_array[highest_count_index]);
    printf("Number of vowels: %i\n", vowel_array[highest_count_index]);
}
bool contains_only_whitespace(const char string[]){

  int length = strlen (string);

  for (int i = 0;i < length; i++) {

    if (isalpha (string [i])){

      return false;
    } 
  }

  return true;
}
int count_vowels(const char string[]){

  int length = strlen (string);
  int count = 0;
  int charecter;

  for (int i = 0; i < length; i++){

    charecter = (tolower(string[i]) - 'a');

    if (charecter == 0 || charecter == 4 || charecter == 8 || charecter == 14 || charecter == 20){

      count++;
    }
  }

  return count;
}

int most_frequent_vowel (const int vowel_count[], int length){
  int max_count = 0;
  int max_index = 0;

  for (int i = 0; i < length; i++){

    if (vowel_count[i] > max_count){

      max_count = vowel_count[i];
      max_index = i;
    }
  }

  return max_index;
}
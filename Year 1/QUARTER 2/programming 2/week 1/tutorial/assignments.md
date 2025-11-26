# Week XX - Assignments

Name: SON CAO

Group: ETI1V.IA

Date: 17/11/2024

**NOTE**: if you'd like to have syntax highlighting in your markdown file, install the "Markdown Preview Github Styling" extension in VS Code.

## First assignment

The first assignment I completed is assignment XXX.
This is the code I wrote:

```c
// TODO: Write your code here
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"
/// Replaces all the occurrences of the given string in the given text with the given replacement character.
/// Each string is replaced by a number of replacement characters equal to the length of the string.
/// The function does not print anything to the console.
/// @param text The text to search.
/// @param string The string to search for.
/// @param replacement The character to replace the string with.
void censor(char *text, const char *string, char replacement);
void censor(char *text, const char *string, char replacement){
    int size = strlen(string);
    char *occurences = strstr(text, string);
    while(occurences != NULL){
        for(size_t i = 0; i < size; i++){
            *(occurences + i) = replacement;
        }
        occurences = strstr(text, string);
    }
}

int main(){
    char text[300];
    char string[300];
    char replacement = '*';
    printf("Please enter a line of text: ");
    read_string(text, 300);
    printf("Please enter a string to search for: ");
    read_string(string, 300);
    censor((void*)text, (void*)string, replacement);
    printf("%s ", text);
}

///int *(array+1) == &array[1]
```

## Second assignment

The second assignment I completed is assignment YYY.
This is the code I wrote:

```c
// TODO: Write your code here
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

/// @brief Prints the array to the console, values comma-separated and on a single line
/// @param array The array to print.
/// @param length The length of the array.
void print_array(const int array[], size_t length);
void print_array(const int array[], size_t length){
    bool first = false;
    for(size_t i = 0; i < length; i++){
        if(first)  printf(", ");
        first = true;
        printf("%d", array[i]);
    }
}

/// @brief Swaps the values of the two integers pointed to by `a` and `b`.
/// @param a The memory address of the first integer.
/// @param b The memory address of the second integer.
void swap(int * a, int * b);
void swap(int * a, int * b){
    int temp = *a;
        *a = *b;
        *b = temp;
}

/// @brief Returns the address of the smallest number in the array.
/// @param array The array to search.
/// @param length The length of the array.
/// @return The address of the smallest number in the array, or NULL if the array is empty.
int* min_ptr(int array[], size_t length);
int* min_ptr(int array[], size_t length){
    int min = 0;
    for(int i = 1; i < length; i++){
        if(array[i] < array[min]){
            min = i;
        }
    }
    return &array[min];
}

/// @brief Returns the address of the largest number in the array.
/// @param array The array to search.
/// @param length The length of the array.
/// @return The address of the largest number in the array, or NULL if the array is empty.
int* max_ptr(int array[], size_t length);
int* max_ptr(int array[], size_t length){
      int max = 0;
    for(int i = 1; i < length; i++){
        if(array[i] > array[max]){
            max = i;
        }
    }
    return &array[max];
}

int main(){
    int array[10];
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("The array is: ");
    for(int i = 0; i < size; i++){
        array[i] = random_int(0, 100);
        }
    print_array(array, size);
    printf(".\n");

    int *min = min_ptr(array, size);
    int *max = max_ptr(array, size);
    printf("The smallest number is %d, and the largest number is %d.\n", *min, *max);

    swap(min, max);
    printf("After swapping, the array is: ");
    print_array(array, size);
    printf(".\n");

    return 0;
}



```

## Third assignment (optional)

I've actually made three assignments this week! The third assignment I completed is assignment ZZZ.
This is the code I wrote:

```c
// TODO: Write your code here
```

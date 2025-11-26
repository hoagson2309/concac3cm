# Week 6 - Tutorial 2: Arrays of strings

Name: SON CAO

Group: ETI1V.IA

Date: 09/10/2024

## Introduction

Before writing a program, it is important to think about how to structure it.
A good way to structure a program is to divide it into smaller parts, each of which performs a specific task.
Each of these smaller parts can then be implemented as a function that has clear input (i.e., parameters) and output (i.e., return value).

In this tutorial, you will write several functions that perform specific tasks, and then combine these functions to create a larger program.

### Activity 0 - Set up a folder for this tutorial & create files

Open the workspace for this week that you downloaded from Brightspace by opening the `.code-workspace` file in the root of the workspace folder.
Alternatively, you can open the workspace from a WSL terminal by typing the `code week6.code-workspace` command in the folder where you extracted the workspace.

You'll be working in the `tutorial2` folder for this tutorial.

## Copying strings

Strings are arrays of characters, and arrays can't be copied directly in C.
However, you can copy the contents of one array to another by copying each element individually.
The following snippet copies the contents of one array to another:

```c
int array1[5] = {1, 2, 3, 4, 5};
int array2[5];

for (int i = 0; i < 5; i++) {
    array2[i] = array1[i];
}
```

When copying strings, the length of the string is not known in advance - it is determined by the null terminator character `\0` at the end of the string.
This means that instead of copying the elements of the array until a certain index, you need to copy the elements until the null terminator is reached.

### Activity 1 - Copying strings

In `tutorial.c`, write a function `copy_string` that copies the contents of one string to another.
Instead of copying the string to the beginning of the destination string, the function should copy the string to a specific index in the destination string.
The function should have the following signature (which is already given in `tutorial.h`):

```c
/// @brief Copies the contents of one string to another.
/// @param destination The string to copy to (it is assumed that the destination string is large enough to hold the source string).
/// @param source The string to copy from.
/// @param destination_index The index in the destination string where the copying should start.
void copy_string(char destination[], const char source[], size_t destination_index);
```

Use the program listed in `activity1.c` to test your function.
When it runs correctly, include your definition of the `copy_string` function in the code block below:

```c
// TODO: include your code here
void copy_string(char destination[], const char source[], size_t destination_index){
    for(int i = 0; i < strlen(source); i ++){
        destination[destination_index + i] = source[i];
    }    
}
```

## Concatenating strings

To concatenate strings, you can copy the contents of one string to the end of another string.
This involves finding the null terminator character in the destination string, and then copying the source string to the index of the null terminator.

### Activity 2 - Concatenating strings

Add the definition of the function `concatenate_strings` to `tutorial.c`.
The prototype for the function is given in `tutorial.h`.

The function must _concatenate_ two strings, using the `copy_string` function.
Use the `strlen` function from the `string.h` library to find the length of the destination string, and pass this length as the `destination_index` parameter to the `copy_string` function.

Use the program listed in `activity2.c` to test your function.
When it runs correctly, include your definition of the `concatenate_strings` function in the code block below:

```c
// TODO: include your code here
void concatenate_strings(char destination[], const char source[]){
    size_t length_destination = strlen(destination);
    copy_string(destination, source, length_destination);
}
```

## Reversing

To reverse an array, you can swap the first element with the last element, the second element with the second-to-last element, and so on.
The following function reverses an array of integers that has a known length:

```c
void reverse_array(int array[], size_t length) {
    size_t i = 0;
    while (i < length) {
        // swap the elements at index i and length - 1
        int temp = array[i];
        array[i] = array[length - 1];
        array[length - 1] = temp;

        i++;        // move to the next element
        length--;   // move to the previous element
    }
}
```

### Activity 3 - Reversing strings

Add the definition for the function `reverse_string` to `tutorial.c`.
The prototype for the function is given in `tutorial.h`.
The function must reverse a string by swapping the characters in the string.

Use the program listed in `activity3.c` to test your function.
When it runs correctly, include your definition of the `reverse_string` function in the code block below:

```c
// TODO: include your code here
void reverse_string(char string[]){
    size_t length = strlen(string);
    size_t i = 0;
    while(i < length){
        char temp = string[i];
        string[i] = string[length - 1];
        string[length - 1] = temp;
        i++;
        length--;
    }
}
```

## Palindromes

A palindrome is a word, phrase, number, or other sequence of characters that reads the same forward and backward.
A classic programming problem is to check if a string is a palindrome.
To do this, you can reverse the string and then compare the reversed string to the original string.
However, it is not necessary to modify the original string to check if it is a palindrome.
Instead, you can compare the characters of the string from the beginning and the end, moving towards the middle of the string, just like you would when reversing the string, but without swapping the characters.

### Activity 4 - Checking if a string is a palindrome

In `tutorial.c`, write a function `is_palindrome` that checks if a string is a palindrome.
The function should have the following signature (already included in `tutorial.h`):

Use the program listed in `activity4.c` to test your function - test it with both palindromes and non-palindromes.
Examples of palindromes are "racecar" and "level".

When you have completed the activity, paste the definition of the `is_palindrome` function into the code block below:

```c
// TODO: include your code here
bool is_palindrome(const char string[]){
    size_t length = strlen(string);
    for (size_t i = 0; i < length; i++){
        if(string[i] != string[length - 1]){
            return false;
        }
        length--;
    }
    return true;
}
```

## Arrays, again

The following program reads 5 strings from the user and stores them in 5 different variables:

```c
#include <stdio.h>  // for printf
#include "functions.h"

int main(void) {
    char string1[200];
    char string2[200];
    char string3[200];
    char string4[200];
    char string5[200];

    printf("Enter 5 sentences:\n");
    read_string(string1, 200);
    read_string(string2, 200);
    read_string(string3, 200);
    read_string(string4, 200);
    read_string(string5, 200);

    printf("You entered the following 5 sentences: %s\n%s\n%s\n%s\n%s\n", string1, string2, string3, string4, string5);

    return 0;
}
```


### Activity 5 - Storing multiple strings in an array

Rewrite the program listed above (and listed in `activity5.c`) so that the strings are stored in an array of strings instead of in 5 separate variables.
Use loops to read the strings from the user and to print the strings.

When you have completed the activity, paste the contents of `activity5.c` into the code block below:

```c
// TODO: include your code here
#include <stdio.h>  
#include "functions.h"
#include <ctype.h>
#include <string.h>

int main(void) {
    char string[5][200];
    for(int i = 0; i < 5; i++){
        read_string(string[i], 200);
    }
    printf("You entered the following 5 sentences: \n");
    for(int i = 0; i < 5; i++){
        printf("%s\n", string[i]);
    }
    return 0;
}
```

### Activity 6 - Printing strings in reverse order

In `activity6.c`, write a program that reads 10 strings from the user and stores them in an array.
After reading the strings, the program should print the 10 strings in reverse order.
That is, the last string entered should be printed first, and the first string entered should be printed last.

When you have completed the activity, paste the contents of `activity6.c` into the code block below:

```c
// TODO: include your code here
#include <stdio.h>  // for printf
#include "functions.h"
#include <ctype.h>
#include <string.h>

int main(void) {
    char string[10][200];
    for(int i = 0; i < 10; i++){
        read_string(string[i], 200);
    }
    printf("You entered the following 10 sentences: \n");
    for(int i = 9; i >= 0; i--){
        printf("%s\n", string[i]);
    }
    return 0;
}
```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will get in touch with you.

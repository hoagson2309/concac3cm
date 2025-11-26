# Week 6 - Tutorial 1: Working with strings

Name: SON CAO

Group: ETI1V.IA

Date: 08/10/2024

## Introduction

Arrays are a fundamental concept in programming, and are used to store multiple values of the same type in a single variable.
In this tutorial, you will learn how to use arrays to store values entered by the user, and how to use loops to iterate over the elements in an array.
You will also learn how to print the contents of an array on a single line, and how to filter the elements in an array based on some condition.

### Activity 0 - Update the system

Before you start with this tutorial, make sure your system is up-to-date by running the following commands in the terminal:

```bash
sudo apt update
sudo apt upgrade
```

### Activity 1 - Open the workspace for this week

Open the workspace for this week that you downloaded from Brightspace by opening the `.code-workspace` file in the root of the workspace folder.
Alternatively, you can open the workspace from a WSL terminal by typing the `code week6.code-workspace` command in the folder where you extracted the workspace.

## ASCII values

Each `char` in C is represented by an ASCII value, which is a number that represents a character.
Characters can be printed to the console using the `printf` function, and the `%c` format specifier.
But since characters are represented by numbers, you can also print the ASCII value of a character by using the `%d` format specifier.

### Activity 2 - Printing ASCII values

Write a program in `activity2.c` that uses the `isprint` function from the `ctype.h` library to check if a character is printable.
The program must list the characters from ASCII value 0 to 127, and indicate for each character whether it is printable or not.
If the character is printable, the program should also print the character itself.
Use the `%3d` format specifier to print the ASCII value of each character, and the `%c` format specifier to print the character itself.

List the contents of the `activity2.c` file in the code block below:

```c
// TODO: include your code here
#include <stdio.h>
#include "functions.h"
#include <ctype.h>

int main(void) {
    for(int i = 0; i < 128; i++){
        if(isprint(i)){
            printf("%3d: %c\n", i , i);
        }
        else{
            printf("%3d: not printable\n", i);
        }
    }
    return 0;
}
```

## Reading and printing strings

To print a string in C, you can use the `printf` function, and use the `%s` format specifier.
Since a string is just a sequence (array) of characters, you can also print each character of the string individually by using a loop to iterate over the characters in the string.
Of course, you need to know when the string ends, which is indicated by the null terminator character `\0`.

### Activity 3 - Printing a string

In file `tutorial.c`, write a function `print_string` that prints a string to the console, by writing each character of the string to the console, followed by a newline character.
The prototype for this is given in `tutorial.h`.

The function must not use the `printf` function to print the string, but should instead print each character individually.
Also, it must not use the `strlen` function to determine the length of the string, but should instead iterate over the characters in the string until the null terminator character is reached.

The file `activity3.c` contains a `main` function that you can use to test your function (make sure to include the files `tutorial.c` and `functions.c` when building the program).
When the tests show that the function works correctly, paste your definition of the `print_string` function into the code block:

```c
// TODO: include your code here
#include <stdio.h>
#include "functions.h"
#include "tutorial.h"

void print_string(const char string[]){
    int i = 0;
    while(string[i] != '\0'){
        printf("%c\n", string[i]);
        i++;
    }
}

int main(void) {
    print_string("Hello, world!\nHow are you today?");
    return 0;
}

```

### Activity 4 - Greet the user

In `activity4.c`, write a program that greets the user by name:
use the `read_string` function from the `functions.h` file to read the user's name (make sure to prompt the user for input).
Next, use the `print_string` function (from `tutorial.h`) to greet the user by printing "Hello, ", followed by the name that the user entered, plus an exclamation mark.
So, if the user entered "Alice", the program should print "Hello, Alice!".

```c
// TODO: include your code here
#include <stdio.h>
#include "functions.h"
#include "tutorial.h"

int main(void) {
    char name [30];
    printf("Please enter your name: ");
    read_string(name, 30);

    printf("Hello, %s!\n", name);
    return 0;
}
```

### Activity 5 - Converting a string to uppercase

Add a function `to_uppercase` to the `tutorial.c` file.
The function must convert all (alphabet) characters of a string to uppercase, by traversing the string only once (i.e., you must not use `strlen`).
The prototype for the function is given in `tutorial.h`.

When writing the function, use the `toupper` function from the `ctype.h` library to convert each character in the string to uppercase.
Test the function by changing the program of activity 4 so that it prints the name that the user entered in uppercase.

Put your definition of the `to_uppercase` function into the code block below:

```c
// TODO: include your code here
#include <stdio.h>
#include "functions.h"
#include "tutorial.h"
#include <ctype.h>

void to_uppercase(char string[]){
    int i = 0;
    while(string[i] != '\0'){
        string[i] = toupper(string[i]);
        i++;
    }
}

int main(void) {
    char name [30];
    printf("Please enter your name: ");
    read_string(name, 30);
    to_uppercase(name);

    printf("Hello, %s!\n", name);
    return 0;
}

```

### Activity 6 - Finding the length of a string

In `tutorial.c`, write a function `string_length` that returns the length of a string as a `size_t` value.
The function must not use the `strlen` function, but should instead iterate over the characters in the string until the null terminator character is reached, and keep track of how many characters have been encountered.
The prototype for the function is given in `tutorial.h`.

Use the following program (listed in `activity6.c`) to test your function:

```c
int main(void) {
    printf("The length of the string 'Hello, world!' is %zu (should be 13)\n", string_length("Hello, world!"));
    printf("The length of the string 'The quick brown fox jumps over the lazy dog' is %zu (should be 43)\n", string_length("The quick brown fox jumps over the lazy dog"));
    printf("The length of the empty string \"\" is %zu (should be 0)\n", string_length(""));
    return 0;
}

//My answer:
#include <stdio.h>
#include "functions.h"
#include "tutorial.h"
#include <ctype.h>
size_t string_length(const char string[]){
    size_t length = 0;
    while(string[length] != '\0'){
        length++;
    }
    return length;
}



```

### Activity 7 - Printing a string in reverse

In `tutorial.c`, write a function `print_string_reverse` that prints a string in reverse, by writing each character of the string to the console in reverse order, followed by a newline character.
The prototype for the function is given in `tutorial.h`.
The function should use the `string_length` function from activity 6 to determine the length of the string, and should then iterate over the characters in the string in reverse order.

Use the following program (listed in `activity7.c`) to test your function:

```c
int main(void) {
    print_string_reverse("Hello, world!"); // should print "!dlrow ,olleH"
    print_string_reverse("");              // should print nothing (empty string)
    print_string_reverse("12345");         // should print "54321\n"
    return 0;
}
//answer:
#include <stdio.h>
#include "functions.h"
#include "tutorial.h"
#include <ctype.h>

void print_string_reverse(const char string[]){
    int length = string_length(string);

    for(int i = length; i >= 0; i--){
        printf("%c", string[i]);
    }
}

int main(void) {
    print_string_reverse("\nHello, world!");  // should print "!dlrow ,olleH\n"
    print_string_reverse("\n");            // should print a newline (empty string)
    print_string_reverse("\n12345");            // should print "54321\n"
    return 0;
}

```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will get in touch with you.

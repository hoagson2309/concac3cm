# Week 5 - Tutorial: Streams and File I/O

Name: SON CAO

Group: ETI1V.IA

Date: 11/12/2024

## Introduction

Up till now, you've written programs that took their input from the user through the console, and that printed their output to the console.
This is fine for many programs, but sometimes you want to read input from a file, or write output to a file.
This week, you will learn how to do this in C, using the standard I/O library.

### Code organization

The code for this tutorial is organized as follows: the `CMakeLists.txt` file in the root of the archive is used to build all the programs in the tutorial.
It builds a separate executable for each activity, and the source code for each activity is in a separate `.c` file.

If you did not install `CMake` and a working compiler on Windows, then make sure to open VS Code from the WSL terminal by typing `code .` in the directory that contains the main `CMakeLists.txt` file.
Use the CMake tab (listed on the left, along with other tabs for "Explorer", "Extensions", etc.) in VS Code to configure, build, run and debug the different targets in the project.

## Opening and closing files

To open a file in C, you use the `fopen` function.
This function takes two arguments: the name of the file you want to open, and the **mode** in which you want to open the file.
The mode is a string that specifies whether you want to read from the file, write to the file, or both.
The most common modes are:

* `"r"`: open the file for reading.
* `"w"`: open the file for writing. If the file already exists, it is truncated to zero length. If the file does not exist, it is created.
* `"a"`: open the file for writing. If the file already exists, the file pointer is set to the end of the file. If the file does not exist, it is created.

Note that the file must be in the same directory as the program, or you must specify the full path to the file.
For example, to open a file called `example.txt` for reading, you would write:

```c
FILE *file = fopen("example.txt", "r");
```

If the file could not be opened, `fopen` returns `NULL`.
You should always check the return value of `fopen` to make sure the file was opened successfully.

### Activity 1 - Opening a file

The program listed in `activity1.c` asks the user for a filename, but does not actually open the file.
Complete the program by letting it open the file for _reading_.
If the file was opened successfully, print a message to the console to indicate this.
If the file could not be opened, print an error message.

Test whether the program works by letting it open the file `example.txt` that is included in the archive.
**NOTE** when using CMake, you're probably running the program from the `build` directory, so you need to specify the path to the file relative to the `build` directory.

When your program can open the file `example.txt` (or any other file) successfully, paste the contents of your program in the code block below:

```c
// TODO: Paste your code here
#include <stdio.h>
#include "functions.h"

int main(void) {
    char filename[100];
    printf("Enter the name of the file: ");
    read_string(filename, sizeof(filename));

    // TODO: try opening the filename for reading
    FILE *file = fopen(filename, "r");
    //       print "File opened successfully." if the file was opened
        if(file != NULL){
            printf("File %s opened successfully.\n", filename);
            
            fclose(file);
        }
    //       print "Failed to open file." if the file was not opened
        else{
            printf("Failed to open file.\n");
        }
    return 0;  
}


```

## Writing to files using `fprintf`

### Activity 2 - Writing to a file

The program listed in `activity2.c` asks the user for a filename, but does not actually do anything with the file.
The program then repeatedly asks the user to enter a string, and stops when the user enters an empty string.
Change the program so that it writes each string entered by the user to a separate line of the file that was specified by the user.
The program must close the file before it exits.

Test whether the program works by letting it write to a file called `output.txt`.
Verify that the file indeed contains the strings that you entered.

When your program writes the strings to the file correctly, paste the contents of your program in the code block below:

```c
// TODO: Paste your code here
#include <stdio.h>
#include "functions.h"
#include <string.h>

int main(void) {
    char buffer[100];
    printf("Enter the name of the file: ");
    read_string(buffer, sizeof(buffer));

    // TODO: open the filename for writing
    FILE *file = fopen(buffer, "w");
    //       print "Failed to open file." if the file could not be opened
    if(file == NULL){
        printf("Failed to open file.\n");
        return 1;
    }
    
    do {
        printf("Enter a string: ");
        read_string(buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            // TODO: write the string to the file using fprintf
            fprintf(file, "%s\n", buffer);
        }
    }
    while (strlen(buffer) != 0);

    // TODO: close the file
    fclose(file);
}


```

## Reading files using `fscanf`

To read from a file, there are multiple functions you can use.
The `fgetc` function reads one character at a time from a file, including whitespace (spaces, tabs, newlines, etc.) characters.
The `fgets` function reads an entire line from a file, including the newline character at the end of the line.

The `fscanf` function reads _formatted input_ from a file, which means that you can specify the format of the data you want to read.
For example, if you would like to read an integer from a file, you can use the following code:

```c
int number;
int result = fscanf(file, "%d", &number);
```

This code will try to interpret the next characters in the file as an integer, and store the result in the variable `number`.
It may fail if the next characters in the file are not an integer, or if the file is at the end.
To see whether it actually succeeded, you should check the return value of `fscanf`: the `result` variable will be equal to `1` if the integer was read successfully.

### Activity 3 - Reading integers from a file

Write a program in `activity3.c` that reads all integers from the file `numbers.txt`, and prints their sum to the console.

When you're done and your program successfully prints the sum of the integers in `numbers.txt`, paste the contents of your program in the code block below:

```c
// TODO: Paste your code here
#include <stdio.h>
#include "functions.h"

int main(void) {
    const char *filename = "../numbers.txt";
    int sum = 0;

    printf("Reading numbers from %s...\n", filename);

    // TODO: open the file numbers.txt for reading
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Failed to open file\n");
        return 1;
    }
    //       sum all the numbers in the file
    int number;
    while(fscanf(file, "%d", &number) == 1){
        sum += number;
    }
    // TODO: close the file
    fclose(file);

    printf("The sum of the numbers is %d.\n", sum);
    return 0;
}
```

## Standard input and output

In C, there are three standard "files" that are automatically opened when your program starts: `stdin`, `stdout`, and `stderr`.
These files are used for standard input, standard output, and standard error output, respectively.
You do not need to open these files, they are already open when your program starts.
For example, to write a string to the console, you can use the `fprintf` function instead of `printf`.
Likewise, to read from the console, you can use the `fscanf` function, instead of `scanf`, which does the same thing but reads from `stdin` implicitly.

```c
fprintf(stdout, "Enter an integer: ");
int number;
int result = fscanf(stdin, "%d", &number);
```

## End of file

When you read from a file, you need to know when you've reached the end of the file.
The `feof` function can be used to check if the end of the file has been reached.
If you do not check for the end of the file, your program may end up in an infinite loop, because `fscanf` will keep trying to read from the file even when there is no more data.

Even the standard input "file" has an end: when you press `Ctrl+D` on Linux or macOS, or `Ctrl+Z` on Windows, the end of the file is reached.

### Activity 4 - Reading from standard input

The program in `activity4.c` repeatedly asks the user to enter a single word, then prints its reverse and checks if the word is a palindrome (a paldindrome is a word that is the same when reversed, such as "racecar" or "level").
The program never stops asking the user for input, so you need to add a way to stop the program.
Do this by changing all occurrences of `scanf` to `fscanf`, and check for the end of the file using `feof` after each input.
When the end of the file is reached, the program should print a message and exit.

When you're done and your program works as expected, paste the contents of your program in the code block below:

```c
// TODO: Paste your code here
#include <stdio.h>
#include "functions.h"
#include "stringfun.h"

int main(void) {
    char buffer[100];
        // TODO: this program never stops.
        const char *filename = "../palindromes.txt";

        FILE *file = fopen(filename, "w");
        if(file == NULL){
            printf("Failed to open file\n");
            return 1;
        }
    //       Fix the program so that it stops when the end-of-file is reached on stdin
    while (1) {
        printf("Enter a word: ");
        if(fscanf(stdin, "%99s", buffer) != 1){ //no need to close 'cause only stdin is used
            if(feof(stdin)){
                printf("End of file detected. Exiting program\n");
                return 1;
            } else {
                printf("Error reading input. Exiting program\n");
                return 1;
            }   
        } 
        reverse(buffer);
        printf("Reversed: %s (palindrome: ", buffer);
        if (is_palindrome(buffer)) {
            printf("yes)\n");
        } else {
            printf("no)\n");
        }
    }
    return 0;
}

```

## Reading until the next newline

Text files are typically processed line by line.
Lines are separated by newline characters (`'\n'`), and you can read an entire line from a file using the `fgets` function.
This will read characters from the file into a character-array buffer until a newline character is encountered, or until the buffer is full.
Note that the function stores the newline character as well, so you may need to remove it if you don't want it.
This can be done by searching for the newline character in the buffer, and replacing it with a null character (`'\0'`).
Instead of writing a loop to do this, you can use the `strrchr` function from the `string.h` library to find the last occurrence of a character in a string.

The `fgets` function is kind of similar to the `read_string` function from `functions.h` that you've used in the previous weeks.
It takes three arguments: the buffer to store the characters in, the size of the buffer, and the file to read from.
It returns `NULL` when no characters could be read (for example because the end of the file was reached).

For example, to read an entire line from the console (standard input), you can use the following code:

```c
char buffer[100];
char *result = fgets(buffer, sizeof(buffer), stdin);
```

### Activity 5 - Reading entire lines

The program in `activity5.c` is similar to the program of activity 4, but it reads its input from a file that the user specifies.

Change the program so that it reads **entire lines** from the file instead of individual words.
Make sure that the program works correctly - it should correctly print the reverse of each line, and correctly determine if the line is a palindrome.

Test your program by letting it read the palindromes from "palindromes.txt".
When you're done and your program works as expected, paste the contents of your program in the code block below:

```c
// TODO: Paste your code here
#include <stdio.h>
#include <stdbool.h>
#include "functions.h"
#include "stringfun.h"
#include <string.h>

int main(void) {
    char buffer[100];
    printf("Enter the name of the file: ");
    read_string(buffer, sizeof(buffer));

    FILE *file = fopen(buffer, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s.\n", buffer);
        return 1;
    }

    // FIXME: this program reads one word at a time, but it should read one line at a time
    //        Fix the program so that it reads one line at a time, using fgets
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *ptr = strchr(buffer, '\n');
        if(ptr != NULL) *ptr = '\0';
        
        printf("%s -> ", buffer);
        reverse(buffer);
        printf("%s (palindrome: ", buffer);
        if (is_palindrome(buffer)) {
            printf("yes)\n");
        } else {
            printf("no)\n");
        }
    }
    fclose(file);
    return 0;
}
```

## Specifying scansets in `fscanf`

As you've seen before, the `%s` format specifier in `fscanf` reads a string of characters until it encounters whitespace.
Sometimes, you want to read a string that only consists of certain characters.
To do this, you can specify a _scanset_ in the format string.
This is done by enclosing the characters you want to read in square brackets (`[]`).

For example, to read a string that only consists of vowels, you can use the following code:

```c
char buffer[100];
int result = fscanf(file, "%99[aeoiuAEOIU]", buffer);
```

This code will read the next (up to 99) characters from the file and copy them to the buffer, but only if they are vowels.
In other words, it will stop as soon as it encounters a character that is not a vowel.

Should you want to read a string that consists of all characters _except_ vowels, you can use the following code:

```c
char buffer[100];
int result = fscanf(file, "%99[^aeoiuAEOIU]", buffer);
```

Here, the `^` character is used to **negate** the scanset, meaning that the string will be read until a vowel is encountered.

### Activity 6 - Reading comma-separated values

The program in `activity6.c` reads a line of text that contains comma-separated values, and prints each value on a separate line.
However, since the program does not treat the commas as delimiters, it will read the entire line as one string.

For example, suppose that the line of text that is entered looks like this: `hello,world,how,are,you,?`.
The program should then print:

```
hello
world
how
are
you
?
```

Change the program so that it reads each value separately, and prints them on separate lines.
Although you can solve this in multiple ways, try using the scanset feature of `fscanf` to read the values.

When you're done and your program works as expected, paste the contents of your program in the code block below:

```c
// TODO: Paste your code here
#include <stdio.h>
#include <stdbool.h>
#include "stringfun.h"

int main(void) {
    char buffer[100];
    printf("Enter a line of text: ");
    
    // read a string until the next newline or space
    while (fscanf(stdin, " %99[^,]", buffer) == 1) {
        printf("%s\n", buffer);
            
        int ch = getchar();// to consume all of the ',' to ch
        if(ch != ','){
            break;
        }
    }
    return 0;
}
  
```

## The `sscanf` function

The `sscanf` function is similar to `fscanf`, but it reads from a string instead of a file.
It has the same number of parameters as `fscanf`, but the first parameter is a string instead of a file.

This can be useful if you have read an entire line of text from a file, and you want to extract values from that line.
For example, to check if a line contains only a single integer, you can use the following code, which checks if there is a trailing character after the integer:

```c
const char *line = "123abc";
int number;
char trailing;
int result = sscanf(line, "%d %c", &number, &trailing);
if (result == 1) {
    printf("The line contains an integer: %d\n", number);
} else {
    printf("The line does not contain an integer\n");
}
```

### Activity 7 - Scanning strings

The program in `activity7.c` reads lines of text from the console (standard input), and checks if the line contains a computation in the form of `number operator number` (accepted operators are `+`, `-`, `*`, and `/`).
If that is the case, the program computes the answer and prints it.

It then calls the `parse_computation` function, which checks if the line contains a computation in the form of `number operator number` (for example, `5.1 + 3.2`).
The function does not do anything useful yet, so you need to change it so that it stores the two numbers and the operator at the memory addresses that are passed to the function.
It must return `true` if the line contains a computation, and `false` otherwise.

When you're done and your program works as expected, paste the contents of your program in the code block below:

```c
// TODO: Paste your code here
 #include <stdio.h>
#include <stdbool.h>
#include "stringfun.h"

/// @brief Parses a computation (i.e. 3.5 * -2.7) from a string.
/// @param line the string to parse.
/// @param left address to store the left operand
/// @param right address to store the right operand
/// @param op address to store the operator
/// @return true if the computation was parsed successfully, and false otherwise.
bool parse_computation(const char* line, float *left, float *right, char *op) {
    if (line == NULL) return false;
    *left = *right = 0.0f;

    if(sscanf(line, " %f %c %f", left, op, right) == 3){
        if (*op != '+' && *op != '-' && *op != '*' && *op != '/') return false; // check if operator is valid
    }
    return true;
}

/// @brief Calculates the result of a computation.
/// @param left left operand
/// @param right right operand
/// @param op operation to perform
/// @return the result
float calculate(float left, float right, char op){
    if (op == '+') return left + right;
    else if (op == '-') return left - right;
    else if (op == '*') return left * right;
    else if (op == '/') return left / right;
    else return 0.0f;
}

int main(void) {
    char buffer[100];
    float left, right;
    char op;

    printf("Enter a computation: ");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (parse_computation(buffer, &left, &right, &op)) {
            fprintf(stdout, "%.2f %c %.2f = %.2f\n", left, op, right, calculate(left, right, op));
        }
        else {
            printf("Invalid computation. Try again: ");
        }
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

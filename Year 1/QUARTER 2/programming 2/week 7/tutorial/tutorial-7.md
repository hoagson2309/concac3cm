# Week 7 - Tutorial: Command-line arguments

Name: SON CAO

Group: ETI1V.IA

Date: 7/1/2025

## Introduction

Functions are the building blocks of any program, and they can be used to create more complex programs by combining them in various ways.
Programs, however, can be regarded as functions themselves - they take input, perform some operations, and produce output.
In all of the previous weeks, this input was provided by the user through the console, and the output was typically printed to the console as well.

Programs can take arguments, similar to functions.
These arguments are provided by the user when the program is started, and they can be used to influence the behavior of the program.
For example, a program that calculates the sum of two numbers could take these two numbers as arguments, so that the user doesn't have to enter them through the console.
You've already passed arguments to programs whenevery you've run the `gcc`, `cd` or `ls` commands in the terminal.
In this tutorial, you will learn how to access these arguments in your own programs.

### Code organization

The code for this tutorial is again organized as follows: the `CMakeLists.txt` file in the root of the archive is used to build all the programs in the tutorial.
It builds a separate executable for each activity, and the source code for each activity is in a separate `.c` file.

If you did not install `CMake` and a working compiler on Windows, then make sure to open VS Code from the WSL terminal by typing `code .` in the directory that contains the main `CMakeLists.txt` file.
Use the CMake tab (listed on the left, along with other tabs for "Explorer", "Extensions", etc.) in VS Code to configure, build, run and debug the different targets in the project.

## Accessing command-line arguments

When a program is started from the command line, the user can provide arguments to the program.
These arguments are passed by simply typing them after the program name, separated by spaces.
For example, to run a program called `my_program` with the arguments `arg1`, `arg2`, and `arg3`, the user would type `./my_program arg1 arg2 arg3`.

In C, the arguments are passed to the `main` function as parameters.
This does mean that the `main` function has a different signature than the functions you've seen so far.
The `main` function can have two different signatures, depending on whether you want to access the arguments or not.
The two signatures are:

```c
int main(void);
int main(int argc, char *argv[]);
```

The first signature is used when you don't want to access the arguments, the second when you do.

The `argc` parameter of the `main` function, is the _number of arguments_ passed to the program.
The second parameter, `argv`, is an array of strings (i.e. `char *`), where each element is one of the arguments passed to the program.

One thing to note is that the first element of the `argv` array is always the name of the program itself.
This means that if the user runs the program `./my_program arg1 arg2 arg3`, then `argc` will be `4`, and `argv` will be an array of strings containing `./my_program`, `arg1`, `arg2`, and `arg3`.

### Activity 1 - Print command-line arguments

File `activity1.c` contains a simple program that accepts no arguments and prints "Hello, world!" to the console.
Modify the program so that it prints all the arguments passed to the program, one argument per line.

When you're done, include the contents of the `activity1.c` file in the code block below.

```c
// TODO: Include the contents of the activity1.c file here
#include <stdio.h>

int main(int argc, char *argv[]){
    //loop and print each argument
    for(int i = 0; i < argc; i++){
        printf("Argument %d: %s\n",i ,argv[i]);
    }
    return 0;
}

```

## Using positional arguments

Programs can take both "mandatory" and "optional" arguments.
Mandatory arguments are arguments that must be passed to the program, while optional arguments are arguments that can be omitted.
A common way to pass mandatory arguments to a program is by using _positional arguments_.
These are arguments that are passed to the program in a specific order (hence the name "positional argument", as their position matters).

You could say that functions in C only accept positional arguments, as the order of the arguments passed to a function must match the order of the parameters in the function definition.

### Activity 2 - Filename arguments

The program listed in `activity2.c` asks the user for a filename, and then prints the contents of the file to the console, with each line prefixed by the line number.
Modify the program so that the filename is passed as an argument to the program, instead of asking the user for it.

When you're done, include the contents of the `activity2.c` file in the code block below.

```c
// TODO: Include the contents of the activity2.c file here
#include <stdio.h>
#include <string.h>

void read_string(FILE* file, char buffer[], size_t size) {
    fgets(buffer, size, file);
    char *ptr = strrchr(buffer, '\n');
    if (ptr != NULL) {
        *ptr = '\0';
    }
}

int main(int argc, char *argv[]){
    //check if filename is provided as a command-line argument
    if(argc < 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", filename);
        return 1;
    }

    int line_number = 1;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%3d: %s", line_number, buffer);
        line_number++;
    }

    fclose(file);

    return 0;
}

```

## Using simple named arguments: flags

Optional arguments are typically passed as _named arguments_.
These are arguments that are passed to the program in the form of `--name value`, or `--name=value`.
Named arguments are more flexible than positional arguments, as they can be passed in any order, and they can be omitted.
They are also called _options_.

Named arguments can often be specified in two ways: a _long form_ and a _short form_.
The long form is typically a word or a phrase that describes the option, while the short form is a single character that is used as a shorthand.
For example, the long form of an option that prints the version of a program could be `--version`, while the short form could be `-v`.
Conventions for the short form of options are that they are prefixed with a single `-` character, while the long form is prefixed with `--`.

Flags are simple options that do not take a value - they are either passed or not, and their presence indicates a certain behavior.
When using short form flags, they are typically combined into a single argument.
For example, if a program has two flags, `--verbose` and `--debug`, the user could pass them as `-vd`, instead of `-v -d`.

To let your program accept named arguments, you will need to parse the `argv` array yourself.
This means that you will need to iterate over the array, and check if an element is a named argument, by checking if it starts with `--` or `-`.
If it is, you will need to extract the value of the argument from the next element in the array.

Note that the above assumes that positional arguments can never start with a `-` character, which is of course not always the case.
To handle these cases (which are rare), a special character (e.g. `--`) is used to mark the end of the named arguments, so that the remaining arguments are always treated as positional arguments.

For example, to create a file named `-hello` with the utility `touch`, you would type `touch -- -hello`.
Not including the `--` would result in an error, as `touch` would interpret `-hello` as an option that it does not recognize.

To obtain _only_ the positional arguments passed to a program, you can use the following function:

```c
size_t find_positional_arguments(char *argv[], char *positional_arguments[]) {
    size_t i = 1;       // index of the first argument to check
    size_t positional_argument_count = 0;
    while (argv[i] != NULL) {                   // while there is one more argument
        if (strcmp(argv[i], "--") == 0) {
            // remaining arguments are positional arguments
            while (argv[++i] != NULL) { positional_arguments[positional_argument_count++] = argv[i];
            break;  // stop parsing the arguments
        }
        else if (argv[i][0] != '-') {           // if the argument does not start with '-', it is a positional argument
            positional_arguments[positional_argument_count++] = argv[i];
        }
        i++;    // move to the next argument
    }
}
    return positional_argument_count;
//argv[i][0]
//Refers to the first character of the i-th argument string.
//Example:
//For argv[1] = "-o", argv[1][0] → '-' (the first character).
//For argv[2] = "output.txt", argv[2][0] → 'o'
}
```

Note that this function only works in case there are only positional arguments and the only named arguments are flags.
In case there are also named arguments that take values, you will need to modify the function to handle these cases as well.

### Activity 3 - Printing number of alphabet characters

The program listed in `activity3.c` asks the user for a filename, and whether the user wants to print the contents of each line, or print only the number of lowercase or uppercase characters in each line.
Modify the program so that it does not interact with the user at all, but instead accepts a single positional argument (the name of the file to read), and at most two flags:

- `--lower` (long form) or `-l` (short form) that, when passed, will cause the program to print the number of lowercase (alphabet) characters in each line.
- `--upper` (long form) or `-u` (short form) that, when passed, will cause the program to print the number of uppercase (alphabet) characters in each line.

If either of these flags is passed, the program must not print the contents of the file, but only the number of characters of the specified type in each line.
The program must accept a combination of both flags (e.g. `./activity3 -lu file.txt` or `./activity3 -ul file.txt`), or separate flags (e.g. `./activity3 -l -u file.txt`).

Use the `find_positional_arguments` function given above to extract the positional arguments from the `argv` array.
Note that you'll need to allocate memory (use the fact that the size is at most `argc - 1`) for the positional arguments array, as the function does not know how many positional arguments there are.
Make sure your program works by running it with the following commands:

```sh
./activity3 -- --test.txt
./activity3 -u alice.txt
./activity3 -lu alice.txt
```

When you're done, include the contents of the `activity3.c` file in the code block below.

```c
// TODO: Include the contents of the activity3.c file here
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>


size_t find_positional_arguments(char *argv[], char *positional_arguments[]);

/// @brief Reads a string from a file and removes the newline character.
/// @param file The file to read from.
/// @param buffer The buffer to store the string in.
/// @param size The size of the buffer.
void read_string(FILE* file, char buffer[], size_t size);

/// @brief Reads a yes or no response from the user.
/// @param prompt The prompt to display to the user.
char read_yes_no(const char *prompt);

/// @brief Counts the number of uppercase and lowercase characters in a string.
/// @param buffer The string to count the characters in.
/// @param upper A pointer to store the number of uppercase characters.
/// @param lower A pointer to store the number of lowercase characters.
void count_upper_lower(const char *buffer, int *upper, int *lower);

int main(int argc, char *argv[]) {
    if(argc < 2){
        fprintf(stderr, "Usage: %s [-l|--lower] [-u|--upper] <filename>\n", argv[0]);
        return 1;
    }
    
    //check for flags
    bool print_lower = false;
    bool print_upper = false;

    //allocate memory for positional arguments
    char **positional_argument = malloc((argc - 1) * sizeof(char *)); //argc - 1 to avoid wasting memory as argc[0] is always a program name not positional argument
    if(!positional_argument){                                         //Use char **positional_arguments when you need dynamic memory allocation for the array and flexibility in handling its size.
        fprintf(stderr, "Memory allocation failed.\n");               //Use char *positional_arguments[] when the size is fixed and known at compile time, or for array declarations in function signatures.
        return 1;
    }

    //parse the command-line arguments
    size_t positional_argument_count = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lower") == 0){ // strcmp == 0 means equal, matched
            print_lower = true;
        }
            
        else if(strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--upper") == 0){
            print_upper = true;
        }

        else if(strcmp(argv[i], "--") == 0){
            positional_argument_count = find_positional_arguments(argv + i, positional_argument);
            break;
        }

        else if(argv[i][0] !=  '-'){ // remember ' ' not " " (because  this is a character not a string)
            positional_argument[positional_argument_count++] = argv[i];
        }
    }

    //validate positional arguments
    if(positional_argument_count < 1){
        fprintf(stderr, "Usage: %s[-l|--lower] [-u|--upper] <filename>\n", argv[0]);
        free(positional_argument);
        return 1;
    }

    const char *filename = positional_argument[0];

    //open the file     
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", filename);
        free(positional_argument);
        return 1;
    }

    int line_number = 1;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {   
        int upper = 0, lower = 0;
        count_upper_lower(buffer, &upper, &lower);
        printf("%3d: ", line_number);
        if (print_lower && print_upper) printf("lowercase: %d, uppercase: %d\n", lower, upper);
        else if (print_lower) printf("lowercase: %d\n", lower);
        else if (print_upper) printf("uppercase: %d\n", upper);
        else printf("%s", buffer);
        line_number++;
    }

    fclose(file);

    free(positional_argument);

    return 0;
}

size_t find_positional_arguments(char *argv[], char *positional_arguments[]) {
    size_t i = 1; //index of the first argument to check
    size_t positional_arguments_count = 0;
    while(argv[i] != NULL){
        if(strcmp(argv[i], "--") == 0){ //==0 => matched
            while(argv[++i] != NULL){
                positional_arguments[positional_arguments_count++] = argv[i];
            }
            break;
        } else if (argv[i][0] != '-'){
            positional_arguments[positional_arguments_count++] = argv[i];
        }
        i++;
    }
    return positional_arguments_count;
}


void read_string(FILE* file, char buffer[], size_t size) {
    fgets(buffer, size, file);
    char *ptr = strrchr(buffer, '\n');
    if (ptr != NULL) {
        *ptr = '\0';
    }
}

void count_upper_lower(const char *buffer, int *upper, int *lower) {
    *upper = 0;
    *lower = 0;
    for (; *buffer != '\0'; buffer++) {
        if (isupper(*buffer)) {
            (*upper)++;
        } else if (islower(*buffer)) {
            (*lower)++;
        }
    }
}

```

## Using named arguments with values

Whereas flags are simple options that are either passed or not, options with values are options that require a value to be passed.
For example, an option that specifies the number of lines to print, or the filename of a file to read.
Options with values are typically passed as `--name value`, or `--name=value`.

To let your program accept options with values, you will need to parse the `argv` array yourself, similar to how you would parse flags.
The difference is that you will need to extract the value of the option from the same element in the array, instead of the next element.
In case a space is used to separate the option and the value, the value will be in the "next" element in the `argv` array.
This means that you'll need to deal with the case where the value is not present, or where the value is not a valid value for the option.

To simplify the parsing of options with values

A typical way to parse options with values is to use a `while` or `for` loop to iterate over the `argv` array, and an `if` statement to check if an element is a (valid) option.
For example, suppose that a program accepts two named arguments: `--option N` that takes an integer value `N`, and `--name S` that takes a string value `S`.
The following code snippet shows how you could parse these options:

```c
int i = 1;
while (argv[i] != NULL && strcmp(argv[i], "--") != 0) {
    if (strcmp(argv[i], "--option") == 0) {
        if (argv[i + 1] != NULL) {
            if (sscanf(argv[i + 1], "%d", &value) == 1) {
                // Handle the option with value
                i++;    // skip the value
            }
            else {
                // Handle the case where the value for --option is not a valid value
            }
        }
        else {
            // Handle the case where the value for --option is not present
        }
    }
    else if (strcmp(argv[i], "--name") == 0) {
        if (argv[i + 1] != NULL) {
            char *value = argv[i + 1];
            // Handle the option --name with value
            i++;    // skip the value
        }
        else {
            // Handle the case where the value for --name is not present
        }
    }
    else if (argv[i][0] == '-') {
        // Handle the case where an invalid option is passed
    }
    else {
        // Handle the case where the argument is a positional argument
    }
    i++;    // move to the next argument
}
```

### Activity 4 - Limiting the number of characters per line

The program listed in `activity4.c` asks the user for a filename, and then asks the user for the number of characters to print per line.
The program then prints the contents of the file to the console, restricting the number of characters per line to the number specified by the user.

Modify the program so that it takes both a positional argument and a named argument: the number of characters to print per line is passed as a named argument to the program, and the filename is passed as a positional argument.
The long form of the named argument must be `--chars N`, its short form `-c N`, and its value (`N`) must be an integer.
If the argument is not passed, the program must print every line in full.

When you're done, include the contents of the `activity4.c` file in the code block below.

Make sure that the program works when the argument is passed in any order.
That is, the following two invocations of the program should both work:

```sh
./activity4 --chars 5 -- --test.txt
./activity4 alice.txt -c 15
```

```c
// TODO: Include the contents of the activity4.c file here
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// @brief Reads a string from a file and removes the newline character.
/// @param file The file to read from.
/// @param buffer The buffer to store the string in.
/// @param size The size of the buffer.
/// @return The buffer containing the string read from the file, or NULL if an error occurred.
char *read_string(FILE* file, char buffer[], size_t size);

/// @brief Reads an integer from the user.
/// @param prompt The prompt to display to the user.
/// @return The integer read from the user.
int read_int(const char *prompt);


/// @brief Parses command line arguments for the filename and character limit.
/// @param argc The number of arguments.
/// @param argv The array of argument strings.
/// @param chars The number of characters per line.
/// @param filename The filename to be processed.
/// @return 1 if successful, 0 if there was an error.
int parse_arguments(int argc, char *argv[], int *chars, char *filename);

int main(int argc, char *argv[]) {

    int chars = -1; //default: unlimited characters per line

    char filename[100];

    //parse arguments
    if(!parse_arguments(argc, argv, &chars, filename)){
        return 1;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", filename);
        return 1;
    }

    char buffer[100];
    while (read_string(file, buffer, sizeof(buffer)) != NULL) { //calls the read_string function to read a line from the file into buffer.
        if (chars > 0 && chars < sizeof(buffer)) buffer[chars] = '\0';
        printf("%s\n", buffer);
    }

    fclose(file);

    return 0;
}

char *read_string(FILE* file, char buffer[], size_t size) {
    if (fgets(buffer, size, file) == NULL) return NULL;
    char *ptr = strrchr(buffer, '\n');
    if (ptr != NULL) *ptr = '\0'; //remove newline character if exists
    return buffer;
}

int parse_arguments(int argc, char *argv[], int *chars, char *filename) {
    for (int i = 1; i < argc; i++) {
        //check for named arguments (-c or --chars)
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--chars") == 0) {
            if (i + 1 < argc && sscanf(argv[i + 1], "%d", chars) == 1) { //the next argument can be parsed as an integer.(That next argument is a valid integer)
                i++;  //skip the next argument (the number for -c or --chars)
            } else {
                fprintf(stderr, "Error: Please provide an integer after -c or --chars\n");
                return 0;
            }
        } 
        //check for positional argument (filename)
        else if (strcmp(argv[i], "--") == 0) {
            if (i + 1 < argc) {
                //the first argument after "--" is the filename (positional argument)
                strcpy(filename, argv[i + 1]);
                i++;  //skip the next argument which is the filename
            } else {
                fprintf(stderr, "Error: Missing filename after '--'\n");
                return 0;
            }
        } 
        else {
            strcpy(filename, argv[i]);//if the current argument (argv[i]) is not -- and has not been parsed as a named argument, it is treated as the filename.
        }
    }
    
    if (strlen(filename) == 0) {
        fprintf(stderr, "Error: No filename provided.\n");
        return 0;
    }
    
    return 1;
}
```

## Redirecting input and output

A program can read input from the console, and write output to the console.
However, it can also read input from a file, and write output to a file.
This is done by _redirecting_ the input and output of the program.

When a program is started from the command line, the user can redirect the input and output of the program.
This is done by using the `<` and `>` operators.
For example, to redirect the output of a program called `my_program` to a file called `output.txt`, the user would type `./my_program > output.txt`.
To redirect the input of a program to a file called `input.txt`, the user would type `./my_program < input.txt`.

Programs can also read input from the output of another program.
This is done by _piping_ the output of one program to the input of another program.
This is done by using the `|` operator.
For example, to pipe the output of a program called `my_program1` to the input of a program called `my_program2`, the user would type `./my_program1 | ./my_program2`.

### Activity 5 - Shuffling a list of numbers

The program listed in `activity5.c` asks the user to enter a list of numbers (ended with a zero), then shuffles the list and prints the result.
Change the program so that it stops as soon as the end of the `stdin` file (`eof`) is reached.
At this point, the program must shuffle the list of numbers and print the shuffled list to the console, one number per line.

Run the program `./activity5 < numbers.txt > shuffled_numbers.txt` to shuffle the numbers in the file `numbers.txt` and write the shuffled numbers to the file `shuffled_numbers.txt`.

When you're done, paste the contents of the `shuffled_numbers.txt` file in the markdown file.

```txt
// TODO: Include the contents of the shuffled_numbers.txt file here
7
29
23
12
5
2
18
20
8
-9
9
-10
1
13
-4
15
-7
19
-3
3
5
-1
19
2
11
-2
16
17
4
10
7
11
3
-6
17
-5
13
-8
14
6

```

### Activity 6 - Processing output from another program

The program `activity6.c` asks the user for a filename, then reads all the numbers from the file, and prints them to the console, in tabular form, with 10 numbers per row.

Modify the program so that it can be used in a pipeline with the `activity5` program.
In other words, running `./activity5 < numbers.txt | ./activity6` should display the numbers after shuffling them.

When you're done, include the contents of the `activity6.c` file in the code block below.

```c
// TODO: Include the contents of the activity6.c file here
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// @brief Reads a string from a file and removes the newline character.
/// @param file The file to read from.
/// @param buffer The buffer to store the string in.
/// @param size The size of the buffer.
/// @return The buffer containing the string read from the file, or NULL if an error occurred.
char *read_string(FILE* file, char buffer[], size_t size);

/// @brief Reads the next integer from a file, skipping non-numbers
/// @param file The file to read from.
/// @return The integer read from the file.
/// @return true if an integer was read, false if the end of the file was reached.
bool read_int(FILE *file, int *value);

int main(void) {
    const int num_columns = 10;

    int number;
    int column = 0;

    //read interger from stdin (no nead for filename)
    while (read_int(stdin, &number)) {
        printf("%10d", number); //print the number with the width of 10
        column = (column + 1) % num_columns;
        if (column == 0) printf("\n");
    }

    printf("\n");  //ensure a newline at the end if the last line doesn't have 10 numbers
    return 0;
}

char *read_string(FILE* file, char buffer[], size_t size) {
    if (fgets(buffer, size, file) == NULL) return NULL;
    char *ptr = strrchr(buffer, '\n');
    if (ptr != NULL) *ptr = '\0';
    return buffer;
}

bool read_int(FILE *file, int *value) {
    char buffer[100];
    int result = fscanf(file, "%99s", buffer);
    while (result != EOF && sscanf(buffer, "%d", value) == 0) {
        result = fscanf(file, "%99s", buffer);
    }
    return result != EOF;
}

```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will get in touch with you.

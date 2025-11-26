# Week 6 - Tutorial: Function pointers

Name: SON CAO

Group: ETI1V.IA

Date: 18/12/2024

## Introduction

The _programming 2_ module is all about pointers - you've worked with various types of pointers, such as pointers to variables, structures and arrays.
This week it's time for another type of pointer which is quite different from the pointers you've seen so far: function pointers.
Function pointers are exactly that - pointers to functions.
Like regular pointers allow you to indirectly access a variable, function pointers allow you to indirectly call a function.
As a result, you can write general functions that delegate certain tasks to other functions that are passed as arguments.
A common use case for function pointers is to pass a comparison function to a sorting algorithm, so that the algorithm can sort any type of data.

### Code organization

The code for this tutorial is again organized as follows: the `CMakeLists.txt` file in the root of the archive is used to build all the programs in the tutorial.
It builds a separate executable for each activity, and the source code for each activity is in a separate `.c` file.

If you did not install `CMake` and a working compiler on Windows, then make sure to open VS Code from the WSL terminal by typing `code .` in the directory that contains the main `CMakeLists.txt` file.
Use the CMake tab (listed on the left, along with other tabs for "Explorer", "Extensions", etc.) in VS Code to configure, build, run and debug the different targets in the project.

## Calling a function through a function pointer

The declaration of a pointer variable needs some getting used to.
In C, a function's prototype can be specified by only specifying its return value, name, and parameter types - parameter names are not necessary:

```c
int add(int, int);
```

Now, to declare a pointer to a function with the same prototype, you need to put the `*` next to the function name, and enclose the function name in parentheses (because otherwise we would simply define a prototype for a function that returns a pointer to an `int`):

```c
int (*pointer)(int, int);
```

This is in fact declaring a pointer to a function that returns an `int` and takes two `int` arguments.
Because this variable declaration looks so much different from a regular pointer declaration, you may wonder what the name of the variable is that was just declared.
The name of the variable is `pointer` - it's "hidden" in the parentheses, and it thus does not appear on the rightmost side of the declaration like "regular" variables do.

Now that you have declared a function pointer, you can let it store the address of a function that has the same prototype.
For example, to let it store the address of the `add` function, you can write:

```c
int (*pointer)(int, int) = add;
```

To call the function through the function pointer, you can use the same syntax as you would use to call the function directly:

```c
int result = pointer(3, 4); // will give the same result as add(3, 4)
```

### Activity 1 - Function pointers

The program in `activity1.c` contains several functions that take two floating point numbers as arguments and return another floating point number.
There is a function `read_choice` that asks the user which function to call (the user can choose between `add`, `subtract`, `multiply`, and `divide`).
The function returns a function pointer, though the return type may not be immediately clear to you.

The function is not called from the `main` function yet, so there's some work to do.

Your task is to create a variable in the `main` function to hold the result of the `read_choice` function, check whether its value is not `NULL`, and call the function through the function pointer that is returned by the `read_choice` function.
If the function pointer is not `NULL`, you should keep on asking the user (without modifying the `read_choice` function) for a choice until the user makes a valid choice.

When you're done, paste the contents of your program in the code block below:

```c
// TODO: Paste the contents of activity1.c here
#include <stdio.h>
#include "functions.h"

float add(float a, float b) { return a + b; }
float multiply(float a, float b) { return a * b; }
float subtract(float a, float b) { return a - b; }
float divide(float a, float b) { return a / b; }

/// @brief Reads a character from the user and returns the matching function through a pointer
/// @return A function pointer that points to the function that corresponds to the user's choice, or NULL
float (*read_choice(void))(float, float);

int main(void) {
    float a, b;
    char trailing;
    printf("Enter two floating-point numbers: ");
    while (scanf("%f %f %c", &a, &b, &trailing) != 2) {
        printf("Invalid input. Please try again.\n");
        while (getchar() != '\n');  // Process input until the rest of the line
    }
    while (getchar() != '\n');  // Process input until the end of the line

    
    float (*operation)(float, float) = NULL;
    
    while (operation == NULL){
        // TODO: store the result of read_choice in a function pointer.
        operation = read_choice();
        // If the function returns NULL, keep on asking until the user made a valid choice.
        if(operation == NULL){
            printf("Invalid choice. Please try again.\n");
        }
    }
    // TODO: call the function returned by read_choice, passing a and b as arguments.
    float result = operation(a, b);
    // FIXME: print the result of the operation chosen by the user
    printf("The result is: %f\n", result);
}

float (*read_choice(void))(float, float) {
    // NOTE: you're not allowed to change this function!
    printf("Enter the operation (+, -, *, /): ");
    char choice = read_char();
    if (choice == '+') return add;
    else if (choice == '-') return subtract;
    else if (choice == '*') return multiply;
    else if (choice == '/') return divide;
    else return NULL;
}

```

## Using `typedef` to simplify function pointer declarations

The syntax for declaring a function pointer can be quite confusing, and indeed, it is not very readable.
Fortunately, you can use `typedef` to simplify the declaration of function pointers.
Looking back at the example above where we declared a function pointer `pointer` that points to a function that returns an `int` and takes two `int` arguments, you can simplify the declaration as follows:

```c
typedef int function_pointer(int, int);
```

Now, this may look like a function prototype, except for the fact that the `typedef` keyword is used.
Because of this `typedef`, you are actually creating an alias for a function pointer type that can "point to" functions that return an `int` and take two `int` arguments:

```c
function_pointer *pointer = add;
```

### Activity 2 - Simplifying function pointer declarations

The program in `activity2.c` contains a few functions that take functions as arguments, plus a `main` function that calls these functions.
Rewrite every function pointer declaration in the program to a more readable form by introducing a `typedef`.

When you're done, paste the contents of your program in the code block below:

```c
// TODO: Paste the contents of activity2.c here
#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <ctype.h>

/// @brief Applies a function to (the address of) each element of an array.
/// @param array The array to apply the function to.
/// @param size The size of the array
/// @param function The function to apply to each element of the array.
void apply(int *array, size_t size, void (*function)(int *));

/// @brief Checks if a string contains only characters that satisfy a condition.
/// @param string The string to check.
/// @param function The function that checks if a character satisfies a condition.
/// @return true if all characters in the string satisfy the condition, and false otherwise.
bool all(const char *string, bool (*function)(char));

// some functions that could be passed to the "apply" function
void times_two(int *number) { *number *= 2; }
void plus_one(int *number) { *number += 1; }

// some functions that could be passed to the "all" function
bool is_digit(char c) { return isdigit(c); }
bool is_vowel(char c) { return strchr("aeiouAEIOU", c) != NULL; }

//typedef for function pointers
typedef void (*int_function)(int *); //if typedef void int_function(int *); => int_function *pointer = some_function;
typedef bool (*char_function)(char);

int main(void) {
    // TODO: introduce two `typedef`s to simplify the function pointers
    
    // function pointers that can be passed to the "all" function
    char_function vowel_checker = is_vowel;
    char_function digit_checker = is_digit;

    // function pointers that can be passed to the "apply" function
    int_function multiplier = times_two;
    int_function adder = plus_one;

    // array of integers
    int numbers[] = {1, 2, 3, 4, 5};

    // array of strings
    const char *strings[] = {"hello", "world", "123", "abc", "AEIOU"};

    // apply the multiplier function to each element of the "numbers" array
    apply(numbers, sizeof(numbers) / sizeof(numbers[0]), multiplier);

    // apply the adder function to each element of the "numbers" array
    apply(numbers, sizeof(numbers) / sizeof(numbers[0]), adder);

    // go over the strings and run the "all" function on each of them
    for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
        if (all(strings[i], vowel_checker)) {
            printf("All characters in \"%s\" are vowels.\n", strings[i]);
        } else if (all(strings[i], digit_checker)) {
            printf("All characters in \"%s\" are digits.\n", strings[i]);
        } else {
            printf("The characters in \"%s\" are neither all vowels nor all digits.\n", strings[i]);
        }
    }
}

void apply(int *array, size_t size, void (*function)(int *)) {
    for (size_t i = 0; i < size; i++) {
        function(&array[i]);
    }
}   

/// @brief Checks if a string contains only characters that satisfy a condition.
/// @param string The string to check.
/// @param function The function that checks if a character satisfies a condition.
/// @return true if all characters in the string satisfy the condition, and false otherwise.
bool all(const char *string, bool (*function)(char)) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!function(string[i])) return false; // if the function returns false, return false
    }
    return true;    // if the function never returns false, return true
}

```

## Passing functions to other functions

Function pointers are often used to pass functions to other functions.
This allows functions to do their work in a general way, and delegate certain tasks to other functions that are passed as arguments.
For example, suppose we have a function `search` that searches an array for a certain value and returns its position if it was found, or `-1` if it was not found.:

```c
int search(int *array, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) return i;
    }
    return -1;
}
```

This function is specialized to search for an exact match.
However, we could make this function more general by letting it accept a function that "tells" whether the target value was found:

```c
typedef bool found_function(int);

int search(int *array, int size, found_function *found) {
    for (int i = 0; i < size; i++) {
        if (found(array[i])) return i;
    }
    return -1;
}
```

We could call this function with either a function that checks for an exact match, or a function that checks for a match within a certain range, etc.

### Activity 3 - Using a generic character counting function

In `activity3.c`, you will find a program that reads a line of text from the console (standard input).
The file contains a function `count_characters` that counts the number of characters in a string that satisfy a certain condition.
The function takes a string and a function pointer as arguments, and returns the number of characters that satisfy the condition.

The program uses the `count_characters` function to count the number of lowercase characters in the string, but of course it could do more!

Write **two** functions that can be passed to `count_characters`:
- A function that causes `count_characters` to count the number of (lowercase or uppercase) vowels in a string
- A function that causes `count_characters` to count the number of consonants in a string.

Call the `count_characters` function two more times, passing the two functions that you wrote as arguments, so that the program prints the number of vowels in the string, as well as the number of consonants.

If everything works as expected, paste the contents of your program in the code block below:

```c
// TODO: Paste the contents of activity3.c here
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

```

## Working with any kind of data

Although the function pointers you've used in the previous activities are quite powerful, they are limited to only work with specific _typees_ of data.
For example, the `search` function in the previous activity only works with integers.
But the concept of _searching_ goes beyond integers - you could search for a certain string in an array of strings, or search for a certain structure in an array of structures.

To make a function that works with (for example) arrays more generic, we need to abstract from the type of data that is stored in the array.
If we want the function to work with any kind of data, then it basically needs to work with the plain bytes stored in memory.
This is achieved by using `void` pointers: pointers that can point to any kind of data.
In fact, a `void` pointer is nothing more than just a memory address - we can't dereference it directly, because the compiler doesn't know what kind of data it points to.

For example, the following function checks if two values are equal, regardless of their type:

```c
bool equal(const void *a, const void *b, size_t size) {
    const char *pa = (const char*) a;
    const char *pb = (const char*) b;
    for (size_t i = 0; i < size; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}
```

The function takes two `void` pointers and a size as arguments.
It assumes that the two pointers point to two blocks of memory that are each `size` bytes long.
This makes sense, because if the function is used to compare two values of the same type, then the size of the two blocks of memory should be the same.
The function then proceeds to compare the two blocks of memory byte by byte - it casts the pointers to a specific (char) pointer type, so that it can access the individual bytes.

### Activity 4 - Using generic functions

The program partially given in `activity4.c` declares several variables of various types.
It then calls the `swap` function to swap the values of the two integers.
The swap function can't be used to swap the values of the other variables, because it only works with integers.

Change the `swap` function so that it works with any kind of data.
To do this, it will have to accept two `void` pointers, plus a size as arguments - just like the `equal` function above.
Next, the function should swap the contents of the two blocks of memory that the pointers point to, byte by byte.

After you've changed the `swap` function, call it for the other variables in the program so that all variables of the same type are swapped.
If everything works as expected, paste the contents of your program in the code block below:

```c
// TODO: Paste the contents of activity4.c here
#include <stdio.h>
#include "functions.h"

// FIXME: make this function more generic so that it works with any type
void swap(void *a, void *b, size_t size) {
    // TODO: implement this function
    char temp;
    char *pa = (char *)a;
    char *pb = (char *)b;

    for(size_t i = 0; i < size; i++){
        temp = pa[i];
        pa[i]= pb[i];
        pb[i] = temp;
    }
}

int main(void) {
    int int1 = 5, int2 = 10;
    double double1 = 3.14, double2 = 6.28;
    char char1 = 'a', char2 = 'b';
    const char *string1 = "hello", *string2 = "world";

    printf("Before swap:\n");
    printf("  int1 = %d, int2 = %d\n", int1, int2);
    printf("  double1 = %f, double2 = %f\n", double1, double2);
    printf("  char1 = %c, char2 = %c\n", char1, char2);
    printf("  string1 = \"%s\", string2 = \"%s\"\n", string1, string2);

    swap(&int1, &int2, sizeof(int));
    swap(&double1, &double2, sizeof(double));
    swap(&char1, &char2, sizeof(char)); //sizeof(char) is for swapping single characters(1 byte). 
    swap(&string1, &string2, sizeof(char *)); //sizeof(char *) is for swapping pointers to characters (or strings in this case)(4 bytes, 8 bytes). 

    
    printf("After swap:\n");
    printf("  int1 = %d, int2 = %d\n", int1, int2);
    printf("  double1 = %f, double2 = %f\n", double1, double2);
    printf("  char1 = %c, char2 = %c\n", char1, char2);
    printf("  string1 = \"%s\", string2 = \"%s\"\n", string1, string2);
}

```

## Combining function pointers with void pointers

If you think we've reached the limits of what we can do with function pointers and `void` pointers, then think again!
We can take things one step further by combining the two.
This means we can write functions that work with any kind of data, and that can be customized by passing a function pointer as an argument.
For example, we could write a function that sorts an array of any kind of data, and that uses a comparison function to determine the order of the elements.

But this function already exists in the C standard library: `qsort`.
The `qsort` function is a generic sorting function that can sort arrays of any kind of data.
To do so, it needs a comparison function that tells it how to compare two elements.
The comparison function should return a negative value if the first element is smaller than the second, a positive value if the first element is larger than the second, and zero if the two elements are equal.

The prototype of the comparison function is as follows:

```c
int compare(const void *a, const void *b);
```

And the `qsort` function is declared as follows:

```c
typedef compare_function(const void *, const void *);
void qsort(void *base, size_t nmemb, size_t size, compare_function *compare);
```

The last parameter is the comparison function that is needed to compare two elements and find out which of the two should come first.
The `base` parameter is a pointer to the first element of the array, `nmemb` is the number of elements in the array, and `size` is the size of each element in the array.
So if you would like to sort an array of 10 integers, then `base` should point to the first integer, `nmemb` should be 10, and `size` should be `sizeof(int)`.

The comparison function that you pass to `qsort` is called multiple times by `qsort` to compare different pairs of elements.
Two elements are passed by (`const`) _pointer_ to the comparison function, so that the comparison function can access the elements.
This means that in the case where you sort an array of integers, the comparison function will receive two `int` pointers.
Through typecasting, the comparison function can access the actual values of the elements.

### Activity 5 - Sorting an array of doubles

The program in `activity5.c` asks the user how many random floating point numbers to generate, which it then generates, stores into an array, and prints to the console.

Use the `qsort` function to _sort_ the numbers from small to large (i.e. in ascending order).
This means that you will have to write a comparison function that can be passed to `qsort` as the last argument, and compares any two `double` values.
The function will receive two addresses of `double` values, but passed as `void` pointers, so you will have to typecast these pointers to the correct type of pointer.

When you're done - check that the numbers are indeed sorted in ascending order - paste the contents of your program in the code block below:

```c
// TODO: Paste the contents of activity5.c here
#include <stdio.h>
#include <stdlib.h> // for qsort
#include "functions.h"

/// @brief A typedef for the comparison function used in qsort.
typedef int compare_function(const void *, const void *);

/// @brief Prints an array of floats, comma-separated and on a single line.
/// @param array Pointer to the array of floats.
/// @param size The size of the array.
void print_floats(float *array, size_t size);

/// @brief Comparison function for qsort to sort floats in ascending order.
/// @param a Pointer to the first element.
/// @param b Pointer to the second element.
/// @return A negative value if a < b, positive value if a > b, 0 if a == b.
int compare_floats(const void *a, const void *b);

int main(void) {
    printf("How many numbers to generate? " );
    int howmany = read_int();
    while (howmany < 1) {
        printf("Invalid input. Please enter a positive number: ");
        howmany = read_int();
    }

    // allocate memory for the numbers
    float *numbers = (float*) malloc(howmany * sizeof(float));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // generate random numbers
    for (int i = 0; i < howmany; i++) numbers[i] = random_float(0.0f, 100.0f);

    // TODO: sort the numbers using qsort
    qsort(numbers, howmany, sizeof(float), (compare_function *)compare_floats);

    // print the sorted numbers
    print_floats(numbers, howmany);

    free(numbers);  // deallocate
}

void print_floats(float *array, size_t size) {
    if (size > 0) printf("%.2f", array[0]);
    for (size_t i = 1; i < size; i++) {
        printf(", %.2f", array[i]);
    }
    printf("\n");
}

int compare_floats(const void *a, const void *b){
    //cast void pointers to float pointers 
    const float *fa = (const float *)a;
    const float *fb = (const float *)b;

    //return comparison result
    if(*fa < *fb){
        return -1;
    } else if(*fa > *fb){
        return 1;
    } else{
        return 0;
    }
}

```

### Activity 6 - Sorting an array of strings

Because `qsort` can sort arrays of any kind of data, it never hurts to practice a little more.
This time, you will sort an array of strings by their length.

The program in `activity6.c` declares an array of (at most 100) strings, and reads strings from a file into the array.
It then prints all strings to the console.

Use the `qsort` function to sort the strings by their length so that the shortest string comes first.
This again means that you will have to write another comparison function that receives two `void` pointers - the addresses of the two strings.
Be aware that when you typecast these pointers, you cast them to the correct type of pointer!

Sort the strings before they are printed to the console, and make sure that the strings are indeed sorted by length.

When you're done, paste the contents of your program in the code block below:

```c
// TODO: Paste the contents of activity6.c here
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/// @brief Reads strings from a file into an array of strings.
/// @param file The file to read from (must be open for reading).
/// @param strings The array of strings to read into.
/// @param maxsize The maximum number of strings to read.
/// @return The number of strings actually read.
size_t read_words(FILE *file, char *strings[], size_t maxsize);

/// @b  rief Prints an array of strings, breaking lines to keep the line length below a given limit.
/// @param strings The array of strings to print.
/// @param count The number of strings in the array.
/// @param linelength The maximum line length.
void print_strings(char *strings[], size_t count, size_t linelength);

/// @brief Comparison function for qsort to sort strings by length.
/// @param a Pointer to the first string.
/// @param b Pointer to the second string.
/// @return A negative value if the first string is shorter, a positive value if it is longer, or 0 if they are equal in length.
int compare_string_lengths(const void *a, const void *b);

int main(void) {
    char *strings[100] = {NULL}; // array of strings, all initialized to NULL
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file.\n");
        return 1;
    }

    size_t count = read_words(file, strings, sizeof(strings) / sizeof(strings[0]));
    fclose(file);

    // TODO: sort the strings using qsort, so that the shortest strings come first
    qsort(strings, count, sizeof(char *), compare_string_lengths);
    
    print_strings(strings, count, 80);

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
}

size_t read_words(FILE *file, char *strings[], size_t maxsize) {
    char buffer[200];   // buffer for reading strings
    size_t count = 0;
    while (fscanf(file, "%99s", buffer) == 1 && count < maxsize) {
        strings[count] = (char*) malloc(strlen(buffer) + 1);
        if (strings[count] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return count;
        }
        strcpy(strings[count], buffer); // copy the string to the allocated memory
        count++;
    }
    return count;
}

/// @brief Prints an array of strings, breaking lines to keep the line length below a given limit.
/// @param strings The array of strings to print.
/// @param count The number of strings in the array.
/// @param linelength The maximum line length.
void print_strings(char *strings[], size_t count, size_t linelength) {
    size_t end = 0;
    bool first = true;
    for (size_t i = 0; i < count; i++) {
        end += strlen(strings[i]) + 2;
        if (end > linelength) {
            printf("\n");
            end = strlen(strings[i]) + 2;
            first = true;
        }
        if (!first) printf(", ");
        printf("%s", strings[i]);
        first = false;
    }
}


/// @brief Comparison function for qsort to sort strings by length.
/// @param a Pointer to the first string.
/// @param b Pointer to the second string.
/// @return A negative value if the first string is shorter, a positive value if it is longer, or 0 if they are equal in length.
int compare_string_lengths(const void *a, const void *b) {
    const char *const *str_a = (const char *const *)a;
    const char *const *str_b = (const char *const *)b;

    size_t len_a = strlen(*str_a);
    size_t len_b = strlen(*str_b);

    return (int)(len_a - len_b);
}
```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will get in touch with you.

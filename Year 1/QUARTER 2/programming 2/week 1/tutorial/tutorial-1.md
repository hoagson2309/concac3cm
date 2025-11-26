# Week 1 - Tutorial: Memory and pointers 

Name: SON CAO

Group: ETI1V.IA

Date: 14/11/2024

## Introduction

When working with C, understanding how memory is managed is crucial.
This understanding starts with knowing how variables are stored in memory, and how pointers can be used to access and manipulate memory locations.
In this tutorial, you will learn how to use pointers store and manipulate memory addresses, and how to use functions that return and take pointers as arguments.

### Activity 0 - Update the system

Before you start with this tutorial, make sure your system is up-to-date by running the following commands in the terminal:

```bash
sudo apt update
sudo apt upgrade
```

## Using pointers

The following very simple program (also listed in `activity1.c`) declares and initializes an integer variable and prints its value:

```c
#include <stdio.h>

int main(void) {
    int x = 42;
    printf("Value of x: %d\n", x);
    return 0;
}
```

### Activity 1 - Printing memory addresses

Add a line to the program of `activity1.c` to print the _memory address_ of the variable `x`.
Use the _address-of_ operator `&` to get the memory address of the variable, and use the `%p` format specifier to print the memory address.
Run the program five times, and note the memory address of the variable `x` in the table below:

| Run | Memory address |
|-----|----------------|
| 1   | 0x7ffe73458864 |
| 2   | 0x7ffe394fe604 |
| 3   | 0x7ffe8e4ea9f4 |
| 4   | 0x7ffe13590e74 |
| 5   | 0x7ffd70ff3f34 |

## Pointer variables

Pointers are variables that store memory addresses.
To declare a pointer variable, you use the `*` operator, which you write after the type of the variable you want to "point to" (i.e., the type of the variable whose memory address you want to store).

The following code declares a pointer variable and initializes it with the memory address of the variable `x`:

```c
int x = 42;
int *ptr_to_x = &x;
```

### Activity 2 - Using pointers

The program listed in `activity2.c` declares (and initializes) several variables: an integer, a float, and a character.
It then prints the values of these variables.

1. Declare three pointer variables (which gives the program a total of six variables), and use them to store the memory addresses of the other three variables. Name these pointer variables `p_integer`, `p_pi`, and `p_letter`.
2. Print the memory addresses of the six variables, by printing their  values of the pointer variables.
3. Print the values stored in the six variables, by using the correct format specifiers for each variable type.

When done, run the program and note the memory addresses and values of the six variables in the table below:

| Variable  | Memory address |     Value      |
|-----------|----------------|----------------|
| p_integer | 0x7ffc68ddc840 | 42             |
| p_pi      | 0x7ffc68ddc848 | 3.14159274     |
| p_letter  | 0x7ffc68ddc850 | 'A'            |
| integer   | 0x7ffc68ddc838 | 42             |
| pi        | 0x7ffc68ddc83c | 3.14159274     |
| letter    | 0x7ffc68ddc837 | 'A'            |

List the contents of `actvity2.c` in the code block below:

```c
// TODO: paste the contents of activity2.c here
#include <stdio.h>

int main(void) {
    int integer = 42;
    int *p_integer = &integer;

    float pi = 3.14159265359f;
    float *p_pi = &pi;

    char letter = 'A';
    char *p_letter = &letter;

    printf("Value of integer: %d\n", integer);
    printf("The memory address of the integer: %p\n", p_integer);
    printf("The memory address of the p_integer: %p\n", &p_integer);

    printf("Value of pi: %.8f\n", pi);
    printf("The memory address of the pi: %p\n", p_pi);
    printf("The memory address of the p_pi: %p\n", &p_pi);

   printf("Value of letter: %c\n", letter);
   printf("The memory address of the letter: %p\n", p_letter);
   printf("The memory address of the p_letter: %p\n", &p_letter);
    return 0;
}
```

## Dereferencing pointers

To access the value stored at a memory address, you can use the _dereference_ (or _indirection_) operator `*`. This operator is often called the _value-at_ operator.
The dereference operator allows you to modify a variable _indirectly_ - that is, by modifying the memory address stored in a pointer variable.

Dereferencing a pointer is something that is necessary when working with _pointer arguments_ in functions.
When you pass a pointer to a function, you often want to access the value stored at the memory address the pointer points to.

### Activity 3 - Indirect modification

The program listed in `activity3.c` declares two floating point variables, `a` and `b`.
It then calls a `swap_floats` function that takes two pointers to floats as arguments.
The function should swap the values of the two floats, but it does not work as expected.

Fix the program so that the `swap_floats` function works correctly.
You'll need to make correct use of the dereference operator `*` to access the values stored at the memory addresses pointed to by the pointer parameters of the `swap_floats` function.

When done, copy-paste your definition of the `swap_floats` function in the code block below:

```c
// TODO: Paste your definition of the swap_floats function here
#include <stdio.h>

/// @brief Function to swap two floats 
/// @param pa pointer to the first float
/// @param pb pointer to the second float
void swap_floats(float *pa, float *pb) {
    // FIXME: this function is not implemented correctly
    float temp = *pa;
    *pa = *pb;
    *pb = temp;
}

int main(void) {
    float a = 3.14f, b = 2.71f;
    printf("Before swap: a = %.4f, b = %.4f\n", a, b);
    swap_floats(&a, &b);
    printf("After swap: a = %.4f, b = %.4f\n", a, b);
    return 0;
}
```

## Returning pointers

Functions can return pointers to memory locations.
When a function returns a pointer, it is important to make sure that the memory location the pointer points to is still valid after the function returns.
That is, you must never return a pointer to a local variable, because the memory at which the local variable is stored is automatically "deallocated" when the function returns.

### Activity 4 - Returning pointers

Write a function `ptr_to_max` that takes two integer pointers as arguments and returns a pointer to the integer with the highest value (if both have the same value, return a pointer to the first integer).
The prototype of the function, plus a program that tests the function, is already listed in `activity4.c`.

Make sure that your function works correctly by running the program and ensuring that the output is as expected.
When done, copy-paste your definition of the `ptr_to_max` function in the code block below:

```c
// TODO: Paste your definition of the ptr_to_max function here
#include <stdio.h>
#include "functions.h"
/// @brief Returns a pointer to the maximum of two integers
/// @param pa pointer to the first integer
/// @param pb pointer to the second integer
/// @return pointer to the maximum of the two integers
int *ptr_to_max(int *pa, int *pb);
int *ptr_to_max(int *pa, int *pb){
    if(*pa >= *pb){
        return pa;
    }
    else{
        return pb;
    }
}
```

## Pointer arithmetic

Arrays are stored in contiguous memory locations.
That is, all elements are stored one after the other in memory - at consecutive memory addresses.
This means that if you know at which address the first element of an array is stored, you can compute the memory address of any other element in the array.

If you were to assume that a pointer contains the address of the first element of an array, then you can use _pointer arithmetic_ to access the other elements of the array.
Pointer arithmetic is basically adding or subtracting an integer value to a pointer, which results in the pointer pointing to a different memory location:
When performing pointer arithmetic, we basically assume that we're working with an array of a certain type, and the pointer is pointing to the first element of that array.
Incrementing the pointer by one will make it point to the next element in the array - this means that the amount by which the memory address is incremented depends on the size of the type of the array elements.

Because pointers and arrays are closely related in C, the name of an array is actually a pointer to the first element of the array.

### Activity 5 - Pointer arithmetic

The following program (listed in `activity5.c`) prints the memory addresses of the elements of an array of integers:

```c
#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int i;

    for (i = 0; i < 5; i++) {
        printf("Address of arr[%d]: %p\n", i, &arr[i]);
    }

    return 0;
}
```

Modify the program so that it does not use the `&` operator to get the memory address of the array elements, but instead uses pointer arithmetic.
Your program must not contain a single use of the `&` operator.

When done, run the program and ensure that the output is as expected.
If it is, copy-paste your modified program in the code block below:

```c
// TODO: Paste your modified program here
#include <stdio.h>

int main(void) {
    int array[] = {1, 2, 3, 4, 5};
    int i;
    int *p = array;

    for (i = 0; i < 5; i++) {
        // FIXME: the & operator is used to obtain the address
        //        instead, use pointer arithmetic - use of & is not allowed!
        printf("Address of arr[%d]: %p\n", i, (void*)p);
        p++;
    }
    return 0;
}
```

## Strings and pointers

As you've seen earlier, pointers and arrays are intimately related in C.
Since strings are just arrays of characters, pointers and strings are just as closely related.
In fact, string _literals_ in C (anything between double quotes, like `"Hello, world!"`) are stored in memory (as arrays of characters), and thus have a memory address.
We can simply obtain this memory address by assigning the string literal to a pointer variable:

```c
const char *str = "Hello, world!";
```

Here, `const` must be used because string literals are read-only - any attempt to modify the contents of a string literal will result in undefined behavior, and will most likely crash your program.

### Activity 6 - Addresses of string literals

In `activity6.c`, you'll find a program that declares a string literal, as well as an array of characters that is initialized from (the same) string literal:

```c
const char *str = "Hello, world!";
char arr[] = "Hello, world!";
```

Write a function `print_string` that takes a `const char*` pointer as an argument, and prints the memory address of the string that starts at that address, as well as the string (i.e., the sequence of characters that ends with a `'\0'` character) itself.
Use the function to print the memory address and the string for both the `str` and `arr` variables (note that both `str` and `arr` are pointers to the first character of the string).

When done, write the memory addresses of `str` and `arr` into the table below, and copy-paste your definition of the `print_string` function in the code block further below:

| Variable | Memory address |
|----------|----------------|
| str      | 0x55d34da02053 |
| arr      | 0x7fffb09dcc5a |

```c
// TODO: Paste your definition of the print_string function here
#include <stdio.h>

/// @brief Prints a string, as well as its address
/// @param str the string to print
void print_string(const char *str) {
    // FIXME: print the address of the first character in the string
    //        and the characters in the string.
    // Example output: "0x7ffeefbff6e0 Hello, world!"
    
        printf("%p %s\n", (void*)str, str);
    
}

```

## Casting pointers

In C, you can cast types to other types.
This tells the compiler to interpret the value in a specific way different from the way it would normally interpret it.
For example, you can cast a pointer to an integer to a pointer to a character, and then access the individual bytes of the integer:

```c
int x = 42;
char *ptr = (char*) &x;
```

Here, we basically assume that the memory at which the integer `x` is stored is also the memory at which a character is stored.
We could thus treat the memory at which `x` is stored as an array of characters, and access the individual characters that make up the integer `x`.

The contents of memory are often displayed as bytes.
Although C does not have a `byte` type, the `char` type has the same size as a byte (8 bits), but a `char` can hold _negative_ values - it is `signed`.
To work with bytes in C, you can use the `unsigned char` type, which is an 8-bit unsigned integer.

By using pointers to `unsigned char`, you can access the individual bytes of a variable.
For example, you can use a pointer to `unsigned char` to access the individual bytes of an `int` variable:

```c
int answer = 42;
unsigned char* ptr = (unsigned char*)&answer;
// print the four bytes of the answer variable, in hexadecimal format (%02x)
printf("Byte 0: %02x\n", ptr[0]);
printf("Byte 1: %02x\n", ptr[1]);
printf("Byte 2: %02x\n", ptr[2]);
printf("Byte 3: %02x\n", ptr[3]);
```

The code snippet listed above assumes that an `int` variable takes up four bytes in memory.
This is true on most systems, but not all.
Instead, we should use the `sizeof` operator to determine the size (in bytes) of an `int` variable, and a loop to go over the bytes - you'll do that in activity 7.

### Activity 7 - Raw data

Write a function `print_raw_data` that takes a `const unsigned char *` pointer to a memory location and a size (in bytes), and prints the raw data at that location.
That is, the function must print exactly `size` bytes of memory, starting at the memory address pointed to by the pointer.
The function should print the data in hexadecimal format, with spaces between each byte.

A prototype of the function is already listed in `activity7.c`, along with a program that tests the function.

When done, run the program and ensure that the output is as expected.
If it is, copy-paste your definition of the `print_raw_data` function in the code block below:

```c
// TODO: Paste your definition of the print_raw_data function here
#include <stdio.h>

void print_raw_data(const unsigned char *data, size_t size) {
    // FIXME: print each byte in the data the raw data in hexadecimal format
    //        Example output: "0x48 0x65 0x6c 0x6c 0x6f 0x2c 0x20 0x77 0x6f 0x72 0x6c 0x64 0x21"
    // Use the printf function with the %02x format specifier to print each byte
    for (size_t i = 0; i < size; i++) {
        printf("0x%02x ", *data);
        data++;
    }
    printf("\n");  
}   
```

## Obfuscated text

Since characters are stored as numbers (bytes) in memory, you can print arrays of integers as if they are strings.
To do this, you can cast a pointer to an array of integers to a pointer to an array of characters, and then print the characters as a string using the `printf` function and the `%s` format specifier:

```c
int arr[] = {539060552, 2698554};
char *ptr = (char*) arr;
printf("%s\n", ptr);
```

This code snippet prints the text `Hi! :-)`, because the integers `539060552` and `2698554` are stored in memory as the ASCII values of the characters `H`, `i`, `!`, ` `, `:`, and `)`, plus a null terminator (`'\0'`).
Note that this code only works as expected if an `int` is four bytes long, and if the endianness of the system is the same as the endianness of the system that generated the array of integers.

### Activity 8 - Hiding text

In this final activity, you will need to fill an array of integers with the correct numbers so that it prints a hidden message, just like the code example above does.
Ask your lab teacher (or TA) for the text that you need to print in this activity.

To approach this activity, you'll need to reverse the process of the code example above.
That is, you'll need to start with the text, and convert it to an array of integers, so that you know which numbers to put in the array.

When done, write the numbers you found on the paper that you got from your lab teacher, and demonstrate that your program prints the requested message.
```c
#include <stdio.h>
#include <string.h>

int main(void) {
    // FIXME: change the contents of the array `obfuscated_text` in such a way that the program prints
    //        the exact string that was given to you by your lab teacher.

    const char *target_string = "Ignorance is bliss";  // change this to the string you were given (on paper)
    // you may want to write some code here to print the string as an array of integers, rather
    int *ptr = (int*)target_string;
    for(size_t i = 0; i < 5; i++){
        printf("%d ", ptr[i]);
    }
    printf("\n");
    // than guessing the values to put in the array obfuscated_text below

    // change the contents of the array
    const int obfuscated_text[] = {1869506377, 1668178290, 1936269413, 1768710688, 620786547};


    // don't make any changes to the following code
    const char *p = (const char *)&obfuscated_text;
    printf("%s\n", p);
    printf("Given string: %s\n", target_string);

    if (strcmp(p, target_string) == 0) {
        printf("You have successfully completed the task!\n");
    } else {
        printf("The task is not completed yet.\n");
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

# Week 4 - Tutorial: Dynamic memory

Name: SON CAO

Group: ETI1V.IA

Date: 06/12/2024

## Introduction

When working with C, understanding how memory is managed is crucial.
In this tutorial, you will learn how to allocate and deallocate memory dynamically, and how to use the address sanitizer to detect memory problems.

### Code organization

The code for this tutorial is organized as follows: the `CMakeLists.txt` file in the root of the archive is used to build all the programs in the tutorial.
It builds a separate executable for each activity, and the source code for each activity is in a separate `.c` file.

If you did not install `CMake` and a working compiler on Windows, then make sure to open VS Code from the WSL terminal by typing `code .` in the directory that contains the main `CMakeLists.txt` file.
Use the CMake tab (listed on the left, along with other tabs for "Explorer", "Extensions", etc.) in VS Code to configure, build, run and debug the different targets in the project.

## The stack

As you have learned from the lecture and the theory of this week, the stack holds the local variables of each function call, stacked on top of each other.
When a function is called, the memory for its local variables is allocated on the (top of the) stack, and when the function returns, that memory is deallocated again so that it can be used by the next function call.

The size of the stack is limited, and if you use too much memory, you will get a stack overflow.
Also, the size of the stack is set to a default value, but you can change it (at least, in Linux) using the `ulimit` command.
This allows you to experiment with the stack size and see how it affects your program.
The `ulimit` command is used to set user limits, and the `-s` option is used to set the stack size.

**Important note**: The stack size is set in kilobytes by `ulimit`, so 5 kilobytes is 5120 bytes.
Setting the stack size too low will cause many programs (such as `gcc` or even `ls` and `cd`) to crash, so be careful when experimenting with the stack size.

### Activity 1 - Illustrating the stack

In the file `activity1`, you will find a program that stores a birthday calendar in a structure.
Because the calendar structure is quite large, the program requires quite a bit of stack space.

Also, because the program passes a copy of the calendar to the `print_calendar` function, the program uses even more stack space.

> Use the `ulimit` command to lower the stack size to 40 kilobytes by entering `ulimit -s 40` in the (WSL2) terminal.
> 
> Next, run the program - it should crash with a segmentation fault because it runs out of stack space.

> **TODO - Answer the following question: why does the program crash with a segmentation fault?**

```c
- The program crashes with a segmentation fault because it exceeds the stack space allocated for the process.
```

Next, change the program so that the `print_calendar` function takes a (`const`) **pointer** to the calendar structure, instead of a copy of the structure.
Rebuild the program and run it again with the same stack size as before.
Make sure that it now prints the calendar without crashing.
When you're done, copy-paste the modified `print_calendar` function in the code block below:

```c
// TODO: Paste the modified print_calendar function here
void print_calendar(const calendar_t *calendar) {
    for (size_t i = 0; i < calendar->count; i++) {
        printf("%s was born on %02d-%02d-%d\n", calendar->persons[i].name,
               calendar->persons[i].birth_date.day,
               calendar->persons[i].birth_date.month,
               calendar->persons[i].birth_date.year);
    }
}

```

## Activity 2 - Illustrating the stack, part 2

Whenever a function calls another function, the memory for the local variables of the called function is allocated on the stack, "on top" of the local variables of the calling function.
But actually, the stack grows in the opposite direction: it grows _downwards_ in memory, towards lower memory addresses.

The program listed in `activity2.c` runs a recursive function that calls itself a number of times.
In the table listed below, write down the memory range used to store the local variable `values`  of the `recursive_function` function.

| Parameter `n` |   Memory range of `values`       |
|---------------|----------------------------------|
| 0             |  0x7fff4c4a1fa0 - 0x7fff4c4a2fa0 |
| 1             |  0x7fff4c4a0f60 - 0x7fff4c4a1f60 |
| 2             |  0x7fff4c49ff20 - 0x7fff4c4a0f20 |
| 3             |  0x7fff4c49eee0 - 0x7fff4c49fee0 |
| 4             |  0x7fff4c49dea0 - 0x7fff4c49eea0 |
| 5             |  0x7fff4c49ce60 - 0x7fff4c49de60 |
| 6             |  0x7fff4c49be20 - 0x7fff4c49ce20 |
| 7             |  0x7fff4c49ade0 - 0x7fff4c49bde0 |
| 8             |  0x7fff4c499da0 - 0x7fff4c49ada0 |
| 9             |  0x7fff4c498d60 - 0x7fff4c499d60 |

> **TODO - Answer the following question: How many bytes of memory separate two consecutive copies of the `values` arrays on the stack?**

```c
4160 bytes separate two consecutive copies of the values arrays on the stack.
```

## The heap

When storing data on the stack (which is done implicitly when declaring variables), the memory is automatically allocated and deallocated.
This can be limiting, as sometimes you'd like to store data that is not known at compile time, or that needs to be shared between functions.

The heap is a memory area that is managed by the operating system, and that can be used to allocate and deallocate memory dynamically - i.e. while the program is running, on request.
When allocating memory on the heap, you need to keep track of the memory yourself, and you need to deallocate the memory when you're done with it, to prevent memory leaks.
To allocate memory on the heap, you use the `malloc` function and specify the number of bytes you want to allocate.
To deallocate memory, you use the `free` function.

### Activity 3 - Dynamic allocation

The program listed in `activity3.c` has a local variable `array` that is an array of 64 integers.
The program prints the memory range used to store the local variable `array` of the `main` function.

There's another variable in the program - `ptr` - that is a pointer to an array of 64 integers that is allocated on the heap using `malloc`.

Update the program so that it also prints the memory range used to store the memory allocated by `malloc`.
Put the memory range of the two variables in the table below.

| Variable  |            Memory range              |
|-----------|--------------------------------------|
| array     | 0x7fff80020e60 - 0x7fff80020f60      |
| malloc-ed | 0x62ffa1bd52a0 - 0x62ffa1bd53a0      |

## Address sanitizers

An address sanitizer is a tool that can be used to detect memory problems in a program.
It can detect memory leaks, memory access errors, and memory corruption.
To use the address sanitizer, you need to compile and link your program with the `-fsanitize=address` flag, and then run the program.
If the address sanitizer detects any memory problems, it will print an error message to the console that tells you what the problem is and where it occurred.

### Activity 4 - Using an Address Sanitizer

In the `CMakeLists.txt` file, add the `-fsanitize=address` flag to both the `target_compile_options` **and** the `target_link_options`  for the `activity4` program.
Then, reconfigure the project and rebuild the program.
**NOTE**: this will only work on Linux, not on Windows.

Run the `activity4` executable, and check that the output includes a message from the address sanitizer.
Copy the error message that the address sanitizer prints into the code block below:

```verbatim
// TODO: Paste the error message here
How many bytes of memory should be allocated on the heap? 5
Memory allocated on the heap in the range 0x502000000010 - 0x502000000014

=================================================================
==16503==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 5 byte(s) in 1 object(s) allocated from:
    #0 0x7f7761d319c7 in malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:69
    #1 0x5648d863f4e1 in main (/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 2/programming 2/week 4/tutorial/build/activity4+0x24e1) (BuildId: d7903c3cb9b51f85551a35b12b6670edd1c56a6f)
    #2 0x7f7761a4c1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #3 0x7f7761a4c28a in __libc_start_main_impl ../csu/libc-start.c:360
    #4 0x5648d863f3c4 in _start (/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 2/programming 2/week 4/tutorial/build/activity4+0x23c4) (BuildId: d7903c3cb9b51f85551a35b12b6670edd1c56a6f)

SUMMARY: AddressSanitizer: 5 byte(s) leaked in 1 allocation(s).
```

### Activity 5 - Fixing memory problems

The program listed in `activity5.c` has *two* problems related to memory management / memory access.
Use the address sanitizer to find and fix these problems.
The first problem is a "heap-buffer-overflow", which means that the program writes past the end of a memory block that was allocated on the heap.

When you've fixed the problems and the address sanitizer does not report any problems, copy-paste the fixed program in the code block below:

```c
// TODO: Paste the fixed program here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(void) {
    printf("How many integers should be allocated on the heap? ");
    int size = read_int();
    while (size < 0) {
        printf("The size must be non-negative. Try again: ");
        size = read_int();
    }

    int *ptr = (int*) malloc(size * sizeof(int)); // allocate memory to store integers //size * sizeof(int) to ensure enough memory is allocated for size integers.
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Memory allocated successfully\nFilling array with random integers...\n");
    
    for (int i = 0; i < size; i++) {
        ptr[i] = random_int(0, 100);
    }
    free(ptr); // if missing could lead to memory leak
    return 0;
}

```

## Reallocating memory
    
When you allocate memory using `malloc`, you specify the number of bytes you want to allocate.
Oftentimes, you don't know how much memory you need in advance, and you need to allocate more memory later on.
To do this, you can use the `realloc` function (reallocate), which allows you to change the size of the memory block that was allocated using `malloc`.

When you call `realloc`, you specify the pointer to the memory block that you want to reallocate, and the new size of the memory block.
The function will then "ask" the operating system for a new memory block of the specified size.
It is possbible and likely that the current memory block can simply be extended to the new size, but it is also possible that the operating system will allocate a new memory block and copy the data from the old memory block to the new memory block.
The `realloc` function will therefore return a new pointer to the memory block, and you should assign this pointer to the original pointer variable, after ensuring that the reallocation was successful (i.e. the pointer is not `NULL`).

### Activity 6 - Reallocating memory

The program listed in `activity6.c` allocates memory for an array of only 1 integer, and then asks the user to enter many integers, which it stores in the array.
Since the program does not use `realloc` to increase the size of the array, it will crash when the user enters more than one integer.
Fix the program so that it uses `realloc` to increment the size of the array each time the memory is full.

Make sure that the program does not crash when the user enters many characters, and that the address sanitizer does not report any memory leaks.
When you're done, copy-paste the fixed program in the code block below:

```c
// TODO: Paste the fixed program here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(void) {
    int *ptr = (int*) malloc(sizeof(int));  // allocate memory to store one integer

    if(ptr == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }

    int capacity = 1; // current capacity of an array
    int count = 0;  // number of integers stored in memory
    
    printf("Enter an integer (0 to stop): ");
    int input = read_int();
    
    while (input != 0) {
        if  (count == capacity){
            capacity *= 2; //double the capacity of interger
            int *update = (int*) realloc(ptr, capacity * sizeof(int));
            if(update == NULL){
                printf("Reallocation failed");
                free(ptr); //free the og memory
                return 1;
            }
            ptr = update; // update the pointer 
        }
        ptr[count] = input;     // store the integer
        count++;                // increment the number of integers stored

        printf("Enter an integer (0 to stop): ");
        input = read_int();
    }

    printf("You've entered %d integers:\n", count);
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            printf(", ");  // print a comma and a space before all but the first integer
        }
        printf("%d", ptr[i]);  // print the integers
    }
    printf("\n");
    free(ptr);
    return 0;
}

```

## Strings revisited

As you should know well enough by now, in C strings are represented as arrays of characters, terminated by a null character (`'\0'`).
Also, arrays and pointers are very closely related in C - you can use the name of an array as a pointer, and you can treat pointers as arrays.

There is one major difference between arrays and pointers, and that is that when declaring an array variable, memory is actually allocated for it (on the stack).
When declaring a pointer variable, only memory for the pointer itself is allocated (on the stack), not for the data it points to.

This means that if you're going to let a pointer point to a string, you either need to let it point to a string that is stored in an array, or you need to allocate memory for the string dynamically.

### Activity 7 - Storing strings on the heap

The program listed in `activity7.c` reads a string into an array of characters that is allocated on the stack.
Change the program so that it does not use any arrays allocated on the stack, but instead uses `malloc` to allocate memory for the string on the heap and store it there.
The program must also free the memory allocated for the string before it exits.

Test that the program works correctly by running it and checking that it does not crash and that it prints the string correctly.
The program is set up to use the address sanitizer, so also make sure that it does not report any memory problems.

When you're done, copy-paste the modified program in the code block below:

```c
// TODO: Paste your modified program here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(void) {
    // FIXME: change this program so that it does not use *ANY* arrays, only pointers
    int capacity = 100;
    char *name = (char*) malloc(capacity * sizeof(char));
    if(name == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Hi, what's your name? ");

    read_string(name, capacity);

    printf("Hello, %s!\n", name);
    
    free(name);
    return 0;
}

```

## Arrays of strings and double pointers

A string is basically a pointer to an array of characters, terminated by a null character.
This means that an array of strings is a double pointer: it points to (the first element of) an array of pointers, each of which points to (the first element of) an array of characters.

Storing multiple strings in a dynamically allocated array of strings is a bit more complex than storing a single string.
This is because you need to allocate memory for each string separately, and you need to allocate memory for the array of pointers as well.
Likewise, when freeing the memory, you need to free the memory for each string separately, and you need to free the memory for the array of pointers as well.

### Activity 8 - Storing arrays of strings

The program listed in `activity8.c` reads _three_ strings into an array of strings that is allocated on the stack.
Change the program so that it allocates *all* memory _dynamically_ (i.e. using `malloc`), and frees all memory before it exits.
The program must have *only one* pointer variable that points to the array of strings.

Test that the program works correctly by running it and checking that it does not crash and that it prints the strings correctly.
Also make sure that the address sanitizer does not report any memory leaks.

When you're done, copy-paste the modified program in the code block below:

```c
// TODO: Paste your modified program here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

#define NUM_STRINGS 3
#define STRING_CAPACITY 200

int main(void) {
    // FIXME: change this program so that it does not use *ANY* arrays, only pointers
    //single pointer variable that points to array of strings
    char **strings = malloc(NUM_STRINGS * sizeof(char *));
    if (strings == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    //allocate memory for each string
    for (int i = 0; i < NUM_STRINGS; i++) {
        strings[i] = malloc(STRING_CAPACITY * sizeof(char));
        if (strings[i] == NULL) {
            printf("Memory allocation failed\n");
            // free already allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }
    }

    // Read strings
    printf("Hi, what's your name? ");
    read_string(strings[0], STRING_CAPACITY);

    printf("Where are you from? ");
    read_string(strings[1], STRING_CAPACITY);

    printf("What's your favorite color? ");
    read_string(strings[2], STRING_CAPACITY);

    printf("Hello, %s from %s! Your favorite color is %s.\n", strings[0], strings[1], strings[2]);
    
    // Free memory
    for (int i = 0; i < NUM_STRINGS; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}

```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will get in touch with you.

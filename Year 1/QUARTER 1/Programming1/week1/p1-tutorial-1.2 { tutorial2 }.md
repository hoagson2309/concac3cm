# Week 1 - Tutorial 2: Compiling and linking multiple files

> Name: HOANG SON CAO
>
> Group: ETI1V.IA
>
> Date: 04/09/2024

## Introduction

In this tutorial, you will learn how to compile and link multiple source files into a single executable program.
You will create a simple program that uses functions from a separate source file, and compile and link the source files together to create an executable program.

To preview this markdown file, use the command palette in Visual Studio Code (CTRL+SHIFT+P) and select `Markdown: Open Preview` to view it in your browser, or use the keyboard shortcut (usually `CTRL+K V`).
You can also switch between the editor and the preview by clicking the icon in the top right corner of the editor window.

You can also switch between preview and editing mode by using the `CTRL+SHIFT+V` keyboard shortcut.

## Create a new project in Visual Studio Code

In this first step, you'll create a project with multiple files in Visual Studio Code.
A project is a collection of files that are related to each other, and that are compiled and linked together to create an executable program.
For now, a project is just a directory / folder on your computer that contains the files for your program.

Two of these files are already provided for you (they can be downloaded from Brightspace): `functions.h`, and `functions.c`.
These two files contain various functions that you will be using throughout this module.
The header file `functions.h` contains the function prototypes, and the source file `functions.c` contains the function definitions.

1. Download the two provided files from Brightspace: `functions.h`, and `functions.c`.
2. Create a new project in Visual Studio Code, and add the two provided files to the project. You can do this by right-clicking on the Explorer pane in Visual Studio Code, and selecting "Add Folder to Workspace". Then, select the folder where you saved the two provided files.
3. Create a new file in the project, called `main.c`. This file will contain the `main` function, which is the entry point of your program.

We'll create a simple program that uses the functions from the `functions.c` file to read two integers from the user, and print the sum of these two integers.
Give this file the following contents:

```c
int main(void)
{
    printf("Enter the first number: ");
    int a = read_int();
    printf("Enter the second number: ");
    int b = read_int();
    int sum = a + b;
    printf("The sum of %d and %d is %d\n", a, b, sum);
    return 0;
}
```

## Compiling the program

The program contained in `main.c` has some problems, since it uses two functions that are not defined in the `main.c` file: `read_int` and `printf`.
The compiler will not be able to compile this program, since it does not know how to find the definitions of these functions.

Try to *compile* the program (that's what the `-c` option passed to `gcc` specifies) by running the following command in the terminal:

```bash
gcc -c main.c
```

### Activity 1

Answer the following question: what are the warnings and / or error messages that you get when you try to compile the program using the command given above, and what do they mean?

> Answer: **TODO**: week1tutorial2.c: In function ‘main’:
week1tutorial2.c:3:5: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
    3 |     printf("Enter the first number: ");
      |     ^~~~~~
week1tutorial2.c:1:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
  +++ |+#include <stdio.h>
    1 | int main(void)
week1tutorial2.c:3:5: warning: incompatible implicit declaration of built-in function ‘printf’ [-Wbuiltin-declaration-mismatch]      
    3 |     printf("Enter the first number: ");
      |     ^~~~~~
week1tutorial2.c:3:5: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
week1tutorial2.c:4:13: warning: implicit declaration of function ‘read_int’ [-Wimplicit-function-declaration]
    4 |     int a = read_int();
      |             ^~~~~~~~
    //There is a missing #include <stdio.h> so the command "printf" cannot work.
    //There is a missing #include "functions.h" so the command "int a = read_int();" cannot work.

## Including the header files

Add two `#include` directives to the `main.c` file, to include the `functions.h` header file, and the standard input/output header file (`stdio.h`).
Make sure to use double quotes (`"`) to include the `functions.h` file, since it is located in the same directory as the `main.c` file.
For `stdio.h`, use angle brackets (`<` and `>`) to include the file, since it is a standard library file.

### Activity 2

List the contents of the file `main.c` after you've included the two `#include` directives.

> Answer: **TODO**: Provide your answer (the contents of main.c) here:
>
> ```c
> // TODO: It is about suming up both of the numbers
> ```
>

### Activity 3

Again, try to compile the program by running the following command in the terminal:

```bash
gcc -c main.c
```

Verify that the program has been compiled successfully by checking if a file named `main.o` has been created in the project directory.

## Compiling and linking multiple files

Now that the `main.c` file has been successfully compiled, we can compile the `functions.c` file as well.

### Activity 4

Compile the `functions.c` file by running the following command in the terminal:

```bash
gcc -c functions.c
```

Verify that the file `functions.o` has been created in the project directory.

### Activity 5

Now that both the `main.c` and `functions.c` files have been compiled, we can link these two object files into a single executable program.

Link the two object files by running the following command in the terminal:

```bash
gcc -o program main.o functions.o
```

Verify that a file named `program` has been created in the project directory, and run the program by executing the following command in the terminal:

```bash
./program
```

## Combining compilation and linking

Instead of first compiling the `main.c` and `functions.c` files separately, and then linking them together, you can also compile and link the files in a single step.

### Activity 6

Remove the `main.o` and `functions.o` files from the project directory by running the following commands in the terminal (use the "Tab" key to autocomplete the filenames!):

```bash
rm main.o
rm functions.o
```

Compile and link the `main.c` and `functions.c` files in a single step by running the following command in the terminal:

```bash
gcc -o program main.c functions.c
```

Again, verify that a file named `program` has been created in the project directory, and run the program to verify that it works correctly.

## Recognizing linking errors

In case your program uses functions that are not defined in any of the source files, the linker will generate an error when you try to link the object files together.
The error message will read like "undefined reference to `function_name`", where `function_name` is the name of the function that the linker cannot find.

It's good to recognize these errors, so here's a final activity to provoke such an error.

### Activity 7

Try to build your program from the `main.c` file alone, without including the `functions.c` file, by running the following command in the terminal:

```bash
gcc -o program main.c
```

Copy-paste the error message that you get when you try to compile the program, and explain what it means.

> Answer: **TODO**: /usr/bin/ld: /tmp/ccbB5SiD.o: in function `main':
week1tutorial2.c:(.text+0x21): undefined reference to `read_int'
/usr/bin/ld: week1tutorial2.c:(.text+0x3d): undefined reference to `read_int'
collect2: error: ld returned 1 exit status - there's a missing functions.c so `read_int' doesn't work.

## Sign off

To sign off this tutorial, you will need to demonstrate the following things:

* You can compile a source file to an object file, on the command-line
* You can link multiple object files into a program, on the command-line
* You can run the program from the command line
* You have answered all questions in this file, and have submitted it at the correct submit point in Brightspace

You'll need to sign off this tutorial before you can continue with the next tutorial.
Once you've successfully demonstrated the items listed above, your lab teacher will mark the assignment as completed, and you can continue with the next tutorial.

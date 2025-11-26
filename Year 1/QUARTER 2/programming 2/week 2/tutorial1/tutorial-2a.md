# Week 2 - Tutorial 1: Make

Name: SON CAO

Group: ETI1V.IA

Date: 20/11/2024

## Introduction

As your programs grow in size and complexity, it becomes increasingly difficult to manage the build process manually. In this tutorial, you will learn how to use Make and CMake to automate the build process for your programs.
Make is a build automation tool that uses a Makefile to specify how to build a program. CMake is a more modern build automation tool that generates Makefiles or project files for other build tools. Both tools are widely used in industry and are essential for managing large software projects.

### Activity 1 - Using a Makefile

The folder `activity1` contains a simple C program that prints "Hello, World!" to the console.
A `Makefile` that compiles the program and produces an executable called `hello` is provided.
The Makefile consists of multiple targets. Each target specifies how to produce a file from other files.
When running `make`, the first target in the Makefile is executed.
In this case, this means that the executable `hello` is built, which cascades into building the other files as needed.

Change the program (i.e. `main.c`) so that it asks the user for their name (using the `read_string` function from `functions.h`) and prints "Hello, <name>!" to the console (with `<name>` replaced by the name entered by the user).

Update the `Makefile` so that it correctly builds the modified program.
This means you'll need to include the `functions.c` file into the build process.
You must apply the same steps (compilation, assembly, and linking) to the `functions.c` file as you did with the `main.c` file.

Test whether the `Makefile` works correctly by running `make` from the terminal.
If it correctly creates the `hello`  program, include the modified Makefile in the code block below:

```make
# TODO: Paste the Makefile you used here

# the program to be built (hello) is composed of main.o and functions.o
hello: main.o functions.o
	@echo "Linking main.o functions.o into hello"
	gcc -o hello main.o functions.o

# main.o is built from main.s
main.o: main.s
	@echo "Assembling main.o from main.s"
	gcc -c main.s
# functions.o is built from functions.s
functions.o: functions.s
	@echo "Assembling functions.o from functions.s"
	gcc -c functions.s
# main.c is complied into main.s
main.s: main.c
	@echo "Compiling main.c into main.s"
	gcc -S main.c
# functions.c is complied into functions.s
functions.s: functions.c
	@echo "Compiling functions.c into functions.s"
	gcc -S functions.c

```

### Activity 2 - Writing a makefile from scratch

The folder `calculator` contains a simple calculator program that can perform basic arithmetic operations.
Write a Makefile from scratch that compiles the program and produces an executable called `calculator`.
Use the Makefile from the previous activity as a reference.

When you're done, include the Makefile in the code block below:

```make
# TODO: Paste the Makefile you used here
# TODO: enter contents here so that calculator is built from main.c and functions.c
#       using a separate compilation step from source to object files

# the program to be built (calculator) is composed of main.o and functions.o
calculator: main.o functions.o 
	@echo "linking main.o functions.o into calculator"
	gcc -o calculator main.o functions.o 

# main.o is built from main.s
main.o: main.s 
	@echo "Assembling main.o from main.s"
	gcc -c main.s

# functions.o is built from functions.s
functions.o: functions.s 
	@echo "Assembling functions.o from functions.s"
	gcc -c functions.s

# main.c is compiled into main.s
main.s: main.c
	@echo "Compiling main.c into main.s"
	gcc -S main.c 
functions.s: functions.c
# functions.c is compile into functions.s
	@echo "compiling functions.c into functions.s"
	gcc -S functions.c
```
## Variables in Makefiles

Makefiles can contain variables that can be used to store values that are used multiple times in the Makefile.
Variables can be defined at the beginning of the Makefile and referenced later in the file.
This makes it easier to change values in the Makefile without having to search for them throughout the file.

There are a few predefined variables in Makefiles that are commonly used:

- `CC`: The C compiler to use.
- `CFLAGS`: Flags to pass to the C compiler, for example to enable warnings or optimizations.
- `CPPFLAGS`: Flags to pass to the C preprocessor, for example to define macros.
- `LDFLAGS`: Flags to pass to the linker, for example to link against certain libraries.

You can redefine these variables or define new variables as needed in the Makefile.
This is done by using the assignment operator (`=`) to assign a value to a variable.

To reference a variable, you use the syntax `$(VAR)`, where `VAR` is the name of the variable.

### Activity 3 - Using variables

Modify the Makefile from the previous activity to use **variables** for the compiler and compiler flags, so that you can easily change them in one place.
Refer to the slides or the theory document for information on how to define and use variables in a Makefile.
Make sure to use the correct variables for the compiler, compiler flags.
These are `CC` for the C compiler, `CFLAGS` for the compiler flags, and `CPPFLAGS` for the preprocessor flags.

When you're done, include the modified Makefile in the code block below:

```make
# TODO: Paste the Makefile you used here
# TODO: enter contents here so that calculator is built from main.c and functions.c
#       using a separate compilation step from source to object files

CC = gcc;
CFLAGS = -Wall;
CPPFLAGS = -I; 

# the program to be built (calculator) is composed of main.o and functions.o
calculator: main.o functions.o 
	@echo "linking main.o functions.o into calculator"
	$(CC) -o calculator main.o functions.o 

# main.o is built from main.s
main.o: main.s 
	@echo "Assembling main.o from main.s"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.s

# functions.o is built from functions.s
functions.o: functions.s 
	@echo "Assembling functions.o from functions.s"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c functions.s

# main.c is compiled into main.s
main.s: main.c
	@echo "Compiling main.c into main.s"
	$(CC) $(CFLAGS) $(CPPFLAGS) -S main.c 
functions.s: functions.c
# functions.c is compile into functions.s
	@echo "compiling functions.c into functions.s"
	$(CC) $(CFLAGS) $(CPPFLAGS) -S functions.c 
```

## Wildcards and substitution

To make your Makefiles more flexible and easier to maintain, you can use **wildcards** and **substitution** in the rules.
Wildcards allow you to match multiple files with a single pattern, while substitution allows you to modify strings in variables.

There are two kinds of wildcards you can use in a Makefile:

- The `*` wildcard matches any number of characters.
- The `%` wildcard matches any single string.

The first wildcard is typically used to match files in a directory, while the second wildcard is used to match parts of filenames in rules.

To let Make automatically find all source files in a directory, you can use the `wildcard` function - note that this is a function, not a wildcard character - in combination with the `*` wildcard character.
For example, `$(wildcard *.c)` will match all `.c` files in the current directory.

The `%` wildcard is used in rules to match parts of filenames.
Remember that the first line of each rule consists of a target (the file to be built), a colon ('`:`'), followed by a list of dependencies.
When using the `%` wildcard in the target, it will match any string and store it in a variable.
This variable can then be used in the dependencies, for example to specify the source file that corresponds to the object file.
For example, the rule `%.o: %.c` will match any `.o` file to its corresponding `.c` file - it thus states that any `.o` file depends on the corresponding `.c` file.

Another powerful feature of Makefiles is **substitution**.
This allows you to modify strings in variables by replacing parts of the string with other parts.
Substitution is done using the `$(VAR:pattern=replacement)` syntax, where `VAR` is the variable to modify, `pattern` is the part of the string to replace, and `replacement` is the string to replace it with.
For example, `$(SRC:.c=.o)` will replace the `.c` extension in all filenames in the `SRC` variable with `.o`.

### Activity 4 - Working with wildcards

The folder `reverser` contains a simple program that reads a string from the console and prints all words in the string in reverse.
The folder has a `Makefile` that does not really do much, except listing all source files that are in the folder.
The makefile makes use of the `wildcard` function to do this.

Modify the Makefile so that it uses **wildcards** (the `%` symbol) to automatically compile all `.c` files in the folder to `.o` files.
Write a Makefile that uses variables and wildcards (use the `%` symbol in the rules) to:

- Compile all `.c` files in the folder to `.o` files.
- Link all `.o` files into an executable called `program`.

The Makefile should consist of only **two** targets - one for compiling _all_ `.c` files to `.o` files, and one for linking all `.o` files into an executable.

Make sure that the Makefile works correctly by running `make` from the terminal.
Verify that indeed all `.c` files are compiled to `.o` files and that these are linked into an executable called `program`.
When you're done, include the modified Makefile in the code block below:

```make
# TODO: Paste the Makefile you used here
CC = gcc
CFLAGS = -Wall
CPPFLAGS = -DDEBUG 

# Get all .c files in the current directory
SOURCES = $(wildcard *.c)

# TODO: assign all .o files that need to be created to OBJECTS
#       by replacing .c with .o in SOURCES
OBJECTS = $(SOURCES:.c=.o) 

# This rule now simply prints the list of source files
# TODO: the rule should depend on the object files, not on the source files
# Rule to link .o files into an executable (reverser)
reverser: $(OBJECTS)
	@echo $^
	$(CC) $(OBJECTS) -o reverser

# Rule to compile .c files to .o files
%.o: %.c
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c $(CPPFLAGS) $< -o $@

```

## Working with build directories

When working on a project, it is common to separate the source files from the build files. This separation keeps the source directory clean and allows you to build the project in a separate directory.

The directory structure of a simple project might look like this:

```plaintext
project/
├── main.c
├── functions.c
|── functions.h
└── build/
```

Or, for more complex projects, source files can be put into a `src` directory, which is at the same level as the `build` directory:

```plaintext
project/
├── src/
│   ├── main.c
│   ├── functions.c
│   └── functions.h
└── build/
```

Directories can be created in a Makefile using the `mkdir` command, which is the Linux command to create directories.
To make sure that the command does not fail if the directory already exists, you can use the `-p` flag.

When working with build directories, it may be useful to list the directory in a variable, so you can easily refer to it in the Makefile.
It is also common to generate the targets (i.e. the object files) from the source files, so you do not have to list them manually.
This can be done using _wildcard substitution_.

For example, if you have a list of source files in a variable `SRC`, you can generate a list of object files in a variable `OBJ` by replacing the `.c` extension with `.o`, or simply appending `.o` to the filenames.
If your files are in the `src` directory, for example, you could put the following lines in your Makefile:

```make
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
```

### Activity 5 - Separating build files

Modify the Makefile from the previous activity so that it writes all build files, including the executable, to a `build` directory.

Create a Makefile that:

- Builds the `build` directory if it does not already exists (use the command `mkdir -p` for this).
- Compiles the source files in the `src` directory to object files in the `build` directory.
- Links the object files into an executable called `program`, which is written to the `build` directory.

Make sure that the Makefile works correctly by running `make` from the terminal.
Verify that the `program` executable is created in the `build` directory.
When you're done, include the modified Makefile in the code block below:

```make
# TODO: Paste the Makefile you used here
CC = gcc
CFLAGS = -Wall
CPPFLAGS = -DDEBUG 

# Get all .c files in the current directory
SOURCES = $(wildcard src/*.c)

# TODO: assign all .o files that need to be created to OBJECTS
#       by replacing .c with .o in SOURCES
OBJECTS = $(SOURCES:src/%.c=build/%.o) 

# This rule now simply prints the list of source files
# TODO: the rule should depend on the object files, not on the source files
# Rule to link .o files into an executable (reverser)
reverser: $(OBJECTS)
	@echo "Linking $(OBJECTS) into $@"
	$(CC) $(CFLAGS) -o build/reverser  $(OBJECTS)

# Rule to compile .c files to .o files
build/%.o: src/%.c
	@mkdir -p build
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
```

## Passing arguments to the preprocessor

The C preprocessor is a tool that runs before the actual compilation process.
It processes the source code and performs tasks such as including header files, defining macros, and removing comments.
The preprocessor is controlled by directives that start with a `#` character, such as `#include`, `#define`, and `#ifdef`.

The preprocessor can also be used to define macros that can be passed to the compiler.
A macro is a symbolic name that represents a value or a piece of code.
When the preprocessor encounters a macro in the source code, it replaces the macro with its value or code before the actual compilation process begins.
To pass a macro to the compiler, you can use the `-D` flag followed by the macro name and its value (if you omit the value, the macro is defined as 1).

### Activity 6 - Passing macros to the compiler

The folder `activity6` contains a simple C program that uses a macro to define the size of an array.
It relies on the `NUM_NUMBERS` macro being defined when the program is compiled.
The file `main.c`, however, does not define the `NUM_NUMBERS` macro itself.
It is up to the Makefile to define the macro and pass it to the compiler.

Update the Makefile that's in the folder so that it defines the `NUM_NUMBERS` macro with a value of `10` and passes it to the compiler when compiling the program.
This flag should be passed to the compiler using the `CPPFLAGS` variable.

When you're done, include the modified Makefile in the code block below:

```make
# TODO: Paste the Makefile you used here
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Werror
CPPFLAGS = -DNUM_NUMBERS=10

numbers: main.o functions.o
	@echo "Linking main.o and functions.o into numbers"
	$(CC) -o numbers main.o functions.o

# implicit rules (these use CC, CFLAGS, and CPPFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c

functions.o: functions.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c functions.c

```

## The NCurses library

The `ncurses` library is a library for creating text-based user interfaces in a terminal.
It provides functions for drawing text, windows, and other elements on the screen.
The library is commonly used in terminal-based games and applications on Unix-like systems.

Before you can use this library, you need to install it on your system.
In a WSL terminal, type `sudo apt install libncurses-dev` to install the library.

To use a library in your program, you need to have two things: the library itself and the header files that declare the functions provided by the library.
Installing the library will make the header files available on your system - for example, you can include the `ncurses.h` header file using `#include <ncurses.h>`.
The library itself is a file that contains the compiled functions that your program can use.
It is usually named `lib<name>.a` or `lib<name>.so`, where `<name>` is the name of the library, and it can typically be found somewhere in `/usr/lib`.

To make the library functions available to your program, you need to link your program against the library.
This is done through the `-l` flag, followed by the name of the library (without the `lib` prefix and the file extension).
So, to link against the `ncurses` library, you would use the `-lncurses` flag.
These flags must be specified in the _linker_ options that are passed to the compiler when linking the program.
Linker flags (if present) should be placed in the `LDFLAGS` variable in the Makefile.

### Activity 7 - Using libraries

The folder `minesweeper` contains a simple minesweeper game that uses the `ncurses` library to draw the game board.
The game is made up of multiple source files, including `main.c` and `game.c`.

Write a makefile that compiles the program and produces an executable called `minesweeper`.
The Makefile must:

- Create a `build` directory if it does not already exist.
- Compile all `.c` files in the folder to `.c.o` files in the `build` directory.
- Link all object files into an executable called `minesweeper`, which is written to the `build` directory.
- Link against the `ncurses` library.

Test your Makefile by running `make` from the terminal.
If it correctly creates the `minesweeper` program, include the Makefile in the code block below:

```make
# TODO: Paste the Makefile you used here
CC = gcc
CFLAGS = -Wall
CPPFLAGS = 
LDFLAGS = -lncurses

BUILDDIR = build

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=build/%.o)

minesweeper: $(OBJECTS)
	@echo "Linking $(OBJECTS) into $@"
	$(CC) $(CFLAGS) -o build/minesweeper $(OBJECTS) $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c $< -o $@
```

### Activity 8 - Cleaning up

Add a `clean` target to the Makefile of the previous activity. It should remove all object files and the executable produced by the build process from the `build` directory.
The rule must not remove the build directory itself, only its contents.

When you're done, include the modified Makefile in the code block below:

```make
# TODO: Paste the Makefile you used here
CC = gcc
CFLAGS = -Wall
CPPFLAGS = 
LDFLAGS = -lncurses

BUILDDIR = build

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=build/%.o)

minesweeper: $(OBJECTS)
	@echo "Linking $(OBJECTS) into $@"
	$(CC) $(CFLAGS) -o build/minesweeper $(OBJECTS) $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up build directory"
	@rm -f build/minesweeper

```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will mark it with 0 points in Brightspace.
If you receive 0 points, make sure to check the feedback, make the necessary changes, and resubmit the tutorial.
Do this before the end of week 2.9, as this is the deadline for having submitted all tutorials and assignments.


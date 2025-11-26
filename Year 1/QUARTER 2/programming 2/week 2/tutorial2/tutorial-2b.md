# Week 2 - Tutorial 2: CMake and Debugging

Name: SON CAO

Group: ETI1V.IA

Date: 23/11/2024

## Introduction

As your programs grow in size and complexity, it ebecomes increasingly difficult to manage the build process manually. In this tutorial, you will learn how to use Make and CMake to automate the build process for your programs.
Make is a build automation tool that uses a Makefile to specify how to build a program. CMake is a more modern build automation tool that generates Makefiles or project files for other build tools. Both tools are widely used in industry and are essential for managing large software projects.

### Activity 1 - Installing CMake

In a WSL terminal, type `cmake --version` to check if CMake is installed. If it is not installed, you can install it using the following command:

```bash
sudo apt install cmake
```

Check to see if CMake is installed by running `cmake --version` again. Make sure you have at least version 3.20 installed.

## The CMakeLists.txt file

A `CMakeLists.txt` file describes how to build a project using CMake. It contains a series of commands to specify the source files, libraries, and build targets for the project.
At a minimum, a `CMakeLists.txt` file should contain the following:

```cmake
cmake_minimum_required(VERSION 3.20)

project(Tutorial)
```

Here, `cmake_minimum_required` specifies the minimum version (in this case 3.20) of CMake required to build the project, and `project` specifies the name of the project.
The project is named "Tutorial" in this example.

If you have the C/C++ extension pack installed in Visual Studio Code, you can create a new CMake project by opening the command palette (Ctrl+Shift+P or F1) and running the `CMake: Quick Start` command.
This will ask you a series of questions to generate a `CMakeLists.txt` file and create a build directory for your project.

### Activity 2 - Creating a CMakeLists.txt file

The folder `acitivity2` contains a simple C program.
The folder does not contain a `CMakeLists.txt` file yet - you will need to create one.

Open the folder in VS Code and create a new file named `CMakeLists.txt` in the folder.
The file must contain one line that uses the `add_executable` command to specify which executable must be built in the project, and what source files the executable is built from.

When you have created the `CMakeLists.txt` file, build the project using the CMake extension in VS Code.
You can use the keyboard shortcut `Ctrl+Shift+P` to open the command palette, and then run the `CMake: Build` command, or use the `F7` key (this is the default keybinding for building the project).
You can then run the program by pressing `F5` or using the `Run` button in the top right corner of the window.

Verify that the program is built and run successfully.
When you're done, paste the contents of the `CMakeLists.txt` file into the markdown file.

```cmake
# TODO: insert the contents of your CMakeLists.txt file here
cmake_minimum_required(VERSION 3.20)

project(numberfun)

add_executable(numberfun numberfun.c main.c functions.c)
target_compile_options(numberfun PRIVATE -Wall) 
```

## Generating multiple executables with CMake

You can generate multiple executables in a single CMake project by using the `add_executable` command multiple times.
For example, the following `CMakeLists.txt` file generates two executables, `tutorial1` and `tutorial2`, from the source files `tutorial1.c` and `tutorial2.c`, which both rely on the functions defined in `functions.c`.:

```cmake
cmake_minimum_required(VERSION 3.20)

project(Tutorial)

add_executable(Tutorial1 tutorial1.c functions.c)
add_executable(Tutorial2 tutorial2.c functions.c)
```

When you build the project, CMake will generate two executables, `tutorial1` and `tutorial2`.
These executables will be placed in a separate subdirectory within the build directory.

### Activity 3 - Generating multiple executables with CMake

The folder `activity3` contains two programs: `primes.c` and `fibonacci.c`.
Create a `CMakeLists.txt` file that generates two executables, `primes` and `fibonacci`, from the source files in the folder.

When you have created the `CMakeLists.txt` file, build the project using the CMake extension in VS Code.

Next, run **both** programs and verify that they work correctly.
When you're done, paste the contents of the `CMakeLists.txt` file into the markdown file.

```cmake
# TODO insert the contents of your CMakeLists.txt file here
cmake_minimum_required(VERSION 3.20)

project(Activity3)

add_executable(fibonacci fibonacci.c functions.c)
add_executable(primes primes.c functions.c)
```

## Splitting the CMakeLists.txt file into multiple files

When working with projects that contain multiple "parts" (e.g. multiple executables or libraries), it can be helpful to split the `CMakeLists.txt` file into multiple files, and distribute these files across the project directory structure.

For example, for the previous activity you could setup the following directory structure:

```plaintext
activity3/
    CMakeLists.txt
    primes/
        CMakeLists.txt
        primes.c
    fibonacci/
        CMakeLists.txt
        fibonacci.c
    functions/
        functions.c
        functions.h
```

The "main" `CMakeLists.txt` file is the one in the root of the project directory, and it should **include** the `CMakeLists.txt` files in the `primes` and `fibonacci` directories using `add_subdirectory`.
The two `CMakeLists.txt` files in the `primes` and `fibonacci` directories can be kept very simple.
The former could for example contain the following:

```cmake
add_executable(primes primes.c ../functions/functions.c)
target_include_directories(primes PRIVATE ../functions)
```

Here, the `target_include_directories` command is used to specify that the `primes` executable should include the `functions` directory when looking for header files.
If we would not do this, the `#include "functions.h"` statement in `primes.c` would not work because the compiler would not know where to find the `functions.h` file.

The main `CMakeLists.txt` file simply includes the `CMakeLists.txt` files in the `primes` and `fibonacci` directories:

```cmake
cmake_minimum_required(VERSION 3.20)
project(Tutorial)

add_subdirectory(primes)
add_subdirectory(fibonacci)
```

### Activity 4 - Splitting the CMakeLists.txt file into multiple files

The folder `acitivity4` contains the same programs as the previous activity, but now they are split into separate directories: `primes`,  `fibonacci`, and `functions`.
Create three `CMakeLists.txt` files: one in the root of the project directory, and one in each of the `primes` and `fibonacci` directories.
The `CMakeLists.txt` file in the root of the project should include the `CMakeLists.txt` files in the `primes` and `fibonacci` directories using `add_subdirectory`.
The ones in the `primes` and `fibonacci` directories should contain the `add_executable` command to build the executables, and use `target_include_directories` to make sure that the `functions` directory is included when looking for header files.

You are not allowed to copy the `functions.c` and `functions.h` files to the `primes` and `fibonacci` directories.

When you have created the `CMakeLists.txt` files, build the project using the CMake extension in VS Code.
Make sure that you can run both programs and that they work correctly.
When you're done, paste the contents of the `CMakeLists.txt` files into the markdown file.

```cmake
# TODO: insert the contents of the CMakeLists.txt file in the root of the project here
cmake_minimum_required(VERSION 3.20)

project(Activity4)

add_subdirectory(fibonacci)
add_subdirectory(primes)


```

```cmake
# TODO: insert the contents of the CMakeLists.txt file in the primes directory here
add_executable(primes primes.c ../functions/functions.c)

target_include_directories(primes PRIVATE ../functions)
```

```cmake
# TODO: insert the contents of the CMakeLists.txt file in the fibonacci directory here
add_executable(fibonacci fibonacci.c ../functions/functions.c)

target_include_directories(fibonacci PRIVATE ../functions)
```

## Creating libraries with CMake

You've exclusively built executables (i.e. programs that can be run) so far, but it's also possible to build libraries.
A library is a collection of functions and data that can be used by other programs.
It does not have a `main` function, as it is not a standalone program.

To create a library with CMake, you use the `add_library` command instead of the `add_executable` command.
The `add_library` command specifies the source files that make up the library, similar to how `add_executable` specifies the source files that make up an executable.

Typically, when creating a library, you also develop a program that uses the library.
This could be a simple program that tests the functions in the library, or a more complex program that uses the library to perform some task.
Suppose for example that you're creating a library that contains a function to calculate the square root of a number (of course, this is just the start of this library, and it will contain more functions later).
Your project directory structure could then look like this:

```plaintext
activity5/
    CMakeLists.txt
    lib/
        CMakeLists.txt
        mysqrt.c
        mysqrt.h
    main/
        CMakeLists.txt
        main.c
```

Here, the `lib` directory contains the source files for the library, and the `main` directory contains the source files for the program that uses the library.
The `CMakeLists.txt` file in the `lib` directory should have an `add_library` line that specifies the source files for the library:

```cmake
add_library(mathlib mysqrt.c)
```

Likewise, the `CMakeLists.txt` file in the `main` directory should have an `add_executable` line that specifies the source files for the program.
However, the only source file in this case is `main.c` - the `mysqrt.c` file is not part of the program, but part of the library.
To make its functions available to the program, the program must be *linked* to the library.
To do this, you use the `target_link_libraries` command:

```cmake
target_link_libraries(main mathlib)
```

Again, the `CMakeLists.txt` file in the root of the project should include the `CMakeLists.txt` files in the `lib` and `main` directories using `add_subdirectory`.

One thing that is missing in the story so far is the fact that the executable built from `main.c` will not know where to find the header file `mysqrt.h`.
To fix this, you can include the `target_include_directories` command in the `CMakeLists.txt` file in the `lib` directory, and using the `PUBLIC` keyword to make sure that the header files in the `lib` directory are included automatically by any executable that uses the library:

```cmake
target_include_directories(mathlib PUBLIC .)
```

### Activity 5 - Building libraries with CMake

The folder `activity5` contains two folders - `lib` and `main`.
The `lib` folder contains some source and header files (`functions.c` and `functions.h`, among other things) that you can use to create a library.
This library must then be used by the program in the `main` folder.

The `CMakeLists.txt` file for the program (in the `main` directory) is already given and must not be modified.
You'll need to create two `CMakeLists.txt` files: one in the root of the project directory, and one in the `lib` directory.
Like you did in a previous activity, the `CMakeLists.txt` file in the root of the project should include the `CMakeLists.txt` files in the `lib` and `main` directories using `add_subdirectory`.
Make sure that the header files in the `lib` directory are included automatically by any executable that uses the library.

When you have created the `CMakeLists.txt` files, build the project using the CMake extension in VS Code and verify that the program works correctly.
When you're done, paste the contents of the two `CMakeLists.txt` files you created into the markdown file, below.

```cmake
# TODO: insert the contents of the CMakeLists.txt file in the root of the project here
cmake_minimum_required(VERSION 3.20)

project(Activity5)

add_subdirectory(lib)
add_subdirectory(main)

```

```cmake
# TODO: insert the contents of the CMakeLists.txt file in the lib directory here
add_library(mylib numberfun.c functions.c)
target_compile_options(mylib PRIVATE -Wall -Wextra -pedantic -Werror)
target_include_directories(mylib PUBLIC .)
```

## CMake Modules

In CMake, modules are pre-defined scripts that provide additional functionality, simplify common tasks, or help find and configure third-party libraries. They are essentially .cmake files that you can include and execute in your CMakeLists.txt.

The purpose of many CMake modules is to find and configure third-party libraries.
As part of the CMake distribution, there are a number of modules that can be used to find and configure libraries such as `ncurses`, `OpenGL`, `OpenMP`, and many others.
A list can be found in the [CMake documentation](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html).

To use a module, you can use the `find_package` command in your `CMakeLists.txt` file.
For example, to find and configure the `ncurses` library, you can use the following command:

```cmake
find_package(Curses REQUIRED)
```

Depending on the library, this command may set a number of variables that you can next use in your `CMakeLists.txt` file.
For example, the `Curses` module sets the `CURSES_INCLUDE_DIRS` and `CURSES_LIBRARIES` variables, which you can use to include the necessary directories and libraries in your project (these can then be used in the `target_include_directories` and `target_link_libraries` commands).
For a full list, consult the documentation of the CMakes module you are using.

### Activity 6 - Using the Curses library with CMake

The folder `activity6` contains a source file that relies on the `ncurses` library to print "Hello, World!" in the center of a window.
To build the program, you need to link it to the `ncurses` library.

Write a `CMakeLists.txt` file that builds the program and links it to the `ncurses` library.
Use the `find_package` command to find and configure the `ncurses` library, and use the `target_include_directories` and `target_link_libraries` commands to include the necessary directories and libraries in your project.

When you have created the `CMakeLists.txt` file, build the project using the CMake extension in VS Code.
Make sure that the program builds and runs correctly by running it in the (external, so not within VS Code) terminal.

If the program can be built and run successfully, paste the contents of the `CMakeLists.txt` file into the markdown file.

```cmake
# TODO: insert the contents of your CMakeLists.txt file here
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(Activity6)

# Find the ncurses library
find_package(Curses REQUIRED)

# Include the ncurses directories
target_include_directories(${CURSES_INCLUDE_DIR})

# Add the source file to the project
add_executable(activity6 main.c functions.c)

# options passed to compiler per target
target_compile_options(activity6 PRIVATE -Wall -Wextra -pedantic -Werror)

# Link the ncurses library to the executable
target_link_libraries(activity6 ${CURSES_LIBRARIES})
```

### Activity 7 - Debugging with GDB in VS Code

The folder `activity7` contains a program that contains a bug.
The program allows a user to enter a valid arithmetic expression (including parentheses, addition, subtraction, multiplication, and division operators) and then evaluates the expression, but it does not work correctly - it returns 0.0 for any expression entered.
This is due to one particular line of code, in `parser.c`, that contains a bug.

To be able to debug the program, create a `CMakeLists.txt` file for the project.
You can do this manually, of by using the "Quick Start" command (from the CMake extension in the command palette).

Open the folder in VS Code and set a breakpoint at the beginning of the `main` function so that the debugger will stop at that point.
Next, start the debugger by pressing `Shift+F5`, or use the command palette and select the command `CMake: Debug`.
Use the "step into" button to step through the program and find the bug.

The program makes a lot of use of pointers, so you may need to use the "watch" feature in the debugger to see the values of the pointers.

When you have found the bug, fix it and verify that the program works correctly.
If you have indeed fixed the problem, include the code you changed, plus a description of the bug and how you fixed it, in the code block below.

**NOTE**: If you're using a Mac, you may need to install the `gdb` debugger using `brew install gdb` before you can use it in VS Code.
If you can't get it to work, contact your lab teacher for help.

```c
// TODO: describe what the bug was and how you fixed it
> Bug: The result of strtod was not stored in the *result pointer, which meant the number parsed from the string was ignored, leading to 0.0 being returned for all expressions.
> If the result is not stored in *result pointer, the program has no way of knowing what the parsed number is. This causes calculations like 2 + 3 to fail because the functions don't have the intermediate values to continue.
> Fix: Assign the return value of strtod to *result pointer.
```
```c
// TODO: include the full code of the function you changed here as well
const char *parse_number_or_pexpression(const char *calculation, double *result, bool *error) {
    // skip whitespace
    calculation = skip_whitespace(calculation);

    // check if this is a parenthesized expression or a number
    if (*calculation == '(') {
        // if it's a parenthesized expression, calculate the sum inside the parentheses
        calculation = calculate_sum(calculation + 1, result, error);

        // next, skip any whitespace
        calculation = skip_whitespace(calculation);

        // there should now be a closing parenthesis. If it's missing, set the error flag and return the calculation pointer
        if (*calculation != ')') {
            *error = true;
            return calculation;
        }

        // move the calculation pointer past the closing parenthesis, skipping any trailing whitespace
        return skip_whitespace(calculation + 1);
    }
    else {
        // if it's not a parenthesized expression, it should be a number
        // use the strtod() function to parse the number
        // this function modifies a pointer to the first character that couldn't be parsed as a number
        char *end;  // will point to the first character that couldn't be parsed as a number
        *result = strtod(calculation, &end);    // parse the number

        // if end is pointing to the beginning of the string, then no number was found, so it's an error
        if (end == calculation) *error = true; 

        // return the calculation pointer, skipping any trailing whitespace
        return skip_whitespace(end);
    }
}

```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will mark it with 0 points in Brightspace.
If you receive 0 points, make sure to check the feedback, make the necessary changes, and resubmit the tutorial.
Do this before the end of week 2.9, as this is the deadline for having submitted all tutorials and assignments.


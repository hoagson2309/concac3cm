# Week 4 - Tutorial 1: Writing functions

Name: SON CAO

Group: ETI1V.IA

Date: 24/09/2024

## Introduction

When writing programs, you'll often need to use the same code in multiple places.
Rather than copying the same code over and over, you can put the code in a *function*, and call the function whenever you need to use the code.
This makes your code easier to read and maintain.

In this tutorial, you will learn how to write functions in C, and how to use them in your programs.

### Activity 0 - Update the system

Before you start with this tutorial, make sure your system is up-to-date by running the following commands in the terminal:

```bash
sudo apt update
sudo apt upgrade
```

### Activity 1 - Set up a folder for this tutorial

Create a folder (directory) for this week's tutorial in your preferred location, and copy the files [`functions.h`](../code/functions.h) and [`functions.c`](../code/functions.c) into this folder.

It's recommended to have a folder for each week, and within that folder a folder for each tutorial, to keep your work organized.
Open up the folder in VS code by selecting the folder in the File->Open menu, or by right-clicking on the folder in your file browser and selecting "Open in VS Code" (if this option is available).

Alternatively, you can open the folder from a WSL terminal by typing the `code .` command.

## Writing a function that returns a value

The following program asks the user to enter a number between 1 and 10 (including both 1 and 10), and stores the number in the `number` variable.
If the user does not enter a number between 1 and 10, the program will repeatedly ask the user for input until the user enters a valid number.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter a number between 1 and 10: ");
    int number = read_int();

    while (number < 1 || number > 10) {
        printf("The number must be between 1 and 10, try again!\n");
        printf("Enter a number between 1 and 10: ");
        number = read_int();
    }

    printf("You entered the number %d\n", number);
    return 0;
}
```

### Activity 2 - Writing a function

Create a new file called `activity2.c` in the folder for this tutorial, and copy the program listed above into the file.
Next, modify the program so that the code that checks if the number is between 1 and 10 is put into a function called `read_number`, so that the `main` function looks like this:

```c
int main(void) {
    int number = read_number();
    printf("You entered the number %d\n", number);
    return 0;
}
```

Make sure to describe what the function `read_number` does in a comment above the function definition.
Use the `@brief` tag to describe what the function does, and the `@return` tag to describe what it returns.

Paste the contents of `activity2.c` into the code block:

```c
// TODO: include your code here
/* @brief Prompts the user to enter a number between 1 and 10, and keeps asking until a valid number is provided.
 * 
 * @return The valid number entered by the user, between 1 and 10.
 */
#include <stdio.h>     
#include "functions.h"
int read_number(void){
    printf("Enter a number between 1 and 10: ");
    int number = read_int();
    while (number < 1 || number > 10) {
        printf("The number must be between 1 and 10, try again!\n");
        printf("Enter a number between 1 and 10: ");
        number = read_int();
    }
    return number;
}

int main(void) {
    int number = read_number();
    printf("You entered the number %d\n", number);
    return 0;
}
```

## Passing arguments to a function

The `read_number` function is not very generic, since it only reads numbers between 1 and 10.
What if we would like to read numbers between 1 and 100, or between 10 and 20 instead?
In order to be able to reuse the same function for this, we must add two parameters to the function, which allow us to pass the minimum and maximum values as arguments.

### Activity 3 - Adding parameters

Create a new file `activity3.c` in the folder for this tutorial, and copy the contents of `activity2.c` into the file.
Next, modify the `read_number` function so that it has two parameters: `min` and `max`, which specify the minimum and maximum values that the number must be between.
Update the description of the function so that it has `@param` tags for the `min` and `max` parameters, which describe what the parameters are used for.

Use the following `main` function to test your `read_number` function:

```c
int main(void) {
    int number = read_number(1, 10);
    printf("You entered the number %d\n", number);
    number = read_number(10, 20);
    printf("You entered the number %d\n", number);
    number = read_number(-42, 42);
    printf("You entered the number %d\n", number);
    return 0;
}
```

Paste the contents of `activity3.c` into the code block:

```c
// TODO: include your code here
/* Asks the user to enter a number between a given minimum and maximum range.
 * @param min The minimum value that the user can enter.
 * @param max The maximum value that the user can enter.
 * @return The number entered by the user, which is guaranteed to be between min and max.
 */
#include <stdio.h>     
#include "functions.h"
int read_number(int min, int max){
    printf("Enter the number between %d and %d: ", min, max);
    int number = read_int();
    while(number < min || number > max){
        printf("Please try again!\n");
        printf("Enter the number between %d and %d: ", min, max);
        number = read_int();
    }
    return number;
}

int main(void) {
    int number = read_number(1, 10);
    printf("You entered the number %d\n", number);
    number = read_number(10, 20);
    printf("You entered the number %d\n", number);
    number = read_number(-42, 42);
    printf("You entered the number %d\n", number);
    return 0;
}
```

### Activity 4 - Using a function result in an expression

Create a new file `activity4.c` in the folder for this tutorial, and copy the contents of `activity3.c` into the file.
Next, modify the `main` function of the file so that it does not store the results of the `read_number` function calls in a variable, but instead uses the result directly in the `printf` function.

Paste the contents of `activity4.c` into the code block:

```c
// TODO: include your code here
#include <stdio.h>     
#include "functions.h"
int read_number(int min, int max){
    printf("Enter the number between %d and %d: ", min, max);
    int number = read_int();
    while(number < min || number > max){
        printf("Please try again!\n");
        printf("Enter the number between %d and %d: ", min, max);
        number = read_int();
    }
    return number;
}

int main(void) {
    printf("You entered the number %d\n", read_number(1, 10));
    printf("You entered the number %d\n", read_number(10, 20));
    printf("You entered the number %d\n", read_number(-42, 42));
    return 0;
}
```

### Activity 5 - Moving the function to a separate file

Create a new file `activity5.c` in the folder for this tutorial, and copy the contents of `activity4.c` into the file.
In the new file, make sure that the function `read_number` is split into a *prototype* and a *definition*.
The prototype must have some comments above it that describe what the function does, and the parameters that it takes (you've done this in activities 2 and 3).

Next, move the prototype from the `activity5.c` file into the file `functions.h`, and the definition into a new file `functions.c`.
Your `main.c` file should now contain only the `main` function, plus two `#include` directives for `stdio.h` and the `functions.h` file.

Ensure that the program compiles and runs correctly after moving the function to a separate file, by running the following commands in the terminal:

```bash
gcc -Wall -o activity5 activity5.c functions.c
./activity5
```

If the program compiles without errors & warnings, and runs successfully, then you've completed this activity.

Paste the contents of `activity5.c` into the code block:

```c
// TODO: include your code here
#include <stdio.h>     
#include "functions.h"
int main(void) {
    printf("You entered the number %d\n", read_number(1, 10));
    printf("You entered the number %d\n", read_number(10, 20));
    printf("You entered the number %d\n", read_number(-42, 42));
    return 0;
}
```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will get in touch with you.

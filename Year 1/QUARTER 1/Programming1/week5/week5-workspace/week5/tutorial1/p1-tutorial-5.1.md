# Week 5 - Tutorial 1: Using arrays

Name: SON CAO

Group: ETI1V.IA

Date: 30/09/2024

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

### Activity 1 - Open the workspace of this week

Open the workspace of this weeek by opening the `week5.code-workspace` file in VS Code.
In this tutorial, you'll be working in the `tutorial1` folder.

Alternatively, you can open the workspace from a WSL terminal by typing the `code week5.code-workspace` command from the root folder of the workspace.

## Storing values in an array

The following program asks the user to enter 10 numbers, and stores all these numbers in 10 separate variables.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number1 = read_int();
    int number2 = read_int();
    int number3 = read_int();
    int number4 = read_int();
    int number5 = read_int();
    int number6 = read_int();
    int number7 = read_int();
    int number8 = read_int();
    int number9 = read_int();
    int number10 = read_int();
    printf("You entered the numbers %d, %d, %d, %d, %d, %d, %d, %d, %d, and %d\n", number1, number2, number3, number4, number5, number6, number7, number8, number9, number10);
    return 0;
}
```

### Activity 2 - Replacing variables with an array

Open the file `activity2.c` that is in the folder for this tutorial, and copy the program listed above into the file.
Next, modify the program so that the code uses an array that can store 10 integers, instead of 10 separate variables.
The program should still ask the user to enter 10 numbers, and store these numbers in the array.
Finally, the program should print out all the numbers (print each number on a separate line) that the user entered, using a loop to iterate over the array.

Paste the contents of `activity2.c` into the code block:

```c
// TODO: include your code here
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number[10];
    for(int i = 0; i < 10; i++){
        number[i] = read_int();
    }
    for(int i = 0; i < 10; i++){
    printf("You entered the numbers: %d\n", number[i]);
    }
    return 0;
}

```

## Using only part of an array

Oftentimes, you may want to use only part of an array, for example, if you have an array of 10 numbers, but only 5 of them have been filled in.
This could happen if you ask the user to enter a number of values, but the user enters fewer values than you asked for.
In such cases, you may want to keep track of both the size of the array and _how many_ values have been entered into the array.

The following program generates random numbers and stores them in an array of size 100, but stops when a number less than 5 is generated, printing out only the numbers that were generated.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for random_int

int main(void) {
    int numbers[100];   // array to store the numbers
    int count = 0;      // how many numbers were stored
    int number = random_int(0, 100);

    while (number >= 5 && count < 100) {
        numbers[count] = number;
        count++;
        number = random_int(0, 10);
    }
    printf("%d numbers were generated:\n", count);
    for (int i = 0; i < count; i++) {
        printf("Number %d: %d\n", i + 1, numbers[i]);
    }
    return 0;
}
```

Note that when the loop stops, the `count` variable contains the number of values that were stored in the array.
While the loop is running, the `count` variable is used to keep track of the next index in the array where a value should be stored.
In fact, the number of values stored in an array is also the index of the next value that should be stored.

### Activity 3 - Storing values until a user enters a specific value

Open the file `activity3.c`, and copy the contents of `activity2.c` into the file.
Next, modify the program so that it stops asking the user for numbers when the user enters a number that is negative or zero (so that only numbers greater than zero are stored).
Finally, the program should print out only the numbers that the user entered, using a loop to iterate over the array.

Example output of the program:

```bash
Enter a number: 5
Enter a number: 10
Enter a number: 0
You entered the following values:
5
10
```

Paste the contents of `activity3.c` into the code block:

```c
// TODO: include your code here
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number[100];
    int count = 0;
    printf("Enter the numbers: ");
    int numberss = read_int();
    while (numberss > 0) {
        number[count] = numberss;
        count++;
        printf("Enter the numbers: ");
        numberss = read_int();
    }
    for(int i = 0; i < count; i++){
    printf("You entered the numbers: %d\n", number[i]);
    }
    return 0;
}

```

## Printing the contents of an array on a single line

When you print the contents of an array, you may want to print all the values on a single line, separated by a comma and a space.
The tricky part here is that you don't want to print the separator after the last value in the array, or before the first value in the array.
When using a loop to print the contents of the array, this means that you have to check whether you are printing the first / last value, or any other value in the array.

There are various ways to do this, but one way is to print the first value before the loop, and then print the separator and the next value for all values except the first one.
Finally, print the last value after the loop.

Here is an example code snippet that prints the contents of an array on a single line:

```c
int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
printf("%d", numbers[0]);
for (int i = 1; i < 10; i++) {
    printf(", %d", numbers[i]);
}
printf("\n");
```

### Activity 4 - Printing the user's input on a single line

Open the file `activity4.c`, and copy the contents of `activity3.c` into the file.
Next, modify program so that it prints all the numbers that the user entered on a single line, separated by a comma and a space.
Finally, the program should print a newline character after printing all the numbers.

Make sure that your program also works correctly if the user did not enter any numbers (i.e., if the user entered a negative number or zero as the first number)!

Paste the contents of `activity4.c` into the code block:

```c
// TODO: include your code here
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number[100];
    int count = 0;
    printf("Enter the numbers: ");
    int numberss = read_int();
    while (numberss > 0) {
        number[count] = numberss;
        count++;
        printf("Enter the numbers: ");
        numberss = read_int();
    }
    printf("%d", number[0]);
    for(int i = 1; i < count; i++){
    printf(", %d", number[i]);
    }
    printf(".\n");
    return 0;
}

```

When printing all elements of an array on a single line like you did in the previous activity, you use the fact that the first element to be printed is the one at index 0.
But what if you only want to print some of the elements in the array, for example, only the numbers that are greater than 5?
In that case you don't know in advance which element will be the first one to be printed, so you need to check whether you are printing the first element in the array or not.
A common way to do this is to use an `if` statement to check whether you are printing the first element, and only print the separator if you are not printing the first element, like this:

```c
int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
bool printed_first = false; // whether the first number has been printed
for (int i = 0; i < 10; i++) {
    if (numbers[i] > 5) {
        if (printed_first) printf(", ");    // print separator if not the first number
        printed_first = true;               // the first number has been printed
        printf("%d", numbers[i]);
    }
}
printf("\n");
```

### Activity 5 - Filtering elements

Open the file `activity5.c`, and copy the contents of `activity4.c` into the file.
Modify the program so that it prints only the numbers that are greater than 5.
The numbers should still be printed on a single line, separated by a comma and a space, and a newline character should be printed after all the numbers.

Paste the contents of `activity5.c` into the code block:

```c
// TODO: include your code here
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number[100];
    int count = 0;
    bool printed_first = false;
    printf("Enter the numbers: ");
    int numberss = read_int();
    while (numberss > 0) {
        number[count] = numberss;
        count++;
        printf("Enter the numbers: ");
        numberss = read_int();
    }
    printf("You entered the following values: ");
    for(int i = 0; i < count; i++) {
        if (number[i] > 5) {
        if (printed_first) printf(", ");    // print separator if not the first number
        printed_first = true;               // the first number has been printed
        printf("%d", number[i]);
        }
    }
        printf(".\n");
    return 0;
}

```

## Magic numbers

A *magic number* is a number that appears in a program without any explanation of what it represents.
Magic numbers could refer to all kinds of things, such as the number of elements in an array, the maximum value that a user can enter, or the number of times a loop should run.
Magic numbers make your code harder to read and understand, and should be avoided.

In case you need to refer to the size of an array, you should use the `sizeof` operator to get the size of the array (see the slides of this week).

### Activity 6 - No magic numbers

Open the file `activity6.c`, and copy the contents of `activity5.c` into the file.
Modify the program so that it uses the `sizeof` operator to get the size (number of elements) of the array, instead of using a magic number.
Make sure that the program still works correctly after this change.

Paste the contents of `activity6.c` into the code block:

```c
// TODO: include your code here
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    int number[10];
    int count = 0;
    bool printed_first = false;
    int numberss;
    int Num = sizeof(number) / sizeof(number[0]);

    printf("Enter the numbers: ");
    numberss = read_int();
    while (numberss > 0 && count < Num) {
        number[count] = numberss;
        count++;
        printf("Enter the numbers: ");
        numberss = read_int();
    }
    
    printf("You entered the following values: ");
    for(int i = 0; i < count; i++) {
        if (number[i] > 5) {
        if (printed_first) printf(", ");    // print separator if not the first number
        printed_first = true;               // the first number has been printed
        printf("%d", number[i]);
        }
    }
        printf(".\n");
    return 0;
}

```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will get in touch with you.

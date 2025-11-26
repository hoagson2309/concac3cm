# Week 3 - Tutorial 2: For-loops and nested loops

Name: SON CAO
Group: ETI1V.IA
Date: 17/09/2024

## Introduction

Whereas the `while` loop is used to repeat code while a certain condition is true, the `for` loop is used to repeat code a certain number of times.
The `for` loop is often used when you know in advance how many times you want to repeat the code.

By nesting loops, you can create more complex patterns and structures.
In this tutorial, you will use for-loops and nested loops to solve problems.

### Activity 0 - Set up a folder for this tutorial

Create a folder (directory) for this tutorial in the same folder where you've stored the previous tutorial.
Next, open the folder in VS code by selecting the folder in the File->Open menu, or by right-clicking on the folder in your file browser and selecting "Open in VS Code" (if this option is available).

Alternatively, you can open the folder from a WSL terminal by typing the `code .` command.
If you've installed the C/C++ extension, then doing so will give you code completion and error highlighting for the code you write.

## Printing numbers with a for-loop

Anything that can be done with a `while` loop can also be done with a `for` loop, and vice versa.
The `while` loop is typically used when you don't know in advance how many times you want to repeat the code.
You've done this in the first tutorial of this week, where often the condition is based on user input.

The following program uses a `while` loop to print the numbers from 1 to 10.

```c
#include <stdio.h>      // for printf

int main(void) {
    int i = 1;              // initialization
    while (i <= 10) {       // condition
        printf("%d\n", i);
        i++;                // increment
    }

    return 0;
}
```

Note that although the initialization, condition, and increment are three separate parts in the `while` loop, they belong together as they jointly control how often the loop is executed.

The `for` loop is a more compact way of writing a loop that repeats a certain number of times.
The program listed above can be rewritten using a `for` loop as follows:

```c
#include <stdio.h>      // for printf

int main(void) {
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }

    return 0;
}
```

### Activity 1 - Printing only multiples of three

The following program uses a `while` loop to print all numbers between 1 and 100 that are multiples of three, from high to low.
    
```c
#include <stdio.h>      // for printf

int main(void) {
    int i = 99;            // initialization
    while (i >= 1) {        // condition
        printf("%d\n", i);
        i -= 3;                // decrement
    }

    return 0;
}

```

Create a file called `activity1.c` in the folder for this tutorial, and paste the code above into the file.
Modify the program so that it uses a `for`-loop to print all numbers between 1 and 100 that are multiples of three, from high to low (i.e., 99, 96, 93, etc.).
You are not allowed to use any `if` statements in your program.

Copy the code you wrote into the code block listed below when you're done:

```c
// TODO: Include your program by copying and pasting it into this code block.
#include <stdio.h>      // for printf

int main(void) {
    int i = 99;            // initialization
    for (i = 99; i >= 1; i-=3)
    {
        printf("%d\n", i);
    }
    return 0;
}
```

## Nested loops

Nested loops are loops that are placed inside other loops.
This means that the inner loop is executed multiple times for each iteration of the outer loop.

The following program uses a nested loop to print a 10x10 multiplication table.

```c
#include <stdio.h>      // for printf

int main(void) {
    for (int i = 1; i <= 10; i++) {
        // print the i-th row of the multiplication table
        for (int j = 1; j <= 10; j++) {
            // print the product of i and j
            printf("%4d", i * j);
        }
        printf("\n");   // newline after each row
    }

    return 0;
}
```

## Printing 2D patterns with nested loops

The following program uses a nested loop to print a triangle of asterisks.
The height of the triangle is controlled by the user, who enters the number of rows.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the number of rows: ");
    int rows = read_int();
    for (int i = 1; i <= rows; i++) {
        // print the i-th row of the triangle
        for (int j = 1; j <= i; j++) {
            // print an asterisk
            printf("*");
        }
        printf("\n");   // newline after each row
    }

    return 0;
}
```

Below is an example of the output of the program when the user enters 5:

```plaintext
Enter the number of rows: 5
*
**
***
****
*****
```

### Activity 2 - Printing a triangle

Create a file called `activity2.c` in the folder for this tutorial, and paste the code above into the file.
Modify the program so that it prints a triangle of numbers instead, with the widest row first.
In order to nicely align the numbers, you can use the `%3d` format specifier to print each number right aligned in a field of width 3.
Below is shown an example output of the program in case the user enters 5:

```plaintext
Enter the number of rows: 5
  5  4  3  2  1
  4  3  2  1
  3  2  1
  2  1
  1
```

Copy the code you wrote into the code block listed below when you're done:

```c
// TODO: Include your program by copying and pasting it into this code block.
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the number of rows: ");
    int rows = read_int();
    for (int i = rows; i >= 1; i--) {
        // print the i-th row of the triangle
        for (int j = i; j >= 1; j--) {
            // print an asterisk
            printf("%3d", j);
        }
        printf("\n");   // newline after each row
    }

    return 0;
}


```

## Using accumulators in loops

In the previous tutorial, you have used an *accumulator* variable to count the number of non-zero numbers entered by the user.
Such an accumulator variable is a variable that is updated inside a loop, to keep track of a certain value.

Similarly, you can use an accumulator variable to keep track of which number to print next in a grid of numbers.

### Activity 3 - Printing a grid of numbers

Create a file called `activity3.c` in the folder for this tutorial.
Write a program (a starting point is given below) that uses nested loops to print a grid of numbers, as shown below:

```plaintext
Enter the number of rows: 5

 1  2  3  4  5
 6  7  8  9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25
```

Copy the code you wrote into the code block listed below when you're done:

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the number of rows: ");
    int rows = read_int();

    // TODO: include code to print a 5x5 grid of numbers
    int a = 1;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            printf("%3d", a);
            a++;
        }
        printf("\n");  
    }
    return 0;
}

```

### Activity 4 - Counting sixes

The following program generates 10 random numbers between 1 and 6, and prints how many of these numbers are sixes.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for random_int

int main(void) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        int number = random_int(1, 6);  // generate a random number between 1 and 6
        if (number == 6) {
            count++;
        }
    }
    printf("Number of sixes: %d\n", count);

    return 0;
}
```

Create a file called `activity4.c` in the folder for this tutorial, and paste the code above into the file.

Modify the program so that it asks the user to enter the number of random numbers to generate, and prints how many of these numbers are sixes.
The program should then again ask the user to enter the number of random numbers to generate and print the six-count, and keep doing this until the user enters zero.

This means that your program will have a loop inside the `main` function that keeps asking the user for input until the user enters zero.
Within this loop, you will have another loop that generates the random numbers and counts the number of sixes, like in the original program.

An example output of the program is shown below:

```plaintext
Enter the number of random numbers to generate: 5
Number of sixes: 1
Enter the number of random numbers to generate: 10
Number of sixes: 2
Enter the number of random numbers to generate: 0
```

Copy the code you wrote into the code block listed below when you're done:

```c
/// TODO: Include your program by copying and pasting it into this code block.
#include <stdio.h>      // for printf
#include "functions.h"  // for random_int

int main(void) {
    int count = 0;
    printf("enter number: ");
        int number = read_int();  
    for (int i = 0; i < number; i++) {
        int a = random_int(1, 6);
        if (a == 6) {
            count++;
        }
    }
    printf("Number of sixes: %d\n", count);

    return 0;
}
```

### Activity 5 - Summing odd numbers

Create a file called `activity5.c` in the folder for this tutorial.
In this file, write a program that asks the user to enter an odd number, and then prints the sum of all odd numbers between 1 and the number entered by the user.
For example, if the user enters 7, the program should print `16` (1 + 3 + 5 + 7).

You can use the following code as a starting point:

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter a positive odd number: ");
    int number = read_int();
    while (number % 2 == 0 || number < 1) {
        printf("That's even or negative, please enter a positive odd number: ");
        number = read_int();
    }
    
    return 0;
}
```

Copy the code you wrote into the code block listed below when you're done:

```c
// TODO: Include your program by copying and pasting it into this code block.
#include <stdio.h>     // for printf
#include "functions.h" // for read_int

int main(void)
{
    printf("Enter a positive odd number: ");
    int number = read_int();
    while (number % 2 == 0 || number < 1)
    {
        printf("That's even or negative, please enter a positive odd number: ");
        number = read_int();
    }

    int i, sum = 0;
    for (i = 1; i <= number; i += 2)
    {
        sum += i;
    }
    printf("The sum of odd numbers from 1 to %d is: %d\n", number, sum);

    return 0;
}
```

## Sign off

To sign off this tutorial, you will need to demonstrate the following things:

* You have implemented the requested programs and ensured that they work correctly.
* You can make small changes on request to the programs you've written.
* You have answered all questions in the markdown file, and have submitted it at the correct submit point in Brightspace

Once you've successfully demonstrated the items listed above, your lab teacher will mark the tutorial as completed.
You'll need to sign off this tutorial before you can continue with the assignments of this week.

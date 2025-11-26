# Week 2 - Tutorial 1: Variables and data types

Name: SON CAO

Group: ETI1V.IA

Date: 23/09/2005

## Introduction

### Activity 0 - Update the system

Before you start with this tutorial, make sure your system is up-to-date by running the following commands in the terminal:

```bash
sudo apt update
sudo apt upgrade
```

## Data types

In C, you can work with different kinds of data, such as numbers and text.
This data is stored in *variables*, which are named memory locations that can store a value.
To use a variable in C, you first need to declare it by specifying its *data type* and name, and possibly assign a value to it, like this:

```c
int number = 42;
float pi = 3.14159f;
char letter = 'A';
```

## Integers and floats

Integers are whole numbers, like 1, 2, 3, and so on.
In C, you can declare integer variables using the `int` data type.
Floats are numbers with a decimal point, like 1.0, 2.0, 3.0, and so on.
They are declared using the `float` data type.

When you perform arithmetic operations on integers, the result is also an integer.
This means that if you divide two integers, the result will be an integer, and the decimal part will be truncated.

### Activity 1 - Fix the program

The program listed below should compute the average of three integers entered by the user, but it does not work properly.
Fix the program so that it calculates the average correctly, without changing the types of the variables `a`, `b`, and `c`.
List your updated program in the markdown file, and explain what you changed to make it work.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the first number: ");
    int a = read_int();
    printf("Enter the second number: ");
    int b = read_int();
    printf("Enter the third number: ");
    int c = read_int();
    int average = (a + b + c) / 3;

    printf("The average of %d, %d, and %d is %d\n", a, b, c, average);

    return 0;
}

//MY ANSWER!!!!:
//I basically just change int to float so that it can calculate in the more accurate way.
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the first number: ");
    float a = read_float();
    printf("Enter the second number: ");
    float b = read_float();
    printf("Enter the third number: ");
    float c = read_float();
    float average = (a + b + c) / 3;

    printf("The average of %f, %f, and %f is %f\n", a, b, c, average);

    return 0;
}

```

## Variables

Data is stored in memory.
Rather than referring to this data through some kind of number that indicates where in memory this data is located, we use *variables*.
Variables have names that we can use to refer to the data they store.
In C, variable names must start with a letter or an underscore, and can contain letters, digits, and underscores.
It is important to choose meaningful names for your variables, so that your code is easier to understand.

### Activity 2 - Variable names

The variables in the following program have names that are not very descriptive. Change the names of the variables to make the program easier to understand.
Hint: use the `F2` key in Visual Studio Code to rename variables.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_float

int main(void) {
    // NOTE the following formulas:
    //  Diameter of circle = 2 * radius
    //  Area of circle = pi * radius * radius
    //  Circumference of circle = diameter * pi
    printf("Enter radius of first circle: ");
    float a = read_float();
    printf("Enter radius of second circle: ");
    float b = read_float();
    printf("Enter radius of third circle: ");
    float c = read_float();
    const float d = 3.14159f;
    float e = a * a * d;
    float f = 2 * a;
    float g = d * f;
    float h = b * b * d;
    float i = 2 * b;
    float j = d * i;
    float k = c * c * d;
    float l = 2 * c;
    float m = d * l;

    printf("First circle: radius = %.2f, diameter = %.2f, ", a, f);
    printf("circumference = %.2f, area = %.2f\n", g, e);
    printf("Second circle: radius = %.2f, diameter = %.2f, ", b, i);
    printf("circumference = %.2f, area = %.2f\n", j, h);
    printf("Third circle: radius = %.2f, diameter = %.2f, ", c, l);
    printf("circumference = %.2f, area = %.2f\n", m, k);
    return 0;
}
//MY ANSWER!!!!!!!: 
#include <stdio.h>     // for printf
#include "functions.h"  // for read_float

int main(void) {
    // NOTE the following formulas:
    //  Diameter of circle = 2 * radius
    //  Area of circle = pi * radius * radius
    //  Circumference of circle = diameter * pi
    printf("Enter radius of first circle: ");
    float radius1 = read_float();
    printf("Enter radius of second circle: ");
    float radius2 = read_float();
    printf("Enter radius of third circle: ");
    float radius3 = read_float();

    const float pi = 3.14159f;
    
    // First circle calculations
    float area1 = pi * radius1 * radius1;
    float diameter1 = 2 * radius1;
    float circumference1 = pi * diameter1;

    // Second circle calculations
    float area2 = pi * radius2 * radius2;
    float diameter2 = 2 * radius2;
    float circumference2 = pi * diameter2;

    // Third circle calculations
    float area3 = pi * radius3 * radius3;
    float diameter3 = 2 * radius3;
    float circumference3 = pi * diameter3;

    // Output for first circle
    printf("First circle: radius = %.2f, diameter = %.2f, ", radius1, diameter1);
    printf("circumference = %.2f, area = %.2f\n", circumference1, area1);

    // Output for second circle
    printf("Second circle: radius = %.2f, diameter = %.2f, ", radius2, diameter2);
    printf("circumference = %.2f, area = %.2f\n", circumference2, area2);

    // Output for third circle
    printf("Third circle: radius = %.2f, diameter = %.2f, ", radius3, diameter3);
    printf("circumference = %.2f, area = %.2f\n", circumference3, area3);

    return 0;
} 
```


## Reusing variables

Variables can be reused to store different values at different times.
This can help you write more concise programs, and reduce the number of variables you need to keep track of.
To reuse a variable, you simply assign a new value to it, like this:

```c
int number = 42;
number = 24;
```

### Activity 3 - Use expressions instead of variables

Modify the program of the previous activity so that it uses expressions to calculate the diameter, circumference, and area of the circles, instead of using variables to store the intermediate results.
This should decrease the number of variables in your program from thirteen down to four: one *constant* variable for the value of pi, and three variables to store the radii of the three circles.

List your updated program in the code block below:

```c
// Your code here
#include <stdio.h>      // for printf
#include "functions.h"  // for read_float

int main(void) {
    // NOTE the following formulas:
    //  Diameter of circle = 2 * radius
    //  Area of circle = pi * radius * radius
    //  Circumference of circle = diameter * pi

    // Reading the radii of three circles
    printf("Enter radius of first circle: ");
    float radius1 = read_float();
    printf("Enter radius of second circle: ");
    float radius2 = read_float();
    printf("Enter radius of third circle: ");
    float radius3 = read_float();

    const float pi = 3.14159f;

    // Output for first circle, calculating on the fly
    printf("First circle: radius = %.2f, diameter = %.2f, ", radius1, 2 * radius1);
    printf("circumference = %.2f, area = %.2f\n", 2 * pi * radius1, pi * radius1 * radius1);

    // Output for second circle, calculating on the fly
    printf("Second circle: radius = %.2f, diameter = %.2f, ", radius2, 2 * radius2);
    printf("circumference = %.2f, area = %.2f\n", 2 * pi * radius2, pi * radius2 * radius2);

    // Output for third circle, calculating on the fly
    printf("Third circle: radius = %.2f, diameter = %.2f, ", radius3, 2 * radius3);
    printf("circumference = %.2f, area = %.2f\n", 2 * pi * radius3, pi * radius3 * radius3);

    return 0;
}
```

### Activity 4 - Minimize variable usage

Modify the program of the previous activity so that it uses only **two** variables, by reusing / updating the variable that stores the radius of the circle.
Note that this involves reordering the calculations so that the value of the radius is updated before it is used in the next calculation.
Run the program to verify that it still works correctly.

List your updated program in the code block below:

```c
// Your code here
#include <stdio.h>      // for printf
#include "functions.h"  // for read_float

int main(void) {
    // NOTE the following formulas:
    //  Diameter of circle = 2 * radius
    //  Area of circle = pi * radius * radius
    //  Circumference of circle = diameter * pi

    // Reusing one variable for the radius
    float radius;
    const float pi = 3.14159f;

    // Reading and calculating for the first circle
    printf("Enter radius of first circle: ");
    radius = read_float();
    printf("First circle: radius = %.2f, diameter = %.2f, ", radius, 2 * radius);
    printf("circumference = %.2f, area = %.2f\n", 2 * pi * radius, pi * radius * radius);

    // Reading and calculating for the second circle
    printf("Enter radius of second circle: ");
    radius = read_float();
    printf("Second circle: radius = %.2f, diameter = %.2f, ", radius, 2 * radius);
    printf("circumference = %.2f, area = %.2f\n", 2 * pi * radius, pi * radius * radius);

    // Reading and calculating for the third circle
    printf("Enter radius of third circle: ");
    radius = read_float();
    printf("Third circle: radius = %.2f, diameter = %.2f, ", radius, 2 * radius);
    printf("circumference = %.2f, area = %.2f\n", 2 * pi * radius, pi * radius * radius);

    return 0;
}
```

## Swapping variables

Swapping two variables means exchanging their values.
For example, if `a` is 1 and `b` is 2, then after swapping `a` should be 2 and `b` should be 1.
Swapping is a very common operation in programming, and is often used in sorting algorithms and other algorithms that manipulate data.

### Activity 5 - Swapping two variables

Modify the program listed below so that it swaps the values of the variables `a` and `b` before it prints them.
This involves using a third variable to temporarily store the value of one of the variables, so that it can be reassigned to the other variable.
Run the program to verify that it works correctly.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the first number: ");
    int a = read_int();
    printf("Enter the second number: ");
    int b = read_int();

    printf("a = %d, b = %d\n", a, b);
    printf("Swapping...\n");
    // TODO: Swap the values of a and b here
    int temp;
    temp = a;
    a = b;
    b = temp;
    printf("a = %d, b = %d\n", a, b);

    return 0;
}
```

### Activity 6 - Swapping three variables

Modify the program you've written in the previous activity so that it "rotates" the values of three variables `a`, `b`, and `c` before it prints them.
Below is an example of what the program should print to the console when run:

```verbatim
Enter the first number: 1
Enter the second number: 2
Enter the third number: 3
a = 1, b = 2, c = 3
Swapping...
a = 3, b = 1, c = 2
```

List your program in the code block below:

```c
// Your code here
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the first number: ");
    int a = read_int();
    printf("Enter the second number: ");
    int b = read_int();
    printf("Enter the third number: ");
    int c = read_int();

    printf("a = %d, b = %d, c = %d\n", a, b, c);
    printf("Swapping...\n");
    // Swapping the values of three numbers
    int temp = a;
    a = b;
    b = c;
    c = temp;
    printf("a = %d, b = %d, c = %d\n", a, b, c);

    return 0;
}
```

## Using the compiler to detect possible problems with your program

The compiler is a very powerful tool that can help you find problems in your program before you run it.
In case your program has errors, like missing semicolons or undeclared variables, the compiler will not be able to build an executable file, and report the errors it found.

Sometimes, your code does not have errors, but the compiler can still generate **warnings**.
It is important to pay attention to these warnings, as they can indicate potential problems in your code that may lead to unexpected behavior when you run your program.

### Activity 7 - Compiler warnings

Compile the program below with warnings enabled (use the `-Wall` flag), and list the warnings that the compiler generates.
Explain what each warning means, and how you can fix it.

Copy the command you used to compile the program, and the warnings that were generated, into the markdown file.

```c
#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter the first number: ");
    int a = read_int();
    printf("Enter the second number: ");
    int b = read_int();
    float sum = (a + b) * 0.5;
    printf("The sum of %f and %d is %d\n", a, b, a + b);
    return 0;
}
```

Command used to compile the program: **TODO** - gcc -Wall -o program ttr1w2.c functions.c

The following warnings were generated: **TODO** -
ttr1w2.c: In function ‘main’:
ttr1w2.c:10:25: warning: format ‘%f’ expects argument of type ‘double’, but argument 2 has type ‘int’ [-Wformat=]
   10 |     printf("The sum of %f and %d is %d\n", a, b, a + b);
      |                        ~^                  ~
      |                         |                  |
      |                         double             int
      |                        %d
ttr1w2.c:9:11: warning: unused variable ‘sum’ [-Wunused-variable]
    9 |     float sum = (a + b) * 0.5;
      |           ^~~
## Sign off

To sign off this tutorial, you will need to demonstrate the following things:

* You can declare variables of type `int` and `float` and assign values to them.
* You can reassign values to variables using the assignment operator `=`.
* You can compile your program with warnings enabled.
* You have answered all questions in the markdown file, and have submitted it at the correct submit point in Brightspace.

Once you've successfully demonstrated the items listed above, your lab teacher will mark the tutorial as completed.
You'll need to sign off this tutorial before you can continue with the next tutorial.

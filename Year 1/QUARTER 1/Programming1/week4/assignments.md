# Week XX - Assignments

Name: SON CAO

Group: ETI1V.IA

Date: 26/09/2024

**NOTE**: if you'd like to have syntax highlighting in your markdown file, install the "Markdown Preview Github Styling" extension in VS Code.

## First assignment

The first assignment I completed is assignment CACULATOR.
This is the code I wrote:

```c
// TODO: Write your code here
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "functions.h"
//Function to check valid operators.
char read_operator(void)
{
    printf("Please enter an operator (+, -, *, /, ^): ");
    char op = read_char();
    while (op != '+' && op != '-' && op != '*' && op != '/' && op != '^'){
            printf("Invalid operator. Please try again.\n");
            printf("Please enter an operator (+, -, *, /, ^): ");
            op = read_char();
        } 
    return op;
}
// CALCULATOR.
float apply_operator(float num1, float num2, char op)
{
    float res;
    switch (op)
    {
    case '+':
        res = num1 + num2;
        break;
    case '-':
        res = num1 - num2;
        break;
    case '*':
        res = num1 * num2;
        break;
    case '/':
        if (num2 != 0)
        {
            res = num1 / num2;
        }
        else
        {
            printf("Error: Division by zero is not allowed.\n");
        }
        break;
    case '^':
        res = pow(num1, num2);
        break;
    default:
        printf("Unexpected error in operator application.\n");
        break;
    }

    return res;
}
// Function to ask the user whether to perform another calculation.
bool perform_another_calculation(void)
{
    bool valid = false;

    while (!valid)
    {
        printf("Do you want to perform another calculation? (y/n): ");
        char ans = read_char();

        if (ans == 'y' || ans == 'Y')
        {
            return true;
        }
        else if (ans == 'n' || ans == 'N')
        {
            return false;
        }
        else
        {
            printf("Invalid input. Please enter 'y' for yes or 'n' for no.\n");
        }
    }

    return false;
}

int main()
{
    float num1, num2, res;
    char op;
    bool another_calculation = true;

    while (another_calculation)
    {
        printf("Please enter a number: ");
        float num1 = read_float();

        printf("Please enter another number: ");
        float num2 = read_float();

        op = read_operator();

        res = apply_operator(num1, num2, op);
        printf("%.4f %c %.4f = %.4f\n", num1, op, num2, res);

        another_calculation = perform_another_calculation();
    }

    printf("Bye!\n");
    return 0;
}
```

## Second assignment

The second assignment I completed is assignment PRETZELS.
This is the code I wrote:

```c
// TODO: Write your code here
#include <stdio.h>
#include <stdbool.h>
#include "functions.h"
/*let the user enter ther number of pretzels in the pile
 *@return pretzels the number of pretzels make up the pile
*/
int print_pretzels(){
    printf("How large should the pile of pretzels be (at least 10)?\n");
    int pretzels = read_int();
    while (pretzels < 10) {
        printf("The pile of pretzels must be at least 10.\n");
        printf("How large should the pile of pretzels be (at least 10)? \n");
        pretzels = read_int();
    }
    return pretzels;
}
/*randomly determine who starts the game and print who starts the game
 *return playersTurn true if it's player's turn, false if vice versa
*/
bool print_playersTurn(){
    bool playersTurn = true;
    if (random_int(0, 1) == 0) {
        playersTurn = false;
    }
    if (playersTurn) {
        printf("You start!\n");
    } else {
        printf("The computer starts!\n");
    }
    return playersTurn;
}

int main(void) {
    printf("Welcome to the Pretzel game!\n");
    printf("The player who takes the last pretzel from the pile loses the game.\n");
    int pretzels;
    pretzels = print_pretzels();
    bool playersTurn;
    playersTurn = print_playersTurn();
    while (pretzels > 0) {
        int taken;
        if (playersTurn) {
            printf("There are %d pretzels left in the pile.\n", pretzels);
            printf("How many pretzels do you want to take? ");
            taken = read_int();
            while (taken < 1 || taken > 3 || taken > pretzels) {
                printf("You can only take 1, 2, or 3 pretzels, and you can't take more pretzels than there are in the pile.\n");
                printf("How many pretzels do you want to take? ");
                taken = read_int();
            }
        } else {
            taken = 1;
            if (pretzels % 4 == 0) {
                taken = 3;
            } else if (pretzels % 4 == 3) {
                taken = 2;
            }
            printf("The computer takes %d pretzels.\n", taken);
        }
        playersTurn = !playersTurn;
        pretzels -= taken;
        }
        
    if (playersTurn) {
        printf("You win!\n");
    } else {
        printf("The computer wins!\n");
    }

    return 0;
}
```

## Third assignment (optional)

I've actually made three assignments this week! The third assignment I completed is assignment ZZZ.
This is the code I wrote:

```c
// TODO: Write your code here
```

# Week 5 - Tutorial 2: Using functions with arrays

Name: SON CAO

Group: ETI1V.IA

Date: 02/10/2024

## Introduction

Before writing a program, it is important to think about how to structure it.
A good way to structure a program is to divide it into smaller parts, each of which performs a specific task.
Each of these smaller parts can then be implemented as a function that has clear input (i.e., parameters) and output (i.e., return value).

In this tutorial, you will write several functions that perform specific tasks, and then combine these functions to create a larger program.

### Activity 0 - Open the workspace of this week

Open the workspace of this weeek by opening the `week5.code-workspace` file in VS Code.
In this tutorial, you'll be working in the `tutorial2` folder.

Alternatively, you can open the workspace from a WSL terminal by typing the `code week5.code-workspace` command from the root folder of the workspace.

The `tutorial2` folder contains the three following files:
- `main.c` for the main program
- `game.h` for the function prototypes
- `game.c` for the function definitions

## Memory game

The program that you will create in this tutorial allows the user to play a simple memory game, where the user has to find pairs of matching numbers.
You will compose this program step by step by writing functions that perform specific tasks.
These tasks are the following:

- Shuffling the cards
- Counting how many cards are face down
- Printing the cards, using asterisks to indicate which cards are face down
- Asking the user to select two cards that are currently face down

Each function will be tested separately before combining them into the final program.
The flow of the final program will be as follows:
1. Shuffle the cards
2. While there are still cards faced down:
    1. Print the cards
    2. Ask the user to select two cards
    3. If the selected cards are a pair, turn them face up

### Shuffling the cards

To keep things simple, we'll play the game with eight "cards", each of which has a number from 1 to 4.
The goal of the game is to find pairs of matching numbers by selecting two cards at a time.
We can keep track of which card is at which position by using an array of integers, like this:

```c
int cards[8] = {1, 1, 2, 2, 3, 3, 4, 4};
```

Of course, the cards should be shuffled before the game starts, so that the pairs are not next to each other.
To do so, we can swap the cards at two random positions in the array multiple times.
Suppose that we have a function `swap` that takes an array and two indices, then the shuffling can be done like this:

```c
/// @brief shuffles an array of integers by swapping two random elements multiple times
/// @param values the array of integers to shuffle
/// @param size the number of elements in the array
/// @param how_many_times the number of times to swap two random elements
void shuffle(int values[], int size, int how_many_times) {
    for (int i = 0; i < how_many_times; i++) {
        int index1 = random_int(0, size - 1);
        int index2 = random_int(0, size - 1);
        swap_elements(values, index1, index2);
    }
}
```

#### Activity 1 - Function for shuffling the cards

Copy the prototype of the shuffle function into the `game.h` file, and its definition into the `game.c` file (don't forget to include `functions.h` in `game.c`).
Add the following prototype to the `game.h` file:

```c
/// @brief swaps two elements in an array
/// @param values the array of integers
/// @param index1 the index of the first element to swap
/// @param index2 the index of the second element to swap
void swap_elements(int values[], int index1, int index2);
```

Add the definition of the `swap_elements` function to the `game.c` file.

Use the following code (for the `main.c` file) that tests the `shuffle` function by shuffling the `cards` array and printing the shuffled cards:

```c
#include <stdio.h>
#include "gameh.h"

int main(void) {
    int cards[8] = {1, 1, 2, 2, 3, 3, 4, 4};
    shuffle(cards, 8, 100);
    for (int i = 0; i < 8; i++) printf("%d ", cards[i]);
}
```

Verify that the card shuffling works correctly by running the program and checking the output.
Finally, include your definition of the `swap_elements` function in the code block below:

```c
// TODO: include your definition of the swap_elements function here
void swap_elements(int values[], int index1, int index2){
    int temp;
    temp = values[index1];
    values[index1] = values[index2];
    values[index2] = temp;
}
```

### Tracking which cards are face up

When playing the game, we'll start with all cards face down, and then turn them face up when the user finds a pair of matching cards.
To keep track of which cards are face up, we can use an array of booleans, where `true` indicates that the card is face up and `false` indicates that the card is face down:

```c
bool face_up[8] = {false};
```

Since `false` is the _default_ value for a boolean array, all non-specified elements will be `false`, so we don't need to initialize the array explicitly.

Next, we'll need to be able to count how many cards are face down - if none are face down, the game is over.

#### Activity 2 - Function for counting face-down cards

Write a function `count_false` that takes an array (marked `const`, since the function doesn't change it) of booleans and its size as parameters, and returns the number of elements in the array that are `false`.
Put the function prototype in the `game.h` file, and the function definition in the `game.c` file.

In the `main.c` file, test the function by creating an array of booleans and counting how many of them are `false`:

```c
#include <stdio.h>
#include "game.h"

int main(void) {
    bool face_up[8] = {false, true, false, false, false, true, false, true};
    printf("There are %d cards face down (should be 5)\n", count_false(face_up, 8));

    bool face_up2[8] = {true, true, true, true, true, true, true, true};
    printf("There are %d cards face down (should be 0)\n", count_false(face_up, 8));
}
```

Verify that the function works correctly by running the program and checking the output.
Finally, include your definition of the `count_false` function in the code block below:

```c
// TODO: include your definition of the count_face_down function here, including description
int count_false(const bool values[], int size){
    int falsenum = 0;
    for (int i = 0; i < size; i++){
        if(!values[i]) falsenum++;
    }
    return falsenum;
}
```

### Asking the user to select a card

The final step is to write a function that asks the user to select a card, and then returns the index of the selected cards.
The user can only select a card that is face down, so the function should keep asking the user for input until the user selects a valid card.
Of course, the function should also check if the user entered a valid index (between 0 and the size of the array minus one).

#### Activity 3 - Function for selecting a card

Write a function `select_face_down_card` that takes an array of booleans and its size as parameters, and returns the index of the selected card.
The function should keep asking the user for input until the user selects a valid index (0..size - 1), which refers to a card that is face down.

Put the function prototype in the `game.h` file, and the function definition in the `game.c` file.

Test the function with the following program:

```c
#include <stdio.h>
#include "game.h"

int main(void) {
    bool face_up[8] = {false};
    int down = count_false(face_up, 8);
    while (down > 0) {
        printf("There are %d cards face down\n", down);
        int index = select_face_down_card(face_up, 8);
        printf("The user selected card %d, turning it face up\n", index);
        face_up[index] = true;
    }
}
```

Verify that the function works correctly by running the program, and testing it with different inputs, including invalid indices (smaller than 0, or greater than 7) and indices of cards that are already face up.
If your function works correctly, then include your definition of the `select_face_down_card` function in the code block below:

```c
// TODO: include your definition of the select_face_down_card function here, including description
int select_face_down_card(const bool values[], int size){
    int a;
    printf("Choose face down cards: ");
    a = read_int();
    while (a < 0 || a > size - 1 || values[a] == true){
        if (a < 0 || a > size - 1){
            printf("TRY AGAIN!");
        }
        else if (values[a]){
            printf("You've chosen a face up card! Try again")
        }
        else{
            return a;
        }
        printf("Choose face down cards: ");
        a = read_int();
    }
    return a;
}
```

### Printing the cards

The building blocks of the game are almost complete - the final step is to write a function that prints the cards, using asterisks to indicate which cards are face down.
This means that the function must know which cards are located at which position, and whether they are face up or face down.
Also, the function must print indices for the cards, so that the user can select a card by entering its index, like this (the user has already found the pairs of 3s and 4s):

```bash
 0  1  2  3  4  5  6  7
** **  3 ** **  3  4  4
```

#### Activity 4 - Function for printing the cards

Write a function `print_cards` that takes an array of integers (the cards), an array of booleans (face up or face down), and the size of the arrays (use only a single parameter for the size, assuming that both arrays have the same size) as parameters.
The function must print the indices of the cards, printing each index, right-aligned in a column of width two (use the `%2d` format specifier for this), followed by a space.
Each card should be printed as two asterisks if it is face down, or as the card number (right-aligned in a column of width two) if it is face up.

Put the function prototype in the `game.h` file, and the function definition in the `game.c` file.

In the main program, test the function by creating an array of integers and an array of booleans, and printing the cards:

```c
#include <stdio.h>
#include "game.h"

int main(void) {
    int cards[8] = {1, 2, 3, 2, 1, 3, 4, 4};
    bool face_up[8] = {false, false, true, false, false, true, true, true};
    print_cards(cards, face_up, 8);
}
```

Verify that the program prints the cards as shown in the example above.
Finally, include your definition of the `print_cards` function in the code block below:

```c
// TODO: include your definition of the print_cards function here, including description
void print_cards(const int cards[], const bool face_up[], int size){
    for (int i=0; i<size; i++){
        printf("%2d: ",i);
    }
    printf("\n");
    for (int i=0; i<size; i++){
        if(faceup[i]){
            printf("%2d: ", cards[i]);
        } else{
            printf("**");
        }
    }
}
```

### Putting it all together

Now that you have written all the functions, you can combine them into a single program that allows the user to play the memory game.
For this, a few more things are needed.

First, we'll need to let the user select *two* cards, not just one.
To do this, we can follow these steps:
1. Ask the user to select a card using the `select_face_down_card` function, and store the index of the selected card.
2. To make sure that the user can't select the card again, turn the selected card face up by setting the corresponding element in the `face_up` array to `true`.
3. Ask the user to select another card, and store the index of the selected card.

Next, we'll need to check if the selected cards are a pair.
This can be done simply by comparing the values of the cards at the selected indices.
If the cards do not form a pair, we should turn them face down again by setting the corresponding elements in the `face_up` array to `false`.

Finally, we'd like to keep track of the number of moves that user has made, and print this at the end of the game.

#### Activity 5 - Final program

Write a program in `main.c` that allows the user to play the memory game, using the functions that you have written in the previous activities.
Follow the steps outlined above to implement the game.

You can use the following code as a starting point for the `main` function:

```c
#include <stdio.h>
#include "game.h"

int main(void) {
    printf("Welcome to the memory game!\n");
    int cards[8] = {1, 1, 2, 2, 3, 3, 4, 4};
    bool face_up[sizeof(cards) / sizeof(cards[0])] = {false};
    const int nr_of_cards = sizeof(cards) / sizeof(cards[0]);
    int rounds = 0;     // the number of rounds played

    // TODO: shuffle the cards
    while (count_false(face_up, nr_of_cards) > 0) {
        // TODO: print the cards
        // TODO: ask the user to select two cards
        // TODO: check if the selected cards are a pair. If not, turn them face down again. If they are, tell the user he found a match
        rounds++;
    }
    // TODO: print the cards (they're all turned face up now)
    printf("Congratulations, you found all pairs in %d rounds!\n", rounds);
}
```

List the contents of your `main.c` file in the code block below:

```c
// TODO: include the contents of main.c here
#include <stdio.h>
#include "game.h"

int main(void) {
    printf("Welcome to the memory game!\n");
    int cards[8] = {1, 1, 2, 2, 3, 3, 4, 4};
    bool face_up[sizeof(cards) / sizeof(cards[0])] = {false};
    const int nr_of_cards = sizeof(cards) / sizeof(cards[0]);
    int rounds = 0;     // the number of rounds played

    

    // TODO: shuffle the cards
    shuffle(face_up, nr_of_cards, random_int(1,20));

    while (count_false(face_up, nr_of_cards) > 0) {
        // TODO: print the cards
        print_cards(cards, face_up, nr_of_cards);
        // TODO: ask the user to select two cards
        printf("Please select face down cards")
        int a = select_face_down_card(face_up, nr_of_cards);
        face_up[a] == true;
        print_cards(cards, face_up, nr_of_cards);

        int b = select_face_down_card(face_up, nr_of_cards);
        face_up[b] == true;
        print_cards(cards, face_up, nr_of_cards);

        // TODO: check if the selected cards are a pair. If not, turn them face down again. If they are, tell the user he found a match
        if (cards[a] == cards[b]){
            printf("You found a match! \n");
        }else{
            printf("This wasn't a pair! \n");
            cards[a] = cards[b] = false;
        }

        rounds++;
    }
    // TODO: print the cards (they're all turned face up now)
    print_cards(cards, face_up, nr_of_cards);
    printf("Congratulations, you found all pairs in %d rounds!\n", rounds);
}
```

## Sign off

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will get in touch with you.

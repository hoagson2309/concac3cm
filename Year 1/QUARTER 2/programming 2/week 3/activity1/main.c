#include <stdio.h>
#include <string.h>
#include "functions.h"

enum item_type{
    ROCK,
    PAPER,
    SCISSOR
};

int read_choice(void) {
    printf("What is your choice? ('R' for Rock, 'P' for Paper, 'S' for Scissors): ");
    char choice = read_char();
    while (strchr("RrPpSs", choice) == NULL) {
        printf("Invalid choice. Please enter 'R', 'P', or 'S': ");
        choice = read_char();
    }
    if (choice == 'R' || choice == 'r') {
        return ROCK;   // FIXME: remove magic number
    } else if (choice == 'P' || choice == 'p') {
        return PAPER;   // FIXME: remove magic number
    } else {
        return SCISSOR;   // FIXME: remove magic number
    }
}

int main(void) {
    printf("** Rock, Paper, Scissors **\n");
    int user_choice = read_choice();
    if (user_choice == ROCK) printf("You chose Rock.\n");  // FIXME: remove magic number
    else if (user_choice == PAPER) printf("You chose Paper.\n");    // FIXME: remove magic number
    else printf("You chose Scissors.\n");

    int cpu_choice = random_int(ROCK, SCISSOR);  // FIXME: remove magic number
    if (cpu_choice == ROCK) printf("I chose Rock.\n"); // FIXME: remove magic number
    else if (cpu_choice == PAPER) printf("I chose Paper.\n");   // FIXME: remove magic number
    else printf("I chose Scissors.\n");

    if (user_choice == cpu_choice) printf("It's a tie!\n");

    // FIXME: remove magic number below
    else if ((user_choice == ROCK && cpu_choice == SCISSOR) || (user_choice == PAPER && cpu_choice == ROCK) || (user_choice == SCISSOR && cpu_choice == PAPER)) {
        printf("You win!\n");
    } else {
        printf("I win!\n");
    }
}

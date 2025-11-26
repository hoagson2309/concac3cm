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
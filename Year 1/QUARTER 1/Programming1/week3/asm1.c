#include <stdio.h>
#include "functions.h"
#include  <stdlib.h>

int main(){
    printf ("I'm thinking of the number between 1 and 50...\n");
    int x = random_int(1,50);

    int guesses = 5;
    printf("You have %d guesses left to find it! ", guesses);

    printf("Guess the number: ");
    int answer = read_int();

    while (answer != 0 && guesses > 1)
    {
        guesses--;

        if(answer > x){
            printf("Too high, you have %d guesses left to find it!\n", guesses);
        } else{
            printf("Too low, you have %d guesses left to find it!\n", guesses);
        }
        printf("Guess the number: ");
        int answer = read_int();
    }
    if (answer == x){
        printf("Correct! You needed %d guesses.\n", 6 - guesses);
    } 
        else{
        printf("Too low, game over! The number was %d\n", x);
        }
    return 0;
    
}
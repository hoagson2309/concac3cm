#include <stdio.h>     // for printf
#include <stdbool.h>   // for bool
#include "functions.h" // for read_int

int main(void)
{
    printf("Please enter your choice (r = rock, p = paper, s = scissors): ");
    char urchoice = read_char();
    // PLAYER'S CHOICE!!!!!!!!!!!!!!!!!!!!!!:
    if (urchoice == 'r')
    {
        printf("You chose rock.\n");
    }
    else if (urchoice == 'p')
    {
        printf("You chose paper.\n");
    }
    else if (urchoice == 's')
    {
        printf("You chose scissors.\n");
    }
    else
    {
        printf("Invalid choice!\n");
    }

    // BOTCHOICE!!!!!!!!!!!!!!!!!!!!!!!!!!:
    int botchoice = random_int(1, 3);
    switch (botchoice)
    {
    case 1:
        printf("I chose paper.\n");
        break;
    case 2:
        printf("I chose rock.\n");
        break;
    case 3:
        printf("I chose scissors.\n");
        break;
    default:
        break;
    }

    // COMPARISON!!!!!!!!!!!!!!!!!!!!!!!!!:
    if (urchoice == 'r' && botchoice == 3 || urchoice == 'p' && botchoice == 2 || urchoice == 's' && botchoice == 1)
    {
        printf("You win!\n");
    }
    else if (urchoice == 'r' && botchoice == 2 || urchoice == 'p' && botchoice == 1 || urchoice == 's' && botchoice == 3)
    {
        printf("It's draw!\n");
    }
    else
    {
        printf("You lose!");
    }
    return 0;
}
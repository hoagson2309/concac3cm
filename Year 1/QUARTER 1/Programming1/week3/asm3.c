#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

int main()
{
    int score = 0;
    int botscore = 0;
    printf("Rock, paper, scissors!\nPlease enter your choice (r, p, s, q): ");
    char ans = read_char();

    while (ans != 'q')
    {
        // YOUR CHOICE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:
        switch (ans)
        {
        case 'r':
            printf("You chose rock. ");
            break;
        case 'p':
            printf("You chose paper. ");
            break;
        case 's':
            printf("You chose scissors. ");
            break;
        default:
            return 1;
        }

        // BOTCHOICE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:
        int botchoice = random_int(1, 3);
        switch (botchoice)
        {
        case 1:
            printf("I chose rock. ");
            break;
        case 2:
            printf("I chose paper. ");
            break;
        default:
            printf("I chose scissors. ");
            break;
        }

        // COMPARISON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:
        if (ans == 'r' && botchoice == 3 || ans == 'p' && botchoice == 1 || ans == 's' && botchoice == 2)
        {
            printf("You win!\n");
            score++;
            printf("Score: You: %d, me: %d\n", score, botscore);
        }
        else if (ans == 'r' && botchoice == 1 || ans == 'p' && botchoice == 2 || ans == 's' && botchoice == 3)
        {
            printf("It's draw\n\n");
            printf("Score: You: %d, me: %d\n", score, botscore);
        }
        else
        {
            printf("I win!\n");
            botscore++;
            printf("Score: You: %d, me: %d\n", score, botscore);
        }
        printf("Please enter your choice (r, p, s, q): ");
        ans = read_char();
    }
    printf("Choose again!!!\n");
    return 0;
}
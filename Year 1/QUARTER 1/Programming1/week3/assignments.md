# Week XX - Assignments

Name: ??

Group: ETI1V.??

Date: dd/mm/yyyy

**NOTE**: if you'd like to have syntax highlighting in your markdown file, install the "Markdown Preview Github Styling" extension in VS Code.

## First assignment

The first assignment I completed is assignment 1 - Guess the number.
This is the code I wrote:

```c
// TODO: Write your code here
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
```

## Second assignment

The second assignment I completed is assignment 3 - Rock, paper, scissors.
This is the code I wrote:

```c
// TODO: Write your code here
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
```

## Third assignment (optional)

I've actually made three assignments this week! The third assignment I completed is assignment ZZZ.
This is the code I wrote:

```c
// TODO: Write your code here

```

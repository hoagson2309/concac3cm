#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "colours.h"

typedef enum choice_t {
    INCREASE,
    DECREASE,
    QUIT
} choice_t;

/// @brief Reads the user's choice to increase, decrease, or quit.
/// @return The user's choice.
choice_t read_choice(void);

int main(void) {
    // TODO: write a program that lets the user enter a colour in the format #RRGGBB
    //       the user should then be asked to increase or decrease the brightness of the colour,
    //       until the user decides to stop
    //       the program should print the colour after each change
    //       Note that the colour should not go below #000000 or above #FFFFFF!

    // Use the structure <struct colour> and functions from colours.h to work with colours
}


choice_t read_choice(void) {
    printf("Do you want to increase (i) or decrease (d) the brightness (q to quit)? ");
    char choice = read_char();
    while (strchr("iIdDqQ", choice) == NULL) {
        printf("Invalid choice!\nDo you want to increase (i) or decrease (d) the brightness (q to quit)? ");
        choice = read_char();
    }
    if (strchr("iI", choice) != NULL) return INCREASE;
    else if (strchr("dD", choice) != NULL) return DECREASE;
    else return QUIT;
}

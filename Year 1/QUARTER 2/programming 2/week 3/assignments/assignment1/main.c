#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <math.h>
#include <ctype.h>

// TODO: define an enum type colour_t
typedef enum {
    BLACK, 
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    GREY,
    WHITE,
    GOLD,
    SILVER
} colour_t;

// TODO: define a structure type resistor_t
typedef struct{
    colour_t band1;
    colour_t band2;
    colour_t multiplier;
} resistor_t;

const char *color_names[] = {"black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "grey", "white", "gold", "silver"};
// TODO: define & implement functions get_value and read_colour

/// Checks if a colour is valid for the first two bands.
/// @param colour The colour to check.
/// @return True if the colour is valid, false otherwise.
bool is_valid_digit_band(colour_t colour) {
    return colour >= BLACK && colour <= WHITE; // Valid colours for digit bands
}

/// Returns the value of the resistor, or NaN if the given colour is not a valid colour for the first two bands.
/// @return The value of the given colour.
double get_value(const resistor_t *resistor);
double get_value(const resistor_t *resistor){
    if(!is_valid_digit_band(resistor->band1) || !is_valid_digit_band(resistor->band2)){
        return NAN; // return "not a number(NAN) (0.0/0.0)" if invalid
    }

    //compute the base value of the first 2 band 
    int base_value = (resistor->band1 * 10) + resistor->band2; //displays 2 numbers next to each other

    if ( resistor->multiplier == GOLD ){ // gold => x10^-1
        return base_value * 0.1;
    }
    if ( resistor->multiplier == SILVER ){ // silver => x10^-2
        return base_value * 0.01;
    }
    if ( resistor->multiplier >= BLACK && resistor->multiplier <= WHITE ){
        return base_value * pow(10, resistor->multiplier); // x10^n (n depends on each color)
    }
    return NAN;
}

/// Reads a colour from the user. Repeat until the user enters a valid colour.
/// @param prompt The prompt to display to the user. (question)
/// @return The colour entered by the user.
colour_t read_colour(const char *prompt);
colour_t read_colour(const char *prompt){
    char input[20]; // separate buffer to hold user input
    while (true){
        printf("%s", prompt);
        scanf("%19s", input); 
        for(size_t i = 0; i < sizeof(color_names) / sizeof(color_names[0]); i++){
            if (equal_strings_ci(input, color_names[i])){
                return (colour_t)i; //return the matching color
            }
        }
        // if no match, prompt again
        printf("Invalid color. Please try again.\n");
    }
}

int main(void) {
    resistor_t resistor;
    printf("Enter the colors of the resistor: ");
    
    // TODO: ask user to enter three colours, store these in a resistor_t variable
    resistor.band1 = read_colour("Enter the first color band: ");
    resistor.band2 = read_colour("Enter the second color band: ");
    resistor.multiplier = read_colour("Enter the third color band: ");
    
    // TODO: use the function get_value to calculate the value of the
    // TODO: print the value of the resistor 
    double value = get_value(&resistor);
    if(isnan(value)){
        printf("Invalid colours were specified\n");
    } else{
    printf("The value of the resistor is %.2lf ohms\n", value);
    }
    return 0;
}

#ifndef COLOURS_H
#define COLOURS_H

#include <stdbool.h>

struct colour {
    int red;
    int green;
    int blue;
};

/// @brief Reads a colour from the user.
/// @return The colour entered by the user.
struct colour read_colour(void);

/// @brief Checks if a colour is black.
/// @param c The colour to check.
/// @return True if the colour is black, false otherwise.
bool is_black(const struct colour *c);

/// @brief Prints a colour
/// @param c The colour to print.
void print_colour(const struct colour *c);

/// @brief Parses a CSS colour string into its components.
/// @param colour 
/// @param x address of the red component
/// @param y address of the green component
/// @param z address of the blue component
/// @return True if the colour was successfully parsed, false otherwise.
bool parse_css_colour(const char *colour, int *x, int *y, int *z);

#endif // COLOURS_H
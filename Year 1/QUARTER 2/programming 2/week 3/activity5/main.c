#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

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

int main(void) {
    const int max_count = 10;

    struct colour colours[max_count]; //initialize an array to store color

    printf("Enter at most %d colours (#rrggbb in hex), #000000 to stop\n", max_count);

    int count = 0;
    while (count < max_count) {
        struct colour c = read_colour();
        if (is_black(&c)) break;
        colours[count] = c;
        count++;
    }

    // TODO: print all colours that were entered using print_colour
    //       you'll need to store them in an array
    printf("You've entered the following %d colours:\n", count);
    for(int i = 0; i < count; i++){
        print_colour(&colours[i]); //print each stored color
    }
    return 0;
}

int hex_to_int(char c) {
    if (isdigit(c)) return c - '0';
    return tolower(c) - 'a' + 10;
}

int hex_to_byte(const char *hex) {
    return hex_to_int(hex[0]) * 16 + hex_to_int(hex[1]);
}

bool parse_css_colour(const char *colour, int *x, int *y, int *z) {
    if (colour[0] != '#') return false;
    if (strlen(colour + 1) != 6) return false; // tuong duong colour[1] vi la pointer
    for (int i = 1; i < 7; i++) if (!isxdigit(colour[i])) return false;
    *x = hex_to_byte(colour + 1); // tuong duong colour[1] vi la pointer
    *y = hex_to_byte(colour + 3); // tuong duong colour[3] vi la pointer
    *z = hex_to_byte(colour + 5); // tuong duong colour[5] vi la pointer
    return true;
}

struct colour read_colour(void) {
    char colour[9];
    struct colour result = {0, 0, 0};
    printf("Enter a valid colour (e.g., #ff00ff): ");
    read_string(colour, sizeof(colour));
    if (!parse_css_colour(colour, &result.red, &result.green, &result.blue)) {
        printf("Invalid input!\nEnter a valid colour (e.g., #ff00ff): ");
        read_string(colour, sizeof(colour));
    }
    return result;
}

bool is_black(const struct colour *c) {
    return c->red == 0 && c->green == 0 && c->blue == 0;
}

void print_colour(const struct colour *c) {
    printf("Colour: #%02x%02x%02x (red: %.1f%%, green: %.1f%%, blue: %.1f%%)\n", c->red, c->green, c->blue, c->red / 2.55f, c->green / 2.55f, c->blue / 2.55f);
}

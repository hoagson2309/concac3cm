#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "colours.h"
#include "functions.h"

int hex_to_int(char c) {
    if (isdigit(c)) return c - '0';
    return tolower(c) - 'a' + 10;
}

int hex_to_byte(const char *hex) {
    return hex_to_int(hex[0]) * 16 + hex_to_int(hex[1]);
}

bool parse_css_colour(const char *colour, int *x, int *y, int *z) {
    if (colour[0] != '#') return false;
    if (strlen(colour + 1) != 6) return false;
    for (int i = 1; i < 7; i++) if (!isxdigit(colour[i])) return false;
    *x = hex_to_byte(colour + 1);
    *y = hex_to_byte(colour + 3);
    *z = hex_to_byte(colour + 5);
    return true;
}

struct colour read_colour(void) {
    printf("Enter a colour in the format ##RRGGBB: ");
    char colour[9];
    struct colour result = {0, 0, 0};
    read_string(colour, sizeof(colour));
    if (!parse_css_colour(colour, &result.red, &result.green, &result.blue)) {
        printf("Invalid input!\nEnter a colour in the format ##RRGGBB: ");
        read_string(colour, sizeof(colour));
    }
    return result;
}

bool is_black(const struct colour *c) {
    return c->red == 0 && c->green == 0 && c->blue == 0;
}

void print_colour(const struct colour *c) {
    printf("#%02x%02x%02x (red: %.1f%%, green: %.1f%%, blue: %.1f%%)\n", c->red, c->green, c->blue, c->red / 2.55f, c->green / 2.55f, c->blue / 2.55f);
}

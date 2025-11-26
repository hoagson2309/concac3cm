#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

/// @brief A structure representing a coordinate in 2D space.
typedef struct {
    int x;
    int y;
} coordinate_t;

/// Checks if the string contains a valid coordinate in the form (x, y).
/// @param string The string to check.
/// @param coordinate The coordinate to store the values in.
/// @return `true` if the string contains a valid coordinate without trailing characters, `false` otherwise.
bool read_coordinate(const char *string, coordinate_t *coordinate){
    char extra;
    int matched = sscanf(string, "(%d, %d)%c", &coordinate->x, &coordinate->y, &extra); //& to pass the address of x and y in coordinate. Using &coordinate->x gives sscanf the precise memory location to store the parsed x value.

    //make sure there's no extra trailing character, the only valid input is (x, y)
    return matched == 2;
}

/// Calculates the distance between two coordinates.
/// @param first The first coordinate.
/// @param second The second coordinate.
/// @return The distance between the two coordinates.
double distance(coordinate_t first, coordinate_t second);

int main(void) {
    // TODO:
    char input[300];
    coordinate_t previous, current;
    bool has_previous = false;

    //   - read a line from the standard input
    printf("Please enter a coordinate: ");

    while(fgets(input, sizeof(input), stdin) != NULL){
        char *ptr = strchr(input, '\n');
        if(ptr != NULL){
            *ptr = '\0';
        }

    //   - check if the line contains a valid coordinate
    if(read_coordinate(input, &current)){
        if(has_previous){
            //   - if it does, compute the distance between this coordinate and the previous one (if there is a previous one)
            double dist = distance(previous, current);
            printf("The distance between (%d, %d) and (%d, %d) is %.6f.\n", previous.x, previous.y, current.x, current.y, dist);
        }
        previous = current;
        has_previous = true;
    } else {
        printf("Invalid input, please try again.\n");
    }

    printf("Please enter a coordinate: ");
    }
    printf("Bye!\n");
    return 0;
}

double distance(coordinate_t first, coordinate_t second) {
    return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

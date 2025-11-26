#include <stdio.h>
#include <math.h>
#include "functions.h"

struct coordinate {
    float x;
    float y;
};

/// @brief Computes the distance between two coordinates.
/// @param a Address of the first coordinate.
/// @param b Address of the second coordinate.
/// @return The (Euclidean) distance between the two coordinates.
float distance(const struct coordinate *a, const struct coordinate *b);

/// @brief Reads a coordinate   from the user and returns it.
/// @return The coordinate entered by the user.
struct coordinate read_coordinate(void);    

int main(void) {
    printf("Enter the first coordinate:\n");
    struct coordinate a = read_coordinate();

    printf("Enter the second coordinate:\n");
    struct coordinate b = read_coordinate();

    float dist = distance(&a, &b);

    printf("The distance between (%.2f, %.2f) and (%.2f, %.2f) is %.2f.\n", a.x, a.y, b.x, b.y, dist);
}

float distance(const struct coordinate *a, const struct coordinate *b) {
    // TODO: implement this function
    float distance = sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
    return distance;
}

struct coordinate read_coordinate(void) {
    printf(" x-coordinate: ");
    float x = read_float();
    printf(" y-coordinate: ");
    float y = read_float();

    struct coordinate result = {x, y};
    return result;
}

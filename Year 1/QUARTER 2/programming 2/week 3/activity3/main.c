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

int main(void) {
    printf("Enter the first coordinate:\n");
    printf(" x-coordinate: ");
    float x1 = read_float();
    printf(" y-coordinate: ");
    float y1 = read_float();

    printf("Enter the second coordinate:\n");
    printf(" x-coordinate: ");
    float x2 = read_float();
    printf(" y-coordinate: ");
    float y2 = read_float();

    struct coordinate a = {x1, y1};
    struct coordinate b = {x2, y2};

    float dist = distance(&a, &b);

    printf("The distance between (%.2f, %.2f) and (%.2f, %.2f) is %.2f.\n", x1, y1, x2, y2, dist);
}

float distance(const struct coordinate *a, const struct coordinate *b) {
    // TODO: implement this function
    float distance = sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
    return distance;
}


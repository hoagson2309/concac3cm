#include <stdio.h>
#include <stdlib.h> // for qsort
#include "functions.h"

/// @brief A typedef for the comparison function used in qsort.
typedef int compare_function(const void *, const void *);

/// @brief Prints an array of floats, comma-separated and on a single line.
/// @param array Pointer to the array of floats.
/// @param size The size of the array.
void print_floats(float *array, size_t size);

/// @brief Comparison function for qsort to sort floats in ascending order.
/// @param a Pointer to the first element.
/// @param b Pointer to the second element.
/// @return A negative value if a < b, positive value if a > b, 0 if a == b.
int compare_floats(const void *a, const void *b);

int main(void) {
    printf("How many numbers to generate? " );
    int howmany = read_int();
    while (howmany < 1) {
        printf("Invalid input. Please enter a positive number: ");
        howmany = read_int();
    }

    // allocate memory for the numbers
    float *numbers = (float*) malloc(howmany * sizeof(float));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // generate random numbers
    for (int i = 0; i < howmany; i++) numbers[i] = random_float(0.0f, 100.0f);

    // TODO: sort the numbers using qsort
    qsort(numbers, howmany, sizeof(float), (compare_function *)compare_floats);

    // print the sorted numbers
    print_floats(numbers, howmany);

    free(numbers);  // deallocate
}

void print_floats(float *array, size_t size) {
    if (size > 0) printf("%.2f", array[0]);
    for (size_t i = 1; i < size; i++) {
        printf(", %.2f", array[i]);
    }
    printf("\n");
}

int compare_floats(const void *a, const void *b){
    //cast void pointers to float pointers 
    const float *fa = (const float *)a;
    const float *fb = (const float *)b;

    //return comparison result
    if(*fa < *fb){
        return -1;
    } else if(*fa > *fb){
        return 1;
    } else{
        return 0;
    }
}

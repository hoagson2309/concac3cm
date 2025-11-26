#include <stdio.h>
#include "functions.h"

/// @brief Fill an array with random floating point numbers between -10 and 10.
/// @param array The array to fill.
/// @param size The size of the array.
void fill_array(float array[], int size){
    float a = size;
    for(int i=0; i<size; i++){
        array[i] = random_float(-a,a);
    }
}

/// @brief Print an array of floating point numbers, comma-separated.
/// @param array The array to print.
/// @param size The size of the array.
void print_array(const float array[], int size){
    bool printed_first = false;
    for(int i=0; i<size; i++){
        if(printed_first) printf(", ");
        printed_first = true;
        printf("%.2f", array[i]);
    }
    printf(".\n");
}

/// @brief Compute the mean of an array of floating point numbers.
/// @param array The array to compute the mean of.
/// @param size The size of the array.
/// @return The mean of the array.
float mean(const float array[], int size){
    float total = 0;
    for(int i=0; i<size; i++){
        total += array[i];
    }
    float mean = total / size;
    return mean;
}

/// @brief Remove the mean from an array of floating point numbers.
/// @param array The array to remove the mean from.
/// @param size The size of the array.
/// @param mean The mean to remove.
void remove_mean(float array[], int size, float mean){
    for(int i=0; i<size; i++){
        array[i] -= mean;
    }
}

int main(void) {
    float array[10];
    int size = sizeof(array) / sizeof(array[0]);
    float Mean = 0.00f;

    fill_array(array, size);
    Mean = mean(array, size);

    printf("Before: ");
    print_array(array, size);

    printf("Mean: ");
    printf("%.2f", Mean);

    remove_mean(array, size, Mean);

    printf("\nAfter: ");
    print_array(array, size);
    
    return 0;
}
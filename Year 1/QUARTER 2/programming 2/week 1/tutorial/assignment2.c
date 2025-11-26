#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

/// @brief Prints the array to the console, values comma-separated and on a single line
/// @param array The array to print.
/// @param length The length of the array.
void print_array(const int array[], size_t length);
void print_array(const int array[], size_t length){
    bool first = false;
    for(size_t i = 0; i < length; i++){
        if(first)  printf(", ");
        first = true;
        printf("%d", array[i]);
    }
}

/// @brief Swaps the values of the two integers pointed to by `a` and `b`.
/// @param a The memory address of the first integer.
/// @param b The memory address of the second integer.
void swap(int * a, int * b);
void swap(int * a, int * b){
    int temp = *a;
        *a = *b;
        *b = temp;
}

/// @brief Returns the address of the smallest number in the array.
/// @param array The array to search.
/// @param length The length of the array.
/// @return The address of the smallest number in the array, or NULL if the array is empty.
int* min_ptr(int array[], size_t length);
int* min_ptr(int array[], size_t length){
    int min = 0;
    for(int i = 1; i < length; i++){
        if(array[i] < array[min]){
            min = i;
        }
    }
    return &array[min];
}

/// @brief Returns the address of the largest number in the array.
/// @param array The array to search.
/// @param length The length of the array.
/// @return The address of the largest number in the array, or NULL if the array is empty.
int* max_ptr(int array[], size_t length);
int* max_ptr(int array[], size_t length){
      int max = 0;
    for(int i = 1; i < length; i++){
        if(array[i] > array[max]){
            max = i;
        }
    }
    return &array[max];
}

int main(){
    int array[10];
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("The array is: ");
    for(int i = 0; i < size; i++){
        array[i] = random_int(0, 100);
        }
    print_array(array, size);
    printf(".\n");

    int *min = min_ptr(array, size);
    int *max = max_ptr(array, size);
    printf("The smallest number is %d, and the largest number is %d.\n", *min, *max);

    swap(min, max);
    printf("After swapping, the array is: ");
    print_array(array, size);
    printf(".\n");

    return 0;
}



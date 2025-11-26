#include <stdio.h>
#include <string.h>
#include "utils.h"

/// @brief Reverse an array.
/// @param array The array to reverse.
/// @param count The number of elements in the array.
/// @param size The size of each element in bytes. 
void reverse(void *array, size_t count, size_t size);

int main(void) {
    int integers[10];
    float floats[12];
    char characters[20];

    fill_random(integers, sizeof(integers) / sizeof(integers[0]), sizeof(int), 0, 255);
    fill_random(floats, sizeof(floats) / sizeof(floats[0]), sizeof(float), 0, 255);
    fill_random(characters, sizeof(characters) / sizeof(characters[0]), sizeof(char), 'a', 'z');

    printf("Original arrays:\n");
    print_ints(integers, sizeof(integers) / sizeof(integers[0]));
    print_floats(floats, sizeof(floats) / sizeof(floats[0]));
    print_chars(characters, sizeof(characters) / sizeof(characters[0]));

    reverse(integers, sizeof(integers) / sizeof(integers[0]), sizeof(int));
    reverse(floats, sizeof(floats) / sizeof(floats[0]), sizeof(float));
    reverse(characters, sizeof(characters) / sizeof(characters[0]), sizeof(char));

    printf("\n\nAfter reversing:\n");
    print_ints(integers, sizeof(integers) / sizeof(integers[0]));
    print_floats(floats, sizeof(floats) / sizeof(floats[0]));
    print_chars(characters, sizeof(characters) / sizeof(characters[0]));
}


void reverse(void *array, size_t count, size_t size) {
    // TODO: implement this function!
    char *array_ptr = (char *)array;
    for(size_t i = 0; i < count / 2; i++){
        char *front = array_ptr + i * size;
        char *back = array_ptr + (count - 1 - i) * size;

        //ex: array_ptr + 20 (points to 6): Since array_ptr is cast as char *, adding 20 moves the pointer 20 bytes forward.
        //This reaches address 0x1014, where the last integer (6) is stored in memory.

        //swap element front and back
        for(size_t j = 0; j < size; j++){
            char temp = front[j]; //You want to store the value at front[j], not its address. so it cannot be char *temp = &front[j] cuz front[j] is a value at j element at this point
            front[j] = back[j];
            back[j] = temp;
        }
    }
}
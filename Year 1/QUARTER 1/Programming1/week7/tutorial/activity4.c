#include <stdio.h>
#include "functions.h"
#include "week7.h"

/// @brief Removes an element from an array by index.
/// @param values the array of values
/// @param size the number of elements in the array
/// @param index the index of the element to remove
/// @return the number of elements remaining in the array
int remove_by_index(int values[], size_t size, size_t index){
    for(size_t i = index; i < size - 1; i++){
        values[i] = values[i + 1];
    }
    size--;

}

int main(void) {
    int numbers[] = {2, 3, 5, 7, 11, 13, 17, 19};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    while (size > 0) {
        print_int_array(numbers, size);
        printf("Enter the index of the element to remove: ");
        size = remove_by_index(numbers, size, read_valid_index(size));
    }
    printf("All elements have been removed.\n");
}

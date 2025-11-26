#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/// @brief Reads the next integer from a file, skipping non-numbers
/// @param file The file to read from.
/// @return true if an integer was read, false if the end of the file was reached.
bool read_int(FILE *file, int *value);

/// @brief Shuffles an array of integers.
/// @param numbers The array of integers to shuffle.
/// @param size The number of elements in the array.
void shuffle(int *numbers, size_t size);

int main(void) {
    int *numbers = NULL;
    size_t capacity = 0, size = 0;

    int number;
    while (read_int(stdin, &number)) {  //continue reading until eof
        if (number == 0) {
            break;  
        }

        if (size >= capacity) {
            size_t newcap = capacity * 2 + 1;
            int *ptr = (int *) realloc(numbers, newcap * sizeof(int));
            if (ptr == NULL) {
                free(numbers);
                return 1;
            }
            numbers = ptr;
            capacity = newcap;
        }

        numbers[size++] = number;
    }

    shuffle(numbers, size);
    for (size_t i = 0; i < size; i++) {
        printf("%d\n", numbers[i]);  
    }

    free(numbers);
    return 0;
}

bool read_int(FILE *file, int *value) {
    char buffer[100];
    int result = fscanf(file, "%99s", buffer);
    while (result != EOF && sscanf(buffer, "%d", value) == 0) {
        result = fscanf(file, "%99s", buffer);
    }
    return result != EOF;
}

void shuffle(int *numbers, size_t size) {
    srand(time(NULL));  
    for (size_t i = 0; i < size; i++) {
        size_t j = rand() % size;
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(void) {
    int *ptr = (int*) malloc(sizeof(int));  // allocate memory to store one integer

    if(ptr == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }

    int capacity = 1; // current capacity of an array
    int count = 0;  // number of integers stored in memory
    
    printf("Enter an integer (0 to stop): ");
    int input = read_int();
    
    while (input != 0) {
        if  (count == capacity){
            capacity *= 2; //double the capacity of interger
            int *update = (int*) realloc(ptr, capacity * sizeof(int));
            if(update == NULL){
                printf("Reallocation failed");
                free(ptr); //free the og memory
                return 1;
            }
            ptr = update; // update the pointer 
        }
        ptr[count] = input;     // store the integer
        count++;                // increment the number of integers stored

        printf("Enter an integer (0 to stop): ");
        input = read_int();
    }

    printf("You've entered %d integers:\n", count);
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            printf(", ");  // print a comma and a space before all but the first integer
        }
        printf("%d", ptr[i]);  // print the integers
    }
    printf("\n");
    free(ptr);
    return 0;
}

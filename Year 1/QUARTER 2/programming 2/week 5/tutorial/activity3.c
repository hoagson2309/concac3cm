#include <stdio.h>
#include "functions.h"

int main(void) {
    const char *filename = "../numbers.txt";
    int sum = 0;

    printf("Reading numbers from %s...\n", filename);

    // TODO: open the file numbers.txt for reading
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Failed to open file\n");
        return 1;
    }
    //       sum all the numbers in the file
    int number;
    while(fscanf(file, "%d", &number) == 1){
        sum += number;
    }
    // TODO: close the file
    fclose(file);

    printf("The sum of the numbers is %d.\n", sum);
    return 0;
}


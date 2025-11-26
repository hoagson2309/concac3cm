#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(void) {
    // FIXME: change this program so that it does not use *ANY* arrays, only pointers
    int capacity = 100;
    char *name = (char*) malloc(capacity * sizeof(char));
    if(name == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Hi, what's your name? ");

    read_string(name, capacity);

    printf("Hello, %s!\n", name);
    
    free(name);
    return 0;
}

#include <stdio.h>
#include "functions.h"
#include "tutorial.h"
#include <ctype.h>

void to_uppercase(char string[]){
    int i = 0;
    while(string[i] != '\0'){
        string[i] = toupper(string[i]);
        i++;
    }
}

int main(void) {
    char name [30];
    printf("Please enter your name: ");
    read_string(name, 30);
    to_uppercase(name);

    printf("Hello, %s!\n", name);
    return 0;
}

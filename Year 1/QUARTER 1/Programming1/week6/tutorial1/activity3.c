#include <stdio.h>
#include "functions.h"
#include "tutorial.h"

void print_string(const char string[]){
    int i = 0;
    while(string[i] != '\0'){
        printf("%c\n", string[i]);
        i++;
    }
}

int main(void) {
    print_string("Hello, world!\nHow are you today?");
    return 0;
}

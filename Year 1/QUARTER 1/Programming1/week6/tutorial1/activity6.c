#include <stdio.h>
#include "functions.h"
#include "tutorial.h"
#include <ctype.h>
size_t string_length(const char string[]){
    size_t length = 0;
    while(string[length] != '\0'){
        length++;
    }
    return length;
}

int main(void) {
    printf("The length of the string 'Hello, world!' is %zu (should be 13)\n", string_length("Hello, world!"));
    printf("The length of the string 'The quick brown fox jumps over the lazy dog' is %zu (should be 43)\n", string_length("The quick brown fox jumps over the lazy dog"));
    printf("The length of the empty string \"\" is %zu (should be 0)\n", string_length(""));
    return 0;
}

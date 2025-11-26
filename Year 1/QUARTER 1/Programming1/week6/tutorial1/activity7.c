#include <stdio.h>
#include "functions.h"
#include "tutorial.h"
#include <ctype.h>

void print_string_reverse(const char string[]){
    int length = string_length(string);

    for(int i = length; i >= 0; i--){
        printf("%c", string[i]);
    }
}

int main(void) {
    print_string_reverse("\nHello, world!");  // should print "!dlrow ,olleH\n"
    print_string_reverse("\n");            // should print a newline (empty string)
    print_string_reverse("\n12345");            // should print "54321\n"
    return 0;
}

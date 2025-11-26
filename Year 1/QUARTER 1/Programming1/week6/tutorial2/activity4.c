#include <stdio.h>      // for printf
#include "functions.h"  // for copy_string
#include "tutorial.h"

int main(void) {
    char string[200];

    printf("Enter a strings and I'll tell you if it's a palindrome: ");
    read_string(string, sizeof(string) / sizeof(string[0]));

    if (is_palindrome(string)) {
        printf("That's a palindrome!\n");
    }
    else {
        printf("Nope, not a palindrome.\n");
    }
    return 0;
}

#include <stdio.h>      // for printf
#include "functions.h"  // for copy_string
#include "tutorial.h"

int main(void) {
    char string[200];
    printf("Enter a string to reverse: ");
    read_string(string, sizeof(string) / sizeof(string[0]));

    reverse_string(string);

    printf("Reversed: \"%s\"\n", string);
    
    return 0;
}

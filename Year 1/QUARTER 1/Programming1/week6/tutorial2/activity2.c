#include <stdio.h>      // for printf
#include "functions.h"  // for copy_string
#include "tutorial.h"

int main(void) {
    char destination[200] = "";

    concatenate_strings(destination, "Hello");
    printf("Destination: %s\n", destination);   // should print "Hello\n"

    concatenate_strings(destination, ", ");
    printf("Destination: %s\n", destination);   // should print "Hello, \n"

    concatenate_strings(destination, "\nHow are you?");
    printf("Destination: %s\n", destination);   // should print "Hello, \nHow are you?\n"

    concatenate_strings(destination, "\nThe quick brown foxes jump over a lazy dog");
    printf("Destination: %s\n", destination);

    return 0;
}

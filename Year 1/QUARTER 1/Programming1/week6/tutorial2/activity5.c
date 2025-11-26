#include <stdio.h>  // for printf
#include "functions.h"

int main(void) {
    char string1[200];
    char string2[200];
    char string3[200];
    char string4[200];
    char string5[200];

    printf("Enter 5 sentences:\n");
    read_string(string1, 200);
    read_string(string2, 200);
    read_string(string3, 200);
    read_string(string4, 200);
    read_string(string5, 200);

    printf("You entered the following 5 sentences: %s\n%s\n%s\n%s\n%s\n", string1, string2, string3, string4, string5);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <ctype.h>
#include <stdbool.h>

int main(void) {
    char string[10];
    printf("What's your name?\n");
    read_string(string, sizeof(string));
    printf("Hello, %s!", string);
    return 0;
}

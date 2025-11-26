#include <stdio.h>     
#include "functions.h"
int main(void) {
    printf("You entered the number %d\n", read_number(1, 10));
    printf("You entered the number %d\n", read_number(10, 20));
    printf("You entered the number %d\n", read_number(-42, 42));
    return 0;
}
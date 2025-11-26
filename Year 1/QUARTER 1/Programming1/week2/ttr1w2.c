#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    printf("Enter your age: ");
    int age = read_int();

    if (age = 0) {
        printf("You are a baby\n");
    } else if (age < 18) {
        printf("You are a minor\n");
    } else if (age < 65) {
        printf("You are an adult\n");
    } else if (age = 100) {
        printf("You are a centenarian!\n");
    } else {
        printf("You are a senior citizen\n");
    }

    return 0;
}
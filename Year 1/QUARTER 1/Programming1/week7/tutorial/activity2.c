#include <stdio.h>
#include "functions.h"
#include "week7.h"

int main(void) {
    int numbers[] = {2, 3, 5, 7, 11, 13, 17, 19};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    
    bool contains5 = contains_int(numbers, size, 5);
    bool contains17 = contains_int(numbers, size, 17);
    bool contains42 = contains_int(numbers, size, 42);

    printf("The array contains 5: %s ", contains5 ? "true " : "false ");
    printf(contains5 ? "correct\n" : "incorrect!\n");

    printf("The array contains 17: %s ", contains17 ? "true " : "false ");
    printf(contains17 ? "correct\n" : "incorrect!\n");

    printf("The array contains 42: %s ", contains42 ? "true " : "false ");
    printf(contains42 ? "correct\n" : "incorrect!\n");
}

#include <stdio.h>      // for printf
#include "functions.h"  // for read_int

int main(void) {
    bool print_first = false;
    int number [100];
    int count = 0;
    printf ("Enter a number: ");
    int num = read_int();
    while (num > 0) {
        number[count] = num;
        count ++;
        printf ("Enter a number: ");
        num = read_int();
    }
    printf ("You entered the following values: ");
    for (int i = 0; i < count; i++) {
        if (print_first) {
            printf (", ");
        }
        print_first = true;
        printf("%d", number[i]);
    }
    printf (".\n");
    return 0;
}

#include <stdio.h>
#include "functions.h"

#ifndef NUM_NUMBERS
    #error NUM_NUMBERS is not defined! use -DNUM_NUMBERS=n to define it at compile time
#endif

#define REPEAT(i, x, n) for (int i = 0; i < n; i++) { x; }

int main(void) {
    printf("Enter %d (integer) numbers: ", NUM_NUMBERS);
    int numbers[NUM_NUMBERS];
    REPEAT(i, numbers[i] = read_int(), NUM_NUMBERS)
    printf("The numbers you've entered are: ");
    if (NUM_NUMBERS > 0) {
        printf("%d", numbers[0]);
        REPEAT(i, printf(", %d", numbers[i + 1]), NUM_NUMBERS - 1)
    }
    return 0;
}

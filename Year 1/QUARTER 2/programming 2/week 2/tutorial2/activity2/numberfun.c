#include "numberfun.h"
#include <stdio.h>

bool is_perfect_number(int number) {
    int sum = 0;
    for (int i = 1; i < number; i++) {
        if (number % i == 0) {
            sum += i;
        }
    }
    return sum == number;
}

void print_factor_sum(int number) {
    printf("1");
    int sum = 1;
    for (int i = 2; i < number; i++) {
        if (number % i == 0) {
            printf(" + %d", i);
            sum += i;
        }
    }
    printf(" = %d\n", sum);
}

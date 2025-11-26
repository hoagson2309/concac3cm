#include <stdio.h>
#include "functions.h"
#include "numberfun.h"

int main(void) {
    printf("Enter a number and I'll try to find all perfect numbers below that number: ");
    int number = read_int();
    int candidate = 1;
    while (candidate < number) {
        if (is_perfect_number(candidate)) {
            printf("%d is a perfect number: ", candidate);
            print_factor_sum(candidate);
        }
        candidate++;
    }
}

#include <stdio.h>
#include "functions.h"

#define LINE_LENGTH 120

bool is_prime(size_t n) {
    if (n < 2) return false;
    for (size_t i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int num_digits(size_t n) {
    int count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

int main(void) {
    printf("How many prime numbers would you like to print? ");
    int count = read_int();

    int length = 0;
    size_t i = 2;
    int found = 0;
    while (found < count) {
        if (is_prime(i)) {
            found++;
            if (length > 0) {
                printf(", ");
                length += 2;
            }
            printf("%zu", i);
            length += num_digits(i);
            if (length > LINE_LENGTH) {
                printf("\n");
                length = 0;
            }
        }
        i++;
    }
}

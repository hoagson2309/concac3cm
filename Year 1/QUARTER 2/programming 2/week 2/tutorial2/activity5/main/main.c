#include <stdio.h>
#include "functions.h"
#include "numberfun.h"

#define LINE_LENGTH 80

void print_prime_numbers(int count);
void print_fibonacci_numbers(int count);

int main(void) {
    printf("What would you like to do?\n" \
        "1. Print prime numbers\n" \
        "2. Print Fibonacci numbers\n");

    int choice = read_int();
    while (choice < 1 || choice > 2) {
        printf("Invalid choice. Please enter 1 or 2: ");
        choice = read_int();
    }

    if (choice == 1) {
        printf("How many prime numbers would you like to print? ");
        int count = read_int();
        print_prime_numbers(count);
    } else {
        printf("How many Fibonacci numbers would you like to print? ");
        int count = read_int();
        print_fibonacci_numbers(count);
    }
}

void print_prime_numbers(int count) {
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

void print_fibonacci_numbers(int count) {
    int time_parts[3];
    printf("Printing the first %d Fibonacci numbers:\n", count);
    for (size_t i = 1; i <= (size_t) count; i++) {
        get_current_time(time_parts);
        int seconds = time_parts[2] + 60 * time_parts[1] + 3600 * time_parts[0];
        printf("F(%zu) = %zu", i, fibonacci(i));
        get_current_time(time_parts);
        int new_seconds = time_parts[2] + 60 * time_parts[1] + 3600 * time_parts[0];
        if (new_seconds - seconds > 1) printf(" (time: %d seconds)\n", new_seconds - seconds);
        else printf("\n");
    }
}
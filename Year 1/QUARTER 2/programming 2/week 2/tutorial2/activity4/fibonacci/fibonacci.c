#include <stdio.h>
#include "functions.h"

#define MAX 60

size_t fibonacci(size_t n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main(void) {
    int time_parts[3];
    printf("Printing the first %d Fibonacci numbers:\n", MAX);
    for (size_t i = 1; i <= MAX; i++) {
        get_current_time(time_parts);
        int seconds = time_parts[2] + 60 * time_parts[1] + 3600 * time_parts[0];
        printf("F(%zu) = %zu", i, fibonacci(i));
        get_current_time(time_parts);
        int new_seconds = time_parts[2] + 60 * time_parts[1] + 3600 * time_parts[0];
        if (new_seconds - seconds > 1) printf(" (time: %d seconds)\n", new_seconds - seconds);
        else printf("\n");
    }
}

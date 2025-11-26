#include "numberfun.h"

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

size_t fibonacci(size_t n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

size_t fibonacci_iter(size_t n) {
    size_t a = 0;
    size_t b = 1;
    for (size_t i = 0; i < n; i++) {
        size_t temp = a;
        a = b;
        b = temp + b;
    }
    return a;
}

#ifndef NUMBERFUN_H
#define NUMBERFUN_H

#include <stdbool.h> // for bool
#include <stddef.h> // for size_t

/// @brief Returns true if n is a prime number, false otherwise.
/// @param n 
/// @return 
bool is_prime(size_t n);

/// @brief Returns the number of digits in n.
/// @param n
/// @return
int num_digits(size_t n);

/// @brief Returns the nth Fibonacci number, using recursion (slow!).
/// @param n
/// @return
size_t fibonacci(size_t n);

/// @brief Returns the nth Fibonacci number, using iteration (fast).
/// @param n
/// @return
size_t fibonacci_iter(size_t n);

#endif // NUMBERFUN_H

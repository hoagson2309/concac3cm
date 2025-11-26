#ifndef NUMBERFUN_H
#define NUMBERFUN_H

#include <stdbool.h>

/// @brief Prints the sum of the factors of a number
///        in the form a + b + c + ... = sum
/// @param number 
void print_factor_sum(int number);

/// @brief Determines if a number is a perfect number
/// @param number
/// @return true if the number is a perfect number, false otherwise
bool is_perfect_number(int number);

#endif // NUMBERFUN_H
#include "IntVector.h"

#include <iostream>

int main()
{
    exam::IntVector v{};
    v.push_back(0);
    v.push_back(1);
    for (auto i{2}; i < 10; ++i)
    {
        v.push_back(v[i - 1] + v[i - 2]);
    }

    std::cout << "Fibonacci sequence: ";
    for (auto i : v)
    {
        std::cout << i << ' ';
    }

    // add same numbers again
    for (auto i{0}; i < 10; ++i)
    {
        v.push_back(v[i]);
    }

    std::cout << "\nFibonacci sequence (twice): ";
    for (auto i : v)
    {
        std::cout << i << ' ';
    }

    v.sort();
    std::cout << "\nFibonacci sequence (twice, but sorted): ";
    for (auto i : v)
    {
        std::cout << i << ' ';
    }

    v.unique();
    std::cout << "\nFibonacci sequence (almost, no dups): ";
    for (auto i : v)
    {
        std::cout << i << ' ';
    }

    return EXIT_SUCCESS;
}
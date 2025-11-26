#include <iostream>
#include <memory>
#include <string>

#include "libptr/unique_ptr.hpp"

template <typename T>
void use_unique(std::unique_ptr<T> const& ptr)
{
    std::cout << "Inside use_unique with const& parameter, no ownership transfer!\n";
    if (ptr) {
        std::cout << "Using UniquePtr managing object at address: "
                  << static_cast<void*>(ptr.get()) << "\n";
        std::cout << "Value: " << *ptr << "\n";
    } else {
        std::cout << "unique_ptr is null.\n";
    }
}

template <typename T>
void use_unique(std::unique_ptr<T>&& ptr)
{
    std::unique_ptr<T> local_ptr = std::move(ptr); // take ownership

    std::cout << "Inside use_unique with rvalue reference parameter, ownership transferred!\n";
    if (local_ptr) {
        std::cout << "Using UniquePtr managing object at address: "
                  << static_cast<void*>(local_ptr.get()) << "\n";
        std::cout << "Value: " << *local_ptr << "\n";
    } else {
        std::cout << "UniquePtr is null.\n";
    }
}

int main()
{
    std::cout << "\nYour implementation of UniquePtr is in the libptr/include/libptr/unique_ptr.hpp file.\n";
    std::cout << "Run the tests in the tests/ folder to verify your implementation.\n";
    std::cout << "The test target is called tests_unique.\n";
    std::cout << "The tests are defined in the tests/test_unique.cpp file. But they won't compile until you have implemented UniquePtr.\n";
    std::cout << "\nYou can use this main function (located in: " __FILE__ ") to do some ad-hoc testing if you want.\n";
    std::cout << "For now, it just demonstrates the std::unique_ptr usage as a reference implementation.\n\n";

    {
        std::unique_ptr<std::string> ptr1{ new std::string{"Hello, World!"} };
        std::cout << "ptr1 points to: " << *ptr1 << "\n";

        auto ptr2 = std::move(ptr1);
        std::cout << "After moving, ptr2 points to: " << *ptr2 << "\n";
        if (ptr1 == nullptr) {
            std::cout << "ptr1 is now null after being moved from.\n";
        }

        use_unique(ptr2); // by reference, no ownership transfer
        if (ptr2 != nullptr) {
            std::cout << "ptr2 is still usable, there was no move (ownership transfer).\n";
        }

        use_unique(std::move(ptr2)); // by rvalue ref, ownership transferred
        if (ptr2 == nullptr) {
            std::cout << "ptr2 is now null after being moved from.\n";
        }
    }
    return 0;
}

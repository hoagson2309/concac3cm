#include "cppf_string.h"
#include <iostream>

int main() {
    // Test default constructor
    cppf::String str0{};
    std::cout << "str0: " << str0.c_str() << " (size: " << str0.size() << ")\n";

    // Test constructor from string literal
    cppf::String str1{"Alice"};
    std::cout << "str1: " << str1.c_str() << " (size: " << str1.size() << ")\n";

    // Test constructor from std::string
    cppf::String str2 = std::string{"Bob"};
    std::cout << "str2: " << str2.c_str() << " (size: " << str2.size() << ")\n";

    // Test copy constructor
    cppf::String str3{str2};
    std::cout << "str3: " << str3.c_str() << " (size: " << str3.size() << ")\n";

    // Test copy assignment operator
    str0 = str1;
    std::cout << "str0 after assignment: " << str0.c_str() << " (size: " << str0.size() << ")\n";

    // Test append
    str0.append(" and Bob");
    std::cout << "str0 after append: " << str0.c_str() << " (size: " << str0.size() << ")\n";

    // Test clear
    str0.clear();
    std::cout << "str0 after clear: " << str0.c_str() << " (size: " << str0.size() << ")\n";

    // Test at and operator[]
    cppf::String str4{"Hello"};

    // Test operator[] for read access
    std::cout << "str4[0]: " << str4[0] << "\n"; // Output: H
    std::cout << "str4[1]: " << str4[1] << "\n"; // Output: e

    // Test operator[] for write access
    str4[0] = 'h'; // Modify the first character
    std::cout << "str4 after modification: " << str4.c_str() << "\n"; // Output: hello

    // Test at() for read access
    std::cout << "str4.at(1): " << str4.at(1) << "\n"; // Output: e

    // Test at() for write access
    str4.at(1) = 'a'; // Modify the second character
    std::cout << "str4 after modification: " << str4.c_str() << "\n"; // Output: hallo

    // Test out-of-bounds access with at() (should throw an exception)
    try {
      std::cout << "str4.at(10): " << str4.at(10) << "\n"; // Throws std::out_of_range
    } catch (const std::out_of_range& e) {
     std::cout << "Caught exception: " << e.what() << "\n"; // Output: Caught exception: Index out of range
    }

    // Test out-of-bounds access with operator[] (undefined behavior, may crash or produce garbage)
    // Uncomment the following lines to see the behavior (not recommended in production code):
    // std::cout << "str4[10]: " << str4[10] << "\n"; // Undefined behavior

    // Test const version of at() and operator[]
    const cppf::String str5{"World"};
    std::cout << "str5[0]: " << str5[0] << "\n"; // Output: W (read-only access)
    std::cout << "str5.at(1): " << str5.at(1) << "\n"; // Output: o (read-only access)

    // Uncommenting the following lines will result in a compilation error (const objects cannot be modified):
    // str5[0] = 'w'; // Error: cannot assign to const object
    // str5.at(1) = 'a'; // Error: cannot assign to const object

    // Test optional functions
    cppf::String str6{"Alice and Bob have mice"};
    auto alice = str6.substr(0, 5);
    std::cout << "alice: " << alice.c_str() << "\n";

    auto mice = str6.substr(19, 4);
    std::cout << "mice: " << mice.c_str() << "\n";

    std::cout << "str6 starts with 'Alice': " << str6.starts_with("Alice") << "\n";
    std::cout << "str6 ends with 'mice': " << str6.ends_with("mice") << "\n";
    std::cout << "str6 contains 'b h': " << str6.contains("b h") << "\n";
    std::cout << "str6 find 'ic': " << str6.find("ic") << "\n";
    std::cout << "str6 find 'ic' starting from 3: " << str6.find("ic", 3) << "\n";

    return 0;
}
#include <iostream>
#include <string>
#include "rational.h"

void print_test_header(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

int main() {
    // Basic construction and output
    print_test_header("Basic Construction");
    Rational a{45, 8};
    Rational b{3, 4};
    std::cout << "a = " << a << ", b = " << b << "\n";
    
    // Additional construction tests
    Rational from_int(5);
    Rational from_neg_int(-3);
    Rational zero;
    std::cout << "From int (5): " << from_int << "\n";
    std::cout << "From neg int (-3): " << from_neg_int << "\n";
    std::cout << "Default (zero): " << zero << "\n";

    // Arithmetic operators - more combinations
    print_test_header("Arithmetic Operations");
    auto r = a + b;
    std::cout << a << " + " << b << " = " << r << "\n";
    
    r = a - b;
    std::cout << a << " - " << b << " = " << r << "\n";
    
    r = a * b;
    std::cout << a << " * " << b << " = " << r << "\n";
    
    r = a / b;
    std::cout << a << " / " << b << " = " << r << "\n";
    
    r /= b;
    std::cout << "(a / b) / b = " << r << "\n";

    // Test with negative numbers
    Rational neg1{-1, 2};
    Rational neg2{1, -3};
    std::cout << "\nNegative numbers:\n";
    std::cout << neg1 << " + " << neg2 << " = " << (neg1 + neg2) << "\n";
    std::cout << neg1 << " - " << neg2 << " = " << (neg1 - neg2) << "\n";
    std::cout << neg1 << " * " << neg2 << " = " << (neg1 * neg2) << "\n";
    std::cout << neg1 << " / " << neg2 << " = " << (neg1 / neg2) << "\n";

    // More compound assignment tests
    print_test_header("Compound Assignment");
    Rational c{1, 2};
    Rational d{1, 3};
    
    c += d;
    std::cout << "(1/2) += (1/3) = " << c << "\n";
    c -= Rational{1, 6};
    std::cout << "(5/6) -= (1/6) = " << c << "\n";
    c *= Rational{3, 1};
    std::cout << "(2/3) *= 3 = " << c << "\n";
    c /= Rational{2, 1};
    std::cout << "2 /= 2 = " << c << "\n";

    // Extended comparison tests
    print_test_header("Comparison Operations");
    Rational e{2, 4};  // Same as 1/2
    Rational f{3, 6};  // Same as 1/2
    Rational g{1, 2};  // Same value
    
    std::cout << e << " == " << f << "? " << (e == f) << " (expected: 1)\n";
    std::cout << e << " == " << g << "? " << (e == g) << " (expected: 1)\n";
    std::cout << b << " < " << a << "? " << (b < a) << " (expected: 1)\n";
    std::cout << a << " > " << b << "? " << (a > b) << " (expected: 1)\n";
    std::cout << e << " >= " << f << "? " << (e >= f) << " (expected: 1)\n";
    std::cout << f << " <= " << g << "? " << (f <= g) << " (expected: 1)\n";
    std::cout << a << " != " << b << "? " << (a != b) << " (expected: 1)\n";

    // More unary operator tests
    print_test_header("Unary Operators");
    Rational pos{3, 4};
    Rational neg{-2, 5};
    
    std::cout << "+" << pos << " = " << (+pos) << "\n";
    std::cout << "-" << pos << " = " << (-pos) << "\n";
    std::cout << "+" << neg << " = " << (+neg) << "\n";
    std::cout << "-" << neg << " = " << (-neg) << "\n";

    // Extended special cases
    print_test_header("Special Cases");
    Rational inf{1, 0};
    Rational neg_inf{-1, 0};
    Rational nan{0, 0};
    
    std::cout << "inf: " << inf << "\n";
    std::cout << "-inf: " << neg_inf << "\n";
    std::cout << "nan: " << nan << "\n";
    
    // Infinity arithmetic
    std::cout << "\nInfinity Arithmetic:\n";
    std::cout << "inf + 1 = " << (inf + Rational{1}) << "\n";
    std::cout << "inf - inf = " << (inf - inf) << " (expected: NaN)\n";
    std::cout << "inf * 0 = " << (inf * zero) << " (expected: NaN)\n";
    std::cout << "0 / 0 = " << (zero / zero) << " (expected: NaN)\n";
    std::cout << "inf / inf = " << (inf / inf) << " (expected: NaN)\n";
    std::cout << "1 / inf = " << (Rational{1} / inf) << " (expected: 0)\n";
    std::cout << "inf * inf = " << (inf * inf) << " (expected: Inf)\n";

    // NaN propagation
    std::cout << "\nNaN Propagation:\n";
    std::cout << "nan + 1 = " << (nan + Rational{1}) << " (expected: NaN)\n";
    std::cout << "1 + nan = " << (Rational{1} + nan) << " (expected: NaN)\n";
    std::cout << "nan * 5 = " << (nan * Rational{5}) << " (expected: NaN)\n";
    std::cout << "nan == nan? " << (nan == nan) << " (expected: 0)\n";

    // String operations - more test cases
    print_test_header("String Operations");
    Rational from_str1{"-3/4"};
    Rational from_str2{"6/-9"};
    Rational from_str3{"0/1"};
    
    std::cout << "From \"-3/4\": " << from_str1 << "\n";
    std::cout << "From \"6/-9\": " << from_str2 << " (expected: (-2/3))\n";
    std::cout << "From \"0/1\": " << from_str3 << "\n";
    
    from_str1.str("22/7");
    std::cout << "After str(\"22/7\"): " << from_str1 << "\n";
    
    // Test invalid string formats
    try {
        Rational invalid("3/4/5");
        std::cout << "ERROR: Shouldn't reach here - invalid format\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Correctly caught invalid format: 3/4/5\n";
    }
    
    try {
        Rational invalid("abc");
        std::cout << "ERROR: Shouldn't reach here - non-numeric\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Correctly caught non-numeric input\n";
    }

    // Edge cases
    print_test_header("Edge Cases");
    Rational large_num{123456, 987654};
    std::cout << "Large fraction: " << large_num << " (simplified)\n";
    
    Rational large_den{1, 987654};
    std::cout << "Small fraction: " << large_den << "\n";
    
    Rational neg_denom{3, -4};
    std::cout << "Negative denominator: " << neg_denom << " (expected: (-3/4))\n";
    
    Rational zero_num{0, 5};
    std::cout << "Zero numerator: " << zero_num << " (expected: (0/1))\n";

    // Mixed operations
    print_test_header("Mixed Operations");
    Rational x{1, 2};
    Rational y{1, 3};
    Rational z{1, 6};
    
    auto result = (x + y) * z / Rational{2};
    std::cout << "(1/2 + 1/3) * 1/6 / 2 = " << result << " (expected: (5/72))\n";
    
    result = -result + Rational{1, 4};
    std::cout << "-previous + 1/4 = " << result << " (expected: (13/72))\n";

    std::cout << "\nAll tests completed successfully!\n";
    return 0;
}
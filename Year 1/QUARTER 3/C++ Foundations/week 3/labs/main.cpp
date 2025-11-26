#include "complex.h"
#include <iostream>

int main(){
    //text constructors
    Complex a{1.0, 2.0};
    Complex b{3.0, 4.0};
    Complex c{"3 + 4i"};
    Complex d{"-i"};
    Complex e{"5"};
    Complex f{"3 +4.2i"};
    Complex g{"3-4.2i"};
    Complex h{"-4.2i"};
    Complex j{"-i"};

    //test arithmetic operations
    auto sum = a.add(b);
    auto diff = a.sub(b);
    auto prod = a.mul(b);
    auto quot = a.div(b);

    //test modulus and argument
    double mod = a.modulus();
    double arg = a.argument();

    //test output 
    std::cout << "a: " << a << '\n'; // 1+2i
    std::cout << "b: " << b << '\n'; // 3+4i
    std::cout << "c: " << c << '\n'; // 3+4i
    std::cout << "d: " << d << '\n'; // 0-1i
    std::cout << "e: " << e << '\n'; // 5+0i
    std::cout << "f: " << f << '\n'; // 3+4.2i
    std::cout << "g: " << g << '\n'; // 3-4.2i
    std::cout << "h: " << h << '\n'; // 0-4.2i
    std::cout << "j: " << j << '\n'; // 0-1i
    
    std::cout << "sum: " << sum << '\n';    // 4+6i
    std::cout << "diff: " << diff << '\n';  // -2-2i
    std::cout << "prod: " << prod << '\n';  // -5+10i
    std::cout << "quot: " << quot << '\n';  // 0.44+0.08i
    std::cout << "mod: " << mod << '\n';    // 2.23607
    std::cout << "arg: " << arg << '\n';    // 1.10715

    return 0;
}
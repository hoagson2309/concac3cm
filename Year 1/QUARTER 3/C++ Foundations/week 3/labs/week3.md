# Week 3 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 26/2/2025

# LABS
```cpp
//COMPLEX.H
#ifndef COMPLEX_H 
#define COMPLEX_H

#include <string>
#include <iostream>
#include <cmath>


class Complex{
public:
    //Constructor
    Complex(double real = 0.0, double imag = 0.0);
    Complex(const std::string& str);

    //accessors
    double real() const; //Provide read-only access to the private data members real_ and imag_
    double imag() const; 

    //arithmetic operation
    Complex add(const Complex& other) const;
    Complex sub(const Complex& other) const;
    Complex mul(const Complex& other) const;
    Complex div(const Complex& other) const;

    //modulus and argument
    double modulus() const;
    double argument() const;

private:
    //Store the real and imaginary parts of the complex number.
    double real_;//real part
    double imag_;//imaginary part

    //helper function to remove spaces from a string
    std::string removeSpaces(const std::string& str) const;
};

inline std::ostream& operator<<(std::ostream& out, const Complex& c){
    return out << c.real() << (c.imag() < 0.0 ? "-" : "+") << std::abs(c.imag()) << "i";
}

#endif //COMPLEX_H

//COMPLEX.CPP
#include "complex.h"
#include <sstream>
#include <cctype> //for functions like std::isspace to check for whitespace characters.
#include <stdexcept> //provides standard exception classes like std::invalid_argument

//constructor implementation
Complex::Complex(double real, double imag) : real_{real}, imag_{imag} {} //initializes a Complex object with the given real and imaginary parts.
// ex: Complex c{3.0, 4.0}; //creates a complex number 3 + 4i

std::string Complex::removeSpaces(const std::string& str) const{
    std::string result;
    //// Iterate over each character in the string
    for (char ch : str) {
        if (!::isspace(ch)) { // if the character is not a space
            result += ch;      // add it to the result
        }
    }
    return result;
}

Complex::Complex(const std::string& str){
    //remove all spaces from string
    std::string s = removeSpaces(str);

    //initialize real and imaginary parts to 0
    real_ = 0.0;
    imag_ = 0.0;

    //find the position of 'i'(imaginary unit)
    size_t iPos = s.find('i');

    //if 'i' is found, extract the imaginary part
    if ( iPos != std::string::npos ){
        //extract the substring b4 'i' as the imaginary part
        std::string imagStr = s.substr(0, iPos);

        //handle the case like "+i" or "-i"(imaginary part is "+1" or "-1")
        if ( imagStr.empty() || imagStr == "+"){
            imag_ = 1.0;
        } else if ( imagStr == "-"){
            imag_ = -1.0;
        } else {
            imag_ = std::stod(imagStr);  //convert string to double
        }

        //remove the imaginary part from the string to extract the real part
        s.erase(0, iPos + 1);
    }

    if( !s.empty() ){
        real_ = std::stod(s); //convert string to double    
    }
}

double Complex::real() const{
    return real_;
}

double Complex::imag() const{
    return imag_;
}

Complex Complex::add(const Complex& other) const{
    return Complex{real_ + other.real_, imag_ + other.imag_};
}

Complex Complex::sub(const Complex& other) const{
    return Complex{real_ - other.real_, imag_ - other.imag_};
}

Complex Complex::mul(const Complex& other) const{
    return Complex{real_ * other.real_ - imag_ * other.imag_, real_ * other.imag_ + imag_ * other.real_};
}

Complex Complex::div(const Complex& other) const{
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    if(denominator == 0){
        throw std::invalid_argument("Division by zero");
    }
    return Complex{(real_ * other.real_ + imag_ * other.imag_) / denominator, (imag_ * other.real_ - real_ * other.imag_) / denominator};
}

//modulus and argument implementation
double Complex::modulus() const{
    return std::sqrt(real_ * real_ + imag_ * imag_); 
}

double Complex::argument() const{
    return std::atan2(imag_, real_);    
}



// Example: "3 + 4i"
// Remove spaces: "3+4i"
// Find 'i': iPos = 3
// Extract imaginary part: imagStr = "3+4"
// Handle imaginary part: imag_ = 4.0
// Remove imaginary part: s = ""
// Extract real part: real_ = 3.0
// Result: real_ = 3.0, imag_ = 4.0

//MAIN.CPP
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
```
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
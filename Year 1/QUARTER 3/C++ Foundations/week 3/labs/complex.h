#ifndef COMPLEX_H //checks if COMPLEX_H is not defined.
#define COMPLEX_H

#include <string> //std::string class
#include <iostream> //Provides input/output functionality (e.g., std::cout).
#include <cmath> //Provides mathematical functions like sqrt and atan2.


class Complex{
public:
    //Constructor
    Complex(double real = 0.0, double imag = 0.0); //Constructors: Initialize a Complex object with real and imaginary parts or from a string.
    Complex(const std::string& str);

    //accessors
    double real() const; //Provide read-only access to the private data members real_ and imag_ (private)
    double imag() const; 

    //arithmetic operation
    Complex add(const Complex& other) const;
    Complex sub(const Complex& other) const;
    Complex mul(const Complex& other) const;
    Complex div(const Complex& other) const;

    //modulus and argument
    double modulus() const; // compute the magnitude and angle of the complex number.
    double argument() const;

private:
    //Store the real and imaginary parts of the complex number.
    double real_;//real part
    double imag_;//imaginary part

    //helper function to remove spaces from a string
    std::string removeSpaces(const std::string& str) const;
};

//Allows printing Complex objects using std::cout.
inline std::ostream& operator<<(std::ostream& out, const Complex& c){
    return out << c.real() << (c.imag() < 0.0 ? "-" : "+") << std::abs(c.imag()) << "i";
}

#endif //COMPLEX_H
#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>

class Rational{
public:
    //constructors
    Rational();                   //Default constructor that initializes the number with a value of 0/1.
    Rational(int num, int den);   //Constructor that takes two integers (numerator and denominator)
    Rational(int num);            //Constructor that takes only one integer (the denominator is assumed to be 1).
    Rational(const std::string& str);   //This constructor parses the string and initializes the Rational instance with the parsed values.

    //accessors
    int num() const;            //for obtaining the values of a numerator and a denominator.
    int den() const;
    std::string str() const;    //str that returns a std::string representation of a Rational instance.

    bool is_pos() const;        //is_pos and is_neg that return a bool value indicating whether the Rational instance is positive or negative.
    bool is_neg() const;
    bool is_inf() const;        //is_inf and is_nan that return true if the Rational instance contains infinity or Not a Number respectively.
    bool is_nan() const;

    //modifiers
    void set(int num, int den);          //set for setting both the numerator and denominator values in one operation.
    void set(const std::string& s);      //str for setting the whole Rational value from a string representation (e.g. “-34/2”). The new values overwrite the old ones.

    Rational add(const Rational& other) const;
    Rational sub(const Rational& other) const;
    Rational mul(const Rational& other) const;
    Rational div(const Rational& other) const;
    Rational pow(int n) const;
    Rational sqrt() const;

private:
    int num_;
    int den_;

    void simplify();  
    int gcd(int a, int b) const;  // calculates the greatest common divisor of two integers to simplify fractions.
};

#endif // RATIONAL_H
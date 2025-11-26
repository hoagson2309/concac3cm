#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cmath>

class Rational {
    public:
        Rational();
        Rational(int numerator, int denominator = 1);
    
        Rational(const std::string& str);
    
        int num() const;
        int den() const;
    
        std::string str() const;
        void str(const std::string s);
    
        bool is_pos() const;
        bool is_neg() const;
        bool is_inf() const;
        bool is_nan() const;

        //compound assignment operators
        Rational& operator+=(const Rational& other);
        Rational& operator-=(const Rational& other);
        Rational& operator*=(const Rational& other);
        Rational& operator/=(const Rational& other);

        // Unary operators
        Rational operator-() const;
        Rational operator+() const;

        // Comparison operators
        bool operator==(const Rational& rhs) const;
        bool operator!=(const Rational& rhs) const;
        bool operator>(const Rational& rhs) const;
        bool operator<(const Rational& rhs) const;
        bool operator>=(const Rational& rhs) const;
        bool operator<=(const Rational& rhs) const;
    
    private:
        int num_;
        int den_;

        bool is_zero() const;
        void normalize();
        static int gcd(int a, int b);
    };

    // Arithmetic operators
Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

// Stream output operator
std::ostream& operator<<(std::ostream& os, const Rational& r);

#endif // RATIONAL_H




/*
Rational::Rational(int numerator) : num_(numerator), den_(1) {}

Actually, upon closer inspection, we can see that the two-parameter constructor already has a default parameter for the denominator (Rational(int numerator, int denominator = 1)), 
which means we don't even need the single-parameter constructor at all! 
The compiler will automatically use the two-parameter constructor when only one integer is provided.
*/
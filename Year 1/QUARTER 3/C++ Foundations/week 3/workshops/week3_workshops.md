# Week 3 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 26/2/2025

# WORKSHOPS
```cpp
//RATIONAL.H
#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>

class Rational{
public:
    //constructors
    Rational();                   //Default constructor that initializes the number with a value of 0/1.
    Rational(int num, int den);   //Constructor that takes two integers (numerator and denominator)
    Rational(int num);            //Constructor that takes only one integer (the denominator is assumed to be 1).
    Rational(std::string& str);   //This constructor parses the string and initializes the Rational instance with the parsed values.

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

//RATIONAL.CPP
#include "rational.h"
#include <sstream>
#include <cmath>
#include <algorithm>

//default constructor
Rational::Rational() : num_(0) , den_(1) {}

//constructor with numerator and denominator
Rational::Rational(int num, int den) : num_(num) , den_(den) {
    simplify();
}

//constructor with only numerator
Rational::Rational(int num) : num_(num) , den_(1) {}

//constructor with string
Rational::Rational(std::string& str){
    set(str);
}

//accessors
int Rational::num() const{
    return num_;
}
int Rational::den() const{
    return den_;
}

std::string Rational::str() const{
    if(is_nan()) return "NaN";
    if(is_inf()) return (num_ > 0 ? "+inf" : "-inf");
    return std::to_string(num_) + "/" + std::to_string(den_); //Converts the numerator (num_) and the denominator (den_) to a string (ex: 3/4)
}

bool Rational::is_pos() const { 
    return num_ > 0 && !is_nan() && !is_inf();
}
bool Rational::is_neg() const{
    return num_ < 0 && !is_nan() && !is_inf();
}
bool Rational::is_inf() const{
    return den_ == 0 && num_ != 0;
}
bool Rational::is_nan() const{
    return den_ == 0 && num_ == 0;
}

//modifier
void Rational::set(int num, int den){
    num_ = num;
    den_ = den;
    simplify();
}

void Rational::set(const std::string& s){
    std::string str = s;
    str.erase(std::remove(str.begin(), str.end(), '('), str.end());
    str.erase(std::remove(str.begin(), str.end(), ')'), str.end());

    size_t slashPos = str.find('/');
    if (slashPos == std::string::npos){
        num_ = std::stoi(str); //convert string to an integer
        den_ = 1;
    } else{
        num_ = std::stoi(str.substr(0, slashPos));  
        den_ = std::stoi(str.substr(slashPos + 1));
    }
    simplify();
}

//simplify the fraction
void Rational::simplify(){
    if(den_ < 0){
        num_ = -num_;
        den_ = -den_; // - - => +
    }
    int commonDivisor = gcd(std::abs(num_), std::abs(den_));
    num_ /= commonDivisor;  //  divide by greatest divisor
    den_ /= commonDivisor;
}

int Rational::gcd(int a, int b) const{
    while(b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Rational Rational::add(const Rational& other) const{
    int newNum = num_ * other.den_ + other.num_ * den_;
    int newDen = den_ * other.den_;
    return Rational(newNum, newDen);
}

Rational Rational::sub(const Rational& other) const{
    int newNum = num_ * other .num_ - other.num_ * num_;
    int newDen = den_ * other.den_;
    return Rational(newNum, newDen);
}

Rational Rational::mul(const Rational& other) const{
    int newNum = num_ * other.num_;
    int newDen = den_ * other.den_;
    return Rational(newNum, newDen);
}

Rational Rational::div(const Rational& other) const{
    int newNum = num_ * other.num_;
    int newDen = den_ * other.den_;
    return Rational(newNum, newDen);
}

Rational Rational::pow(int n) const{
    if(n == 0) return Rational(1, 1);
    Rational result = *this;
    for(int i = 1; i < n; ++i){
        result = result.mul(*this);
    }
    return result;
}

Rational Rational::sqrt() const{
    if(is_nan() || is_neg() || is_inf()) return Rational(0, 0); // NaN
    int numRoot = std::sqrt(num_);
    int denRoot = std::sqrt(den_);
    if(numRoot * numRoot != num_ || denRoot * denRoot != den_) return Rational(0, 0); //NaN
    return Rational(numRoot, denRoot);
}

//RATIONAL_CALC.H
#ifndef RATIONAL_CALC_H
#define RATIONAL_CACL_H

#include "rational.h"
#include <string>

Rational calculate(const std::string& expr);
bool process(const std::string& file_name);

#endif //RATIONAL_CALC_H

//RATIONAL_CALC.CPP
#include "rational_calc.h"
#include <fstream>
#include <sstream>
#include <iostream>

Rational calculate(const std::string& expr){ //free function
    std::istringstream iss(expr); //This makes it easy to extract data
    std::string part1, op, part2;
    
    //check if the expression starts with "sqrt"
    if(expr.substr(0, 4) == "sqrt"){
        std::string sqrtArg = expr.substr(5); // extract the argument after "sqrt" and a space
        Rational r(sqrtArg);
        return r.sqrt();
    }

    //otherwis, parse the expression into two numbers and an operator
    iss >> part1 >> op >> part2;

    Rational a(part1);
    Rational b(part2);

    //perform the operation based on the operator
    if (op == "+") return a.add(b);
    if (op == "-") return a.sub(b);
    if (op == "*") return a.mul(b);
    if (op == "/") return a.div(b);
    if (op == "^") return a.pow(std::stoi(part2));
    if (op == "sqrt") return a.sqrt();

    //if the operator is invalid, return NaN
    return Rational(0, 0); //NaN
}

bool process(const std::string& file_name){
    std::ifstream infile(file_name);
    if(!infile) return false;

    std::ofstream outfile(file_name + ".out");
    if(!outfile) return false;

    std::string line;
    while (std::getline(infile, line)){
        Rational result = calculate(line);
        outfile << result.str() << std::endl;
    }
    return true;
}

//MAIN.CPP
#include "rational_calc.h"
#include <iostream>

int main(int argc, char* argv[]){
    if(argc > 1){
        std::string filename = argv[1];
        if(!process(filename)){
            std::cerr << "Error processing file: " << filename << std::endl;
            return 1;
        }
    } else {
        std::string expr;
        while(std::getline(std::cin, expr)){
            Rational result = calculate(expr);
            std::cout << result.str() << std::endl;
        }
    }
    
    return 0;
}
```
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
Rational::Rational(const std::string& str){
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
    if(is_nan() || other.is_nan()) return Rational(0, 0); //NaN + anything = NaN
    if(is_inf() || other.is_inf()){
        if(is_inf() && other.is_inf()){
            //case: +inf + (-inf) = NaN
            if(num_ * other.num_ < 0) return Rational(0, 0);
            //case: +inf + +inf = inf
            return *this;
        }
        //case: inf + normal = inf
        return is_inf() ? *this : other;  // Example: +∞ + 5 returns +∞
    }                                      //Example: 5 + (-∞) returns -∞
    int newNum = num_ * other.den_ + other.num_ * den_;
    int newDen = den_ * other.den_;
    return Rational(newNum, newDen);
}

Rational Rational::sub(const Rational& other) const{
    // Handle NaN cases
    if (is_nan() || other.is_nan()) return Rational(0, 0);
    
     // Handle infinity cases
     if (is_inf() || other.is_inf()) {
        if (is_inf() && other.is_inf()) {
            // Cases: inf - inf = NaN, -inf - (-inf) = NaN
            if (num_ * other.num_ > 0) return Rational(0, 0);
            // Cases: inf - (-inf) = inf, -inf - inf = -inf
            return *this;
        }
        // Case: inf - normal = inf, normal - inf = -inf
        return is_inf() ? *this : Rational(-other.num_, 0);  //return (-other.num,0) because it's -inf cannot be +inf
    }
    int newNum = num_ * other .den_ - other.num_ * den_;
    int newDen = den_ * other.den_;
    return Rational(newNum, newDen);
}

Rational Rational::mul(const Rational& other) const{
    // Handle NaN cases
    if (is_nan() || other.is_nan()) return Rational(0, 0);
    
    // Handle infinity cases
    if (is_inf() || other.is_inf()) {
        // Cases: 0 * inf = NaN, inf * 0 = NaN
        if ((is_inf() && other.num_ == 0) || (other.is_inf() && num_ == 0))
            return Rational(0, 0);
        // Cases: inf * non-zero = inf (with sign)
        return Rational(num_ * other.num_, 0);
    }
    int newNum = num_ * other.num_;
    int newDen = den_ * other.den_;
    return Rational(newNum, newDen);
}

Rational Rational::div(const Rational& other) const{
    // Handle NaN cases
    if (is_nan() || other.is_nan()) return Rational(0, 0);
    
    // Handle infinity cases
    if (is_inf()) {
        if (other.is_inf()) return Rational(0, 0); // inf/inf = NaN
        return Rational(num_ * other.den_, 0); // inf/x = inf (with sign)
    }
    
    // Handle division by zero
    if (other.num_ == 0) {
        if (num_ == 0) return Rational(0, 0); // 0/0 = NaN
        return Rational(num_ * other.den_, 0); // x/0 = inf (with sign)
    }

    if (other.is_inf()) return Rational(0, 1); // x/inf = 0
    int newNum = num_ * other.den_;
    int newDen = den_ * other.num_;
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





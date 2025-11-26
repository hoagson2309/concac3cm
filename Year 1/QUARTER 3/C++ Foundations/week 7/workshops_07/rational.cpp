#include "rational.h"

Rational::Rational() : num_(0), den_(1) {}

Rational::Rational(int numerator, int denominator) : num_(numerator), den_(denominator) {
    if(denominator == 0){
        if(numerator == 0) {
            num_ = 0;
            den_ = 0; //Nan
        } else {
            num_ = (numerator > 0) ? 1 : -1;
            den_ = 0;   //Infinity
        }
    } else {
        normalize();
    }
}

Rational::Rational(const std::string& str) {
    std::istringstream iss(str);
    char slash;
    if(iss >> num_ >> slash >> den_){
        if(slash != '/'){
            throw std::invalid_argument("Invalid rational format!");
        }
        if(den_ == 0){
            if(num_ == 0){
                num_ = 0;
                den_ = 0; //Nan
            } else {
                num_ = (num_ > 0) ? 1 : -1;
                den_ = 0; //Infinity
            }
        } else {
            normalize();
        }
    } else { 
        throw std::invalid_argument("Invalid rational format!");
    }
}

int Rational::num() const { return num_; }
int Rational::den() const { return den_; }

std::string Rational::str() const{
    if(is_nan()) return "NaN";
    if(is_inf()) return (num_ > 0) ? "Inf" : "-Inf";
    return "(" + std::to_string(num_) + '/' + std::to_string(den_) + ")";
}

void Rational::str(const std::string s){  //EXPLAIN~~~~~~~
    *this = Rational(s);
}

bool Rational::is_pos() const{
    if(is_nan() || is_inf()) return false;
    return num_ > 0;
}

bool Rational::is_neg() const { 
    if (is_nan() || is_inf()) return false;
    return num_ < 0; 
}

bool Rational::is_inf() const { return den_ == 0 && num_ != 0; }
bool Rational::is_nan() const { return den_ == 0 && num_ == 0; }

Rational& Rational::operator+=(const Rational& other) {   //EXPLAIN ~~~~~~~
    if(is_nan() || other.is_nan()){
        *this = Rational(0, 0);
        return *this;
    }
    if(is_inf() || other.is_inf()){   //ex: (2, 0) or (-3, 0)
        if(is_inf() && other.is_inf() && num_ != other.num_){
           *this = Rational(0, 0);  //Inf + (-Inf) = NaN
        } if (is_inf()){
            return *this;  // Example: +∞ + 5 returns +∞ or -∞ + 5 returns -∞
        } else {
            *this = other;  //Example: 5 + (-∞) returns -∞ or 5 + (+∞) returns +∞
        }
        return *this;
    }
    num_ = num_ * other.den_ + other.num_ * den_;
    den_ *= other.den_;
    normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& other){
    return *this += (-other);
}

Rational& Rational::operator*=(const Rational& other) {
    if (is_nan() || other.is_nan()) {
        *this = Rational(0, 0);
        return *this;
    }
    if(is_inf() || other.is_inf()){
        if(is_zero() || other.is_zero()){  //is_zero => num == 0
            *this = Rational(0, 0); // 0 * Inf = NaN
        } else {
            int sign = (num_ * other.num_) > 0 ? 1 : -1;    //EXPLAIN ~~~~~~~~
            *this = Rational(sign, 0);
        }
        return *this;
    }
    num_ *= other.num_;
    den_ *= other.den_;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    if (is_nan() || other.is_nan()) {
        *this = Rational(0, 0);
        return *this;
    }
    if (other.is_zero()) {
        if (is_zero()) {
            *this = Rational(0, 0); // 0/0 = NaN
        } else {
            int sign = (num_ * other.num_) > 0 ? 1 : -1;
            *this = Rational(sign, 0); // x/0 = Inf
        }
        return *this;
    }
    if (is_inf()) {
        if (other.is_inf()) {
            *this = Rational(0, 0); // Inf/Inf = NaN
        } else {
            return *this;
        }
        return *this;
    }
    if (other.is_inf()) {
        *this = Rational(0, 1); // x/Inf = 0
        return *this;
    }
    num_ *= other.den_;
    den_ *= other.num_;
    normalize();
    return *this;
}

Rational Rational::operator-() const {
    if (is_nan()) return *this;
    if (is_inf()) return Rational(-num_, 0);
    return Rational(-num_, den_);
}

Rational Rational::operator+() const {
    return *this;
}

bool Rational::operator==(const Rational& rhs) const{
    if(is_nan() || rhs.is_nan() || is_inf() || rhs.is_inf()) return false;
    return num_ == rhs.num_ && den_ == rhs.den_;
}

bool Rational::operator!=(const Rational& rhs) const{
    return !(*this == rhs);
}

bool Rational::operator>(const Rational& rhs) const {
    if (is_nan() || rhs.is_nan() || is_inf() || rhs.is_inf()) return false;
    return num_ * rhs.den_ > rhs.num_ * den_;
}

bool Rational::operator<(const Rational& rhs) const {
    if (is_nan() || rhs.is_nan() || is_inf() || rhs.is_inf()) return false;
    return num_ * rhs.den_ < rhs.num_ * den_;
}

bool Rational::operator>=(const Rational& rhs) const {   //EXPLAIN WHY THESE @ FUNCTIONS are different from the two above? why not return *this above
    return *this > rhs || *this == rhs;
}

bool Rational::operator<=(const Rational& rhs) const {
    return *this < rhs || *this == rhs;
}

bool Rational::is_zero() const { return num_ == 0 && den_ != 0; } //!!!!

void Rational::normalize(){
    if(den_ < 0){
        num_ = -num_;
        den_ = -den_;
    }
    int gcd_val = gcd(std::abs(num_), std::abs(den_));
    num_ /= gcd_val;
    den_ /= gcd_val;
}

int Rational::gcd(int a, int b){
    while(b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result = lhs;
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs){
    Rational result = lhs;
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs){
    Rational result = lhs;
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs){
    Rational result = lhs;
    result /= rhs;
    return result;
}

std::ostream& operator<<(std::ostream& os, const Rational& r){
    os << r.str();
    return os;
}



#ifndef RATIONAL_CALC_H
#define RATIONAL_CALC_H

#include "rational.h"
#include <string>

Rational calculate(const std::string& expr);
bool process(const std::string& file_name);

#endif //RATIONAL_CALC_H
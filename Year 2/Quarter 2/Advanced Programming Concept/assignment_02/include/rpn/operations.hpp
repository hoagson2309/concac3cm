#ifndef INCLUDED_OPERATIONS_OPERATIONS_HPP
#define INCLUDED_OPERATIONS_OPERATIONS_HPP

#include <string_view>
#include <numbers>
#include <cmath>
#include "../interfaces/ioperation.hpp"
#include <stdexcept>

namespace sax
{   
    //~~~BINARY OPERATION~~~
    struct Addition : public IBinaryOperation{
        double evaluate(double left, double right) const override { return left + right;}
        std::string_view symbol() const override { return "+"; }
        std::string_view help() const override { return "+: Addition - adds two numbers."; }
    };

    struct Subtraction : public IBinaryOperation{
        double evaluate(double left, double right) const override { return left - right;}
        std::string_view symbol() const override { return "-"; }
        std::string_view help() const override { return "-: Subtraction - subtracts two numbers."; }
    };

    struct Multiplication : public IBinaryOperation{
        double evaluate(double left, double right) const override { return left * right;}
        std::string_view symbol() const override { return "*"; }
        std::string_view help() const override { return "*: Multiplication - multiplies two numbers."; }
    };

    struct Division : public IBinaryOperation{
        double evaluate(double left, double right) const override { return left / right;}
        std::string_view symbol() const override { return "/"; }
        std::string_view help() const override { return "/: Division - divides two numbers."; }
    };

    struct Power : public IBinaryOperation{
        double evaluate(double left, double right) const override {
            double p = std::pow(left, right);
            if(std::isnan(p)) throw std::invalid_argument("Invalid power operation");
            return p;
        }
        std::string_view symbol() const override { return "^"; }
        std::string_view help() const override { return "^: Power - Power of two numbers."; }
    };

    //~~~UNARY OPERATION~~~
    struct SqrtOp : public IUnaryOperation{
        double evaluate(double operand) const override {
            if(operand < 0.0) throw std::invalid_argument("Square root of negative number");
            return std::sqrt(operand);
        }
        std::string_view symbol() const override { return "sqrt"; }
        std::string_view help() const override { return "sqrt: Square root - calculates sqrt(operand)"; }
    };

    struct ExpOp : public IUnaryOperation{
        double evaluate(double operand) const override {
            return std::exp(operand);
        }
        std::string_view symbol() const override { return "exp"; }
        std::string_view help() const override { return "exp: Exponentiation - calculates the exponent with the natural base e."; }
    };

    struct LnOp : public IUnaryOperation{
        double evaluate(double operand) const override {
            if(operand < 0.0) throw std::invalid_argument("Logarithm of non-positive number");
            return std::log(operand);
        }
        std::string_view symbol() const override { return "ln"; }
        std::string_view help() const override { return "ln: Logarithm - calculates the natural logarithm of a number."; }
    };

    //~~~Nullary operations (constants)~~~
    struct Pi : public INullaryOperation{
        double evaluate() const override { return std::numbers::pi_v<double>; }
        std::string_view symbol() const override { return "pi"; }
        std::string_view help() const override { return "pi: Returns the value of π."; }

    };

    struct EConst : public INullaryOperation{
        double evaluate() const override { return std::numbers::e_v<double>; }
        std::string_view symbol() const override { return "e_constant"; }
        std::string_view help() const override { return "e_constant: Returns the value of constant e."; }
    };


}

#endif /* INCLUDED_OPERATIONS_OPERATIONS_HPP */

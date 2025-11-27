#ifndef INCLUDED_OPERATIONS_OPERATIONS_HPP
#define INCLUDED_OPERATIONS_OPERATIONS_HPP

#include <string_view>
#include <numbers>
#include <cmath>
#include "../interfaces/ioperation.hpp"
#include <stdexcept>
#include <functional>

namespace sax
{   
    class BinaryOperation : public IBinaryOperation {
        public:
            BinaryOperation(std::string_view s, std::string_view h, std::function<double(double, double)> f) 
                : symbol_(s), help_(h), func_(f) {} 

            double evaluate(double left, double right) const override { return func_(left, right); }
            std::string_view symbol() const override { return symbol_; }
            std::string_view help() const override { return help_; }

        private:
            std::string symbol_;
            std::string help_;
            std::function<double(double, double)> func_;
    };

    class UnaryOperation : public IUnaryOperation {
        public:
            UnaryOperation(std::string_view s, std::string_view h, std::function<double(double)> f) 
                : symbol_(s), help_(h), func_(f) {} 

            double evaluate(double operand) const override { return func_(operand); }
            std::string_view symbol() const override { return symbol_; }
            std::string_view help() const override { return help_; }

        private:
            std::string symbol_;
            std::string help_;
            std::function<double(double)> func_;
    };

    class NullaryOperation : public INullaryOperation {
        public:
            NullaryOperation(std::string_view s, std::string_view h, std::function<double()> f) 
                : symbol_(s), help_(h), func_(f) {} 

            double evaluate() const override { return func_(); }
            std::string_view symbol() const override { return symbol_; }
            std::string_view help() const override { return help_; }

        private:
            std::string symbol_;
            std::string help_;
            std::function<double()> func_;
    };


    template<typename>
    inline constexpr bool always_false = false;

    template<typename Callable>
        std::unique_ptr<IOperation> make_operation(std::string_view symbol, std::string_view help, Callable func) {
            //if constexpr lets the compiler decide at compile time which branch to use, based on the callable’s type.
            if constexpr (std::is_invocable_r_v<double, Callable>) {            //check if it's nullary lamda
                return std::make_unique<NullaryOperation>(symbol, help, func); 
            } else if constexpr (std::is_invocable_r_v<double, Callable, double>) {     //check if it's unary lamda
                return std::make_unique<UnaryOperation>(symbol, help, func);
            } else if constexpr (std::is_invocable_r_v<double, Callable, double, double>) { //check if it's binary lamda
                return std::make_unique<BinaryOperation>(symbol, help, func);
            } else {
                static_assert(always_false<Callable>, "Unsupported callable type");
            }
        }
}

//Because static_assert(false, "...") inside a template always fails, even if that branch is never taken.
//false is not dependent on the template type => the compiler sees it immediately => compile-time error.
//always_false<Callable> is dependent on the template parameter, so the compiler only evaluates it if that branch is chosen by if constexpr.
//This avoids errors unless the callable type is truly unsupported.

//static_assert(false, ...) => always triggers => unusable in templates.
//static_assert(always_false<Callable>, ...) => only triggers when needed.

// 1. Callable
// It’s a template parameter representing any function-like object: a lambda, function pointer, or std::function.
// Using Callable lets us write one make_operation function that works for nullary, unary, or binary operations without writing separate functions.

// 2. constexpr
// In if constexpr, it allows the compiler to evaluate the condition at compile time.
// Only the branch that is true gets compiled; other branches are ignored.
// This is important so that static_assert(always_false<Callable>, ...) does not trigger unless we actually reach the unsupported branch.

#endif /* INCLUDED_OPERATIONS_OPERATIONS_HPP */

    

    // //~~~BINARY OPERATION~~~
    // struct Addition : public IBinaryOperation{
    //     double evaluate(double left, double right) const override { return left + right;}
    //     std::string_view symbol() const override { return "+"; }
    //     std::string_view help() const override { return "+: Addition - adds two numbers."; }
    // };

    // struct Subtraction : public IBinaryOperation{
    //     double evaluate(double left, double right) const override { return left - right;}
    //     std::string_view symbol() const override { return "-"; }
    //     std::string_view help() const override { return "-: Subtraction - subtracts two numbers."; }
    // };

    // struct Multiplication : public IBinaryOperation{
    //     double evaluate(double left, double right) const override { return left * right;}
    //     std::string_view symbol() const override { return "*"; }
    //     std::string_view help() const override { return "*: Multiplication - multiplies two numbers."; }
    // };

    // struct Division : public IBinaryOperation{
    //     double evaluate(double left, double right) const override { return left / right;}
    //     std::string_view symbol() const override { return "/"; }
    //     std::string_view help() const override { return "/: Division - divides two numbers."; }
    // };

    // struct Power : public IBinaryOperation{
    //     double evaluate(double left, double right) const override {
    //         double p = std::pow(left, right);
    //         if(std::isnan(p)) throw std::invalid_argument("Invalid power operation");
    //         return p;
    //     }
    //     std::string_view symbol() const override { return "^"; }
    //     std::string_view help() const override { return "^: Power - Power of two numbers."; }
    // };

    // //~~~UNARY OPERATION~~~
    // struct SqrtOp : public IUnaryOperation{
    //     double evaluate(double operand) const override {
    //         if(operand < 0.0) throw std::invalid_argument("Square root of negative number");
    //         return std::sqrt(operand);
    //     }
    //     std::string_view symbol() const override { return "sqrt"; }
    //     std::string_view help() const override { return "sqrt: Square root - calculates sqrt(operand)"; }
    // };

    // struct ExpOp : public IUnaryOperation{
    //     double evaluate(double operand) const override {
    //         return std::exp(operand);
    //     }
    //     std::string_view symbol() const override { return "exp"; }
    //     std::string_view help() const override { return "exp: Exponentiation - calculates the exponent with the natural base e."; }
    // };

    // struct LnOp : public IUnaryOperation{
    //     double evaluate(double operand) const override {
    //         if(operand < 0.0) throw std::invalid_argument("Logarithm of non-positive number");
    //         return std::log(operand);
    //     }
    //     std::string_view symbol() const override { return "ln"; }
    //     std::string_view help() const override { return "ln: Logarithm - calculates the natural logarithm of a number."; }
    // };

    // //~~~Nullary operations (constants)~~~
    // struct Pi : public INullaryOperation{
    //     double evaluate() const override { return std::numbers::pi_v<double>; }
    //     std::string_view symbol() const override { return "pi"; }
    //     std::string_view help() const override { return "pi: Returns the value of π."; }

    // };

    // struct EConst : public INullaryOperation{
    //     double evaluate() const override { return std::numbers::e_v<double>; }
    //     std::string_view symbol() const override { return "e_constant"; }
    //     std::string_view help() const override { return "e_constant: Returns the value of constant e."; }
    // };




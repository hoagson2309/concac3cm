#ifndef INCLUDED_INCLUDE_IOPERATION_HPP
#define INCLUDED_INCLUDE_IOPERATION_HPP

#include <string_view>
#include <optional>

namespace sax
{
    struct IOperation
    {
        virtual ~IOperation() = default;

        // operation symbol, e.g. "+", "sqrt", "Pi_constant"
        virtual std::string_view symbol() const = 0;
        //human readable help text for this operation
        virtual std::string_view help() const = 0;
    };

    struct INullaryOperation : public IOperation
    {
        virtual double evaluate() const = 0;
    };

    struct IUnaryOperation : public IOperation
    {
        virtual double evaluate(double operand) const = 0;
    };

    struct IBinaryOperation : public IOperation
    {
        virtual double evaluate(double left, double right) const = 0;
    };
}

#endif /* INCLUDED_INCLUDE_IOPERATION_HPP */

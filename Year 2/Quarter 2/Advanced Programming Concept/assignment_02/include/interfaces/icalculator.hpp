#ifndef INCLUDED_INTERFACES_ICALCULATOR_HPP
#define INCLUDED_INTERFACES_ICALCULATOR_HPP
#include <string_view>
#include <optional>
#include <vector>
#include <memory>

#include "ioperation.hpp"
#include "iparser.hpp"


namespace sax
{
    struct ICalculator
    {
        virtual ~ICalculator() = default;

        // Evaluate an expression (throws std::domain_error on parse / semantic error)
        virtual double evaluate(std::string_view expression) const = 0;
        // Register an operation (dependency injection)
        virtual void add_operation(std::unique_ptr<IOperation> operation) = 0;
        // Remove all operations
        virtual void clear_operations() = 0;

        // Return list of supported operation symbols (for UI)
        virtual std::vector<std::string_view> supported_operations() const = 0;
        // Return help text entries for each operation  
        virtual std::vector<std::string_view> help() const = 0;
    };
}

#endif /* INCLUDED_INTERFACES_ICALCULATOR_HPP */

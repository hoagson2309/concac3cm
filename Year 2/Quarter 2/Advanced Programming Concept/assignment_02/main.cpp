#include "include/rpn/rpn.hpp"
#include "include/rpn/parser.hpp"
#include "include/rpn/operations.hpp"

#include <iostream>
#include <memory>
#include <string>

// TODO: Most of the work is in the files in include/rpn
// The directory include/interfaces already contains the implementations of all the interfaces


int main()
{
    using namespace sax;

    /* Create the calculator */

    // vvv won't work yet as RPNParser & RPNCalculator are not fully implemented

    auto parser = std::make_unique<RPNParser>();
    std::unique_ptr<ICalculator> calculator = std::make_unique<RPNCalculator>(std::move(parser));
   
    // TODO: Add operations to the calculator

    calculator->add_operation(make_operation(
        "+",
        "+: Addition - adds two numbers.",
        [](double a, double b) { return a + b; }
    ));

    calculator->add_operation(make_operation(
        "-",
        "-: Subtraction - subtracts two numbers.",
        [](double a, double b) { return a - b; }
    ));

    calculator->add_operation(make_operation(
        "*",
        "*: Multiplication - multiplies two numbers.",
        [](double a, double b) { return a * b; }
    ));

    calculator->add_operation(make_operation(
        "/",
        "/: Division - divides two numbers.",
        [](double a, double b) { return a / b; }
    ));

    calculator->add_operation(make_operation(
        "sqrt",
        "sqrt: Square root - calculates sqrt(operand)",
        [](double operand) { return std::sqrt(operand); }
    ));

    calculator->add_operation(make_operation(
        "exp",
        "exp: Exponentiation - calculates the exponent with the natural base e.",
        [](double operand) { return std::exp(operand); }
    ));

    calculator->add_operation(make_operation(
        "ln",
        "ln: Logarithm - calculates the natural logarithm of a number.",
        [](double operand) { return std::log(operand); }
    ));

    calculator->add_operation(make_operation(
        "pi",
        "pi: Returns the value of π.",
        []() { return std::numbers::pi_v<double>; }
    ));

    calculator->add_operation(make_operation(
        "e_constant",
        "e_constant: Returns the value of constant e.",
        []() { return std::numbers::e_v<double>; }
    ));

    // calculator->add_operation(std::make_unique<Addition>());
    // calculator->add_operation(std::make_unique<Subtraction>());
    // calculator->add_operation(std::make_unique<Multiplication>());
    // calculator->add_operation(std::make_unique<Division>());
    // calculator->add_operation(std::make_unique<Power>());
    // calculator->add_operation(std::make_unique<SqrtOp>());
    // calculator->add_operation(std::make_unique<ExpOp>());
    // calculator->add_operation(std::make_unique<LnOp>());
    // calculator->add_operation(std::make_unique<Pi>());
    // calculator->add_operation(std::make_unique<EConst>());

    std::cout << "RPN Calculator\n";
    std::cout << "Enter an RPN expression to evaluate.\n";
    std::cout << "Enter '(h)elp' for help.\n";
    std::cout << "Enter '(o)ps' for available operations.\n";
    std::cout << "Enter '(q)uit' to exit.\n";

    std::string expression{};
    while (true)
    {
        std::cout << "Enter RPN expression (or 'exit' to quit): ";
        std::getline(std::cin, expression);
        if (expression == "exit" || expression == "quit" || expression == "q")
        {
            break;
        }
        else if (expression == "help" || expression =="h" || expression == "?")
        {
            // TODO: Print help information
            std::cout << "Enter expressions using RPN notation, for instance to calculate:\n";
            std::cout << "2 + 3 * 4\n";
            std::cout << "enter '2 3 4 * +'\n";
            std::cout << "or enter '3 + 4 * 2 +'\n";

            // Print help text for all operations
            for (auto h : calculator->help())
                std::cout << h << "\n";

            continue;
        }

        else if (expression == "o" || expression == "ops")
        {
            std::cout << "Supported operations:\n";
            for (auto op : calculator->supported_operations()) //std::string_view symbol in operations.hpp
                std::cout << "  " << op << "\n";
            continue;
        }
        
        try
        {
            double result = calculator->evaluate(expression);
            std::cout << "Result: " << result << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        
    }
    return 0;
}

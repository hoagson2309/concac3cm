using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Security.Cryptography.X509Certificates;

namespace RPNCalculator.Core {
    public class RPNCalculator : ICalculator {
        public IList<string> SupportedOperators { get; } = new List<string> { "+", "-", "*", "/", "^", "sqrt", "exp", "ln"};
        public IList<string> OperationsHelpText { get; } = new List<string> {
            "+ - (Addition) adds two numbers",
            "- - (Subtraction) subtracts two numbers",
            "* - (Multiplication) multiplies two numbers",
            "/ - (Division) calculates the fraction of two numbers",
            "^ - (Power) calculates the power of two numbers",
            "sqrt - (SquareRoot) calculates the square root of a number",
            "exp - (Exponentiation) calculates the exponent with the natural base e",
            "ln - (Logarithm) calculates the natural logarithm of a number"
        };

        public double Calculate(IList<Token> expression) {
            var stack = new Stack<double>();
            foreach (var token in expression) {
                if(token.IsNumber) {
                    stack.Push(token.NumericValue);  //if token is a number push double numeric vlue of token to stack
                }
                else if(token.IsOperator) {
                    switch (token.Value) {
                        case "+":
                            if(stack.Count < 2) throw new InvalidOperationException("Not enough operands for '+'");
                            stack.Push(stack.Pop() + stack.Pop());
                            break;
                        case "-":
                            if(stack.Count < 2) throw new InvalidOperationException("Not enough operands for '-'");
                            double sub2 = stack.Pop();
                            double sub1 = stack.Pop();
                            stack.Push(sub1 - sub2);
                            break;
                        case "*":
                            if(stack.Count < 2) throw new InvalidOperationException("Not enough operands for '*'");
                            stack.Push(stack.Pop() * stack.Pop());
                            break;
                        case "/":
                            if(stack.Count < 2) throw new InvalidOperationException("Not enough operands for '/'");
                            double div2 = stack.Pop();
                            double div1 = stack.Pop();
                            if (div2 == 0) throw new DivideByZeroException("Division by zero");
                            stack.Push(div1 / div2);
                            break;
                        case "^":
                            if(stack.Count < 2) throw new InvalidOperationException("Not enough operands for '^'");
                            double exp2 = stack.Pop();
                            double exp1 = stack.Pop();
                            stack.Push(Math.Pow(exp1, exp2));
                            break;
                        case "sqrt":
                            if (stack.Count < 1) throw new InvalidOperationException("Not enough operands for 'sqrt'");
                            stack.Push(Math.Sqrt(stack.Pop()));
                            break;
                        case "exp":
                            if (stack.Count < 1) throw new InvalidOperationException("Not enough operands for 'exp'");
                            stack.Push(Math.Exp(stack.Pop()));
                            break;
                        case "ln":
                            if (stack.Count < 1) throw new InvalidOperationException("Not enough operands for 'ln'");
                            double lnVal = stack.Pop();
                            if(lnVal <= 0) throw new ArgumentException("ln(x) requires x > 0");
                            stack.Push(Math.Log(lnVal));
                            break;
                        default:
                            throw new FormatException($"Unsupported operator: {token.Value}");
                    }
                }
            }
            if(stack.Count != 1) {
                throw new InvalidOperationException("Invalid RPN expression: stack does not contain exactly one result.");
            }
            return stack.Pop();
        }
    }
}
using System;
using RPNCalculator.Core;
using System.Collections.Generic;

namespace RPNCalculator.Core
{
    public class Program
    {
        static void Main(string[] args)
        {
            // Create calculator
            ICalculator calculator = new RPNCalculator();

            // Create parser with dependency injection of supported operators
            IParser parser = new Parser(calculator.SupportedOperators);

            // Create menu with dependency injection of operations help text
            IMenu menu = new TextMenu(calculator.OperationsHelpText);

            // Create controller with DI
            var controller = new Controller(calculator, parser, menu);

            // Run the calculator
            controller.Run();
        }
    }
}

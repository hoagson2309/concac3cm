using System;
using System.Collections.Generic;

namespace RPNCalculator.Core {
    public class TextMenu : IMenu {
        public IList<string> OperationsHelp { get; set; }

        public TextMenu(IList<string> operationshelp) {   // later use in program.cs pass by calculator
            OperationsHelp = operationshelp ?? new List<string>();
        }
        public void ShowMenu() {
            Console.WriteLine("RPN Calculator");
            Console.WriteLine("Enter an RPN expression to evaluate.");
            Console.WriteLine("Enter '(h)elp' for help.");
            Console.WriteLine("Enter '(o)ps' for available operations.");
            Console.WriteLine("Enter '(q)uit' to exit.");
        }
        public void ShowOperations() {
            Console.WriteLine("Calculator operations:");
            foreach (var op in OperationsHelp) {
                Console.WriteLine(op);
            }
        }
        public void ShowHelp() {
            Console.WriteLine("Enter expressions using RPN notation, for instance to calculate:\n");
            Console.WriteLine("2 + 3 * 4");
            Console.WriteLine("enter '2 3 4 * +'");
            Console.WriteLine("enter (o)ps to see available operations");
        }
    }
}
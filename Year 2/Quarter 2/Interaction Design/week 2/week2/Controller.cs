using System;
using System.Collections.Generic;

namespace RPNCalculator.Core {
    public class Controller {
        public ICalculator Calculator { get; set; }
        public IParser Parsers { get; set; }
        public IMenu Menu { get; set; }

        public Controller(ICalculator calculator, IParser parser, IMenu menu) {
            Calculator = calculator ?? throw new ArgumentNullException(nameof(calculator));
            Parsers = parser ?? throw new ArgumentNullException(nameof(parser));
            Menu = menu ?? throw new ArgumentNullException(nameof(menu));
        }
        public void Run() {
            Menu.ShowMenu();
            string input;

            do {
                Console.Write("> ");
                input = Console.ReadLine() ?? "q";

                switch (input.Trim().ToLower()) {
                    case "q":
                        break;
                    case "h":
                        Menu.ShowHelp();
                        break;
                    case "o":
                        Menu.ShowOperations();
                    break;
                    default:
                    try {
                        var split = Parsers.Tokenize(input);
                        if (split.Count > 0) {
                            var tokens = Parsers.Lex(split);
                            var result = Calculator.Calculate(tokens);
                            Console.WriteLine($"\n{result}\n");
                        }
                    }
                    catch (Exception e) {
                        Console.WriteLine($"Error: {e.Message}");
                    }
                    break;
                }
            } while (input.Trim().ToLower() != "q");
                Console.WriteLine("\nCalculator is quitting. Bye!");
        }
    }
}
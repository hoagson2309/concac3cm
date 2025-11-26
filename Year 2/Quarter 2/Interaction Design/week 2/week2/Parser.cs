using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
namespace RPNCalculator.Core{
    public class Parser : IParser {
        public IList<string> SupportedOperators { get; set; }

        //public Parser() : this(new List<string>()) { } => no need
        public Parser(IList<string> supportedOperators) {  // later use in program.cs pass by calculator
            SupportedOperators = supportedOperators ?? new List<string>(); //if there's a list of supported operators => put to SupportedOperator otherwise create new list
        }

        // Split input string by whitespace into tokens
        public IList<string> Tokenize(string expression) {  //3 5 +
            if(string.IsNullOrEmpty(expression)) 
                return new List<string>();

            return expression.Split(' ', StringSplitOptions.RemoveEmptyEntries); //Split string into array 3,5,+

        }

        // Convert string tokens into Token objects (numbers or operators)
        public IList<Token> Lex(IList<string> tokens) {  //3,5,+
            var result = new List<Token>();

            foreach(var t in tokens) {
                if(double.TryParse(t, NumberStyles.Float, CultureInfo.InvariantCulture, out _)) { //if can parse t to double 
                    result.Add(new Token(TokenType.NUMBER, t));     // add t as new number to result
                } 
                else if (SupportedOperators.Contains(t)) { //if t is in SupportedOperators
                    result.Add(new Token(TokenType.OPERATOR, t));   // add t as new operator to result
                }
                else {
                    throw new FormatException($"Unsupported token: '{t}'");
                }
            }
            return result;
        }
    }
}
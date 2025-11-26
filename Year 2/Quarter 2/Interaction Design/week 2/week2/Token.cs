using System.Collections.Specialized;
using System.Globalization;
using System.Text.Json;

namespace RPNCalculator.Core{
    public enum TokenType {NUMBER, OPERATOR}
    public class Token {
        public TokenType TokenType { get; }
        public string Value { get; }
        public double NumericValue { get; }
        public bool IsOperator => TokenType == TokenType.OPERATOR;
        public bool IsNumber => TokenType == TokenType.NUMBER;

        public Token(TokenType tokenType, string text) {
            if (string.IsNullOrEmpty(text)) {
                throw new ArgumentNullException(nameof(text), "Token text cannot be null or whitespace.");
            }

            TokenType = tokenType;
            Value = text;

            if(tokenType == TokenType.NUMBER) {
                if(!double.TryParse(text, NumberStyles.Float, CultureInfo.InvariantCulture, out var value)) {
                    throw new FormatException($"Invalid numeric token: '{text}'");
                }
                NumericValue = value;
            } else {
                NumericValue = double.NaN;
            }
        }
        public override string ToString() => Value;
    }
}
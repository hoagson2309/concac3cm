using System.Security.Principal;
using System.Collections.Generic;

namespace RPNCalculator.Core{
    public interface IParser {
        IList<string> SupportedOperators { get; set; }
        IList<string> Tokenize(string expression);
        IList<Token> Lex(IList<string> tokens);
    }
}

using System.Collections.Generic;

namespace RPNCalculator.Core {
    public interface ICalculator {
        IList<string> SupportedOperators { get; }
        IList<string> OperationsHelpText { get; }
        double Calculate(IList<Token> expression);
    }    
}

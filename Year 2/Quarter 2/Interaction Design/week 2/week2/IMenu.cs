using System.Collections.Generic;

namespace RPNCalculator.Core {
    public interface IMenu {
        IList<string> OperationsHelp { get; set; }

        void ShowMenu();
        void ShowOperations();
        void ShowHelp();
     }
}
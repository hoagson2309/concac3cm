#include <iostream>
#include <stdexcept>
#include "date.h"
#include "utils.h"

int main() {
    try
    {
        bday_calendar::Date now{};
        std::cout << "Today is: " << now.str() << '\n';

        bday_calendar::Date from_string{"2023-02-28"};
        std::cout << "Parsed date is not validated: " << from_string.str() << '\n';

        bday_calendar::Date from_numbers{2023, 2, 29};
        std::cout << "This gets validated, so you will never see this message: " << from_numbers.str() << '\n';
    }
    catch(std::invalid_argument exarg)
    {
        std::cout << "Something wrong happend. This precisely:\n";
        std::cout << exarg.what() << '\n';
    }
    catch(std::logic_error exlog)
    {
        std::cout << "Logic error happend: " << exlog.what() << '\n';
    }
    catch(...) // catch-all
    {

    }
}

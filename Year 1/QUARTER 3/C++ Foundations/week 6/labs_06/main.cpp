#include "numbers.h"

int main()
{
    using namespace numeric;
    
    Numbers numbers1{};
    numbers1.push_back(3.14);
    numbers1.push_back(2.71);
    numbers1.push_back(1.61);

    Numbers numbers2{numbers1}; // copy constructor

    Numbers numbers3{};
    numbers3 = numbers1; // copy assignment operator

    numbers2.pop_back();
    numbers2.push_back(1.41);

    std::cout << numbers1 << '\n'; // prints Numbers {capacity: 16, size: 3}: [3.14, 2.71, 1.41]
    std::cout << numbers2 << '\n'; // prints Numbers {capacity: 16, size: 3}: [3.14, 2.71, 1.41] (yes!)
    std::cout << numbers3 << '\n'; // prints Numbers {capacity: 16, size: 3}: [3.14, 2.71, 1.41] (yes! again)
}
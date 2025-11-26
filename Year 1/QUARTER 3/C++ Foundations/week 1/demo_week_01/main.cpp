#include <iostream> // header with in/out stream
#include <fstream>  // file stream
#include <iomanip>  // nobody knows

namespace demo {
void demo_1()
{
    std::string name = "Alice";
    std::string animal{};
    auto how_many{42};

    std::cout << "What animals does " << name << " have?\n";

    if (std::getline(std::cin, animal))
    {
        if (!animal.ends_with("."))
        {
            animal = animal + ".";
        }
        std::cout << name << " has " << how_many << ' ' << animal << '\n';
    }
}

void demo_2()
{
    auto birth_year = 0;

    const auto now = 2025;

    while (birth_year < 1900 || birth_year > now){
        std::cout << "Hello, in which year were you born?\n";
        if (!(std::cin >> birth_year))
        {
            std::cin.clear();
            std::cin.ignore(1'000, '\n');
            std::cout << "You are not reading correctly, enter a number a number please!\n";
        }
        else if (birth_year < 1900 || birth_year > now)
        {
            // no input error but an invalid range
            std::cout << "Enter a valid year\n";
        }
    }

    std::cout << "You are " << now - birth_year << " years old!\n";
}

void demo_3(std::string file_name)
{
    // 1. open the file for reading and check if you managed
    // 2. read word-by-word trying to convert to ints
    // 2a. if converted, add up the number

    std::ifstream input{file_name};
    std::ofstream output{file_name + ".out"};

    if (input)
    {
        auto sum{0};
        while(!input.eof())
        {
            int number = 0;
            if (input >> number)
            {
                sum += number;
                if (output){
                    output << number << ' ';
                }
            }
            else
            {
                input.clear();
                std::string dummy;
                input >> dummy;
                if (output){
                    output << dummy << " ";
                }
            }
        }
        std::cout << "There are " << sum << " pieces of fruit.\n";
    }
}

void demo_4()
{

}

void demo_5()
{

}

}

int main()
{
    // demo::demo_1();
    // demo::demo_2();
    demo::demo_3("input.txt");
    demo::demo_4();
    demo::demo_5();
}

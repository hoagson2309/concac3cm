#include <iostream> // header with in/out stream
#include <fstream> // file stream

void demo_01()
{
    std::string name = "Alice";

//    name = name + std::to_string(5);

    name = name + " and Bob";

    std::cout << "Hello, " << name << "!\n"; // endl == '\n'

    std::cout << "Your name starts with: " << name.front() << '\n';

    std::cout << "You name is " << name.length() << " letters long.\n";
}

void demo_02()
{
    std::string name = "";
    int year_of_birth = 0;

    std::cout << "What is your name and year of birth?\n";

    std::cin >> name;

    std::cin >> year_of_birth;

    while (! std::cin.good())
    {
        std::cout << "You are a noob, " << name << "! Enter a valid integer!\n";
        std::cin.clear(); // clears all the errors in the stream

        std::string more_name;
        std::cin >> more_name;

        name = name + " " + more_name;

        std::cin >> year_of_birth;
    }

    std::cout << "Hello, " << name << ", you seem to be " << (2024 - year_of_birth) << " old.\n";
}

void demo_03()
{
    std::string name = "";
    int year_of_birth = 0;

    std::cout << "What is your name and year of birth?\n";

    std::cin >> name;

    while (! (std::cin >> year_of_birth ))  // as long as you cannot read an int from std::cin
    {
        std::cout << "You are a noob, " << name << "! Enter a valid integer!\n";
        std::cin.clear(); // clears all the errors in the stream

        std::cin.ignore(1000, ' ');

        std::string more_name;
        std::cin >> more_name;

        name = name + " " + more_name;
    }

    std::cout << "Hello, " << name << ", you seem to be " << (2024 - year_of_birth) << " old.\n";

}

void demo_04()
{
    std::ifstream input{ "input.txt" }; // opens a file "input.txt"

    if (input)
    {
        int sum = 0;

        while(!input.eof()) // eof == end of file
        {
            int number = 0;

            if (input >> number)
            {
                sum += number;
            }
            else
            {
                input.clear();
                std::string dummy;
                input >> dummy;
            }
        }

        std::cout << "There are " << sum << " fruits in total.\n";
    }
    else
    {
        std::cout << "The file doesn't exist!\n";
    }
}

void demo_05()
{
    std::ifstream input{ "input.txt" }; // opens a file "input.txt"

    if (input)
    {
        int sum = 0;
        int c;

        while(!input.eof())
        {
            c = input.get();    // read a single character
            if (c == '\n')
            {
                ++sum;
            }
        }

        std::cout << "There are " << sum << " lines in total.\n";
    }
    else
    {
        std::cout << "The file doesn't exist!\n";
    }
}

int main()
{
    std::ifstream input{"input.txt"};

    std::ofstream output{"input.out"};

    if (input && output)
    {

        /*
        // That's not the best approach - we ignore all the newlines;(
        // Perhaps use something like:

        std::string line;
        while(std::getline(input, line))
        {
            // now I have a full line in the `line` variable

            // Let's make an input string stream out of it...

        }
        */


        std::string word = "";

        while(input >> word)
        {
            output << word << ' ';
        }
    }

    return 0;
}

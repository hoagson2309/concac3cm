#include <iostream>
#include "options.h"

void Options::parse(int argc, const char** argv)
{
    int i = 1;
    while(true)
    {
        std::string arg = argv[i];

        if (arg == "-i") {
            ignore_case = true;
            i++;
        }
        else if (arg == "-c") {
            color = true;
            i++;
        }
        else
        {
            // we must break out of the loop here
            // if the pattern begins with  "-"
            break;
        }
    }

    pattern = argv[i++];

    for (; i< argc; ++i)
    {
        files.push_back(argv[i]);
    }
}

void Options::print() const
{
    std::cout << "==DEBUG OPTIONS==\n";
    std::cout << "Color: " << color << '\n';
    std::cout << "Ignore case: " << ignore_case << '\n';
    std::cout << "Files: \n";
    for (auto file : files)
    {
        std::cout << file << " ";
    }
    std::cout << "\n==END OF DEBUG OPTIONS==\n";
}
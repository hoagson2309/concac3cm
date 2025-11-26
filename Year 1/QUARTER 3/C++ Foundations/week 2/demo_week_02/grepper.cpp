#include <fstream>
#include <iostream>

#include "grepper.h"

void Grepper::set_options(std::string pat, bool c, bool ic)
{
    pattern = pat;
    color = c;
    ignore_case = ic;
}

/// @brief Converts a string to lower case
std::string to_lower(std::string str)
{
    for (auto& c : str)
        c = static_cast<char>(std::tolower(c & 0xff));
    return str;
}

void Grepper::process(std::string file_name) const
{
    if ( std::ifstream input{file_name} ; input.is_open())
    {
        // if we ignore case, turn the pattern into lower case, otherwise don't
        std::string pattern_copy = ignore_case ? to_lower(pattern) : pattern;

        std::string line;
        while(std::getline(input, line)) {
            // if we ignore case, just turn the whole line into lower case, otherwise don't
            auto line_copy = ignore_case ? to_lower(line) : line;

            // try to find the position of the pattern in the line
            auto pos = line_copy.find(pattern_copy);
            if (pos != std::string::npos) {

                // we always print the original, not the (possibly) lower-case copy!
                if (color)
                {
                    // for color printing we use https://en.wikipedia.org/wiki/ANSI_escape_code
                    // TODO: try to analyze and understand how this code works
                    auto last = 0ul;
                    while (pos != std::string::npos)
                    {
                        std::cout << line.substr(last, pos-last);
                        std::cout << "\033[1;31m" << line.substr(pos, pattern.length()) << "\033[0m";
                        last = pos + pattern.size();
                        pos = line_copy.find(pattern_copy, last);
                    }
                    std::cout << line.substr(last) << std::endl;
                }
                else
                {
                    std::cout << line << '\n';
                }
            }
        }
    }
    else
    {
        std::cerr << "Error opening file " << file_name << '\n';
    }
}

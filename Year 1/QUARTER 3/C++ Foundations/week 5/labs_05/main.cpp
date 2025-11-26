#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "word_counter.h"


std::string to_lower(const std::string& str)
{
    std::string result{ str };
    for (auto& c : result)
    {
        c = static_cast<char>( std::tolower(c & 0xff) );
    }
    return result;
}

std::string lr_strip(const std::string& str, const std::string& chars)
{
    auto first = str.find_first_not_of(chars);
    if (first == std::string::npos)
    {
        return "";
    }
    auto last = str.find_last_not_of(chars);
    return str.substr(first, last - first + 1);
}

std::string lr_strip_all(const std::string& str)
{
    return lr_strip(str, ".,:;!?\"'_-()*[]{}<>|/\\ \t\n\v\f\r");
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    if (std::ifstream file{ argv[1] })
    {
        counts::WordCounter counter{};
        std::string word;
        while (file >> word)
        {
            if (word = lr_strip_all(to_lower(word)); !word.empty())
            {
                counter.increment(word);
            }
        }

        std::sort(counter.begin(), counter.end(),
            [](const auto& a, const auto& b)
            {
                return a.count > b.count;
            });

        auto i = 25;
        for (const auto& [word, count] : counter)
        {
            std::cout << word << ": " << count << std::endl;
            if (--i == 0)
            {
                break;
            }
        }
    }
    else
    {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }
} // Destructor is called here when `counter` goes out of scope
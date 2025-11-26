#include "NumberFinder.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace exam
{
    NumberFinder::NumberFinder(bool unique, bool sorted) :
        unique_{unique},
        sorted_{sorted}
    {}

    bool NumberFinder::find(const std::string& file_name)
    {
        std::ifstream input{file_name};
        if (!input)
        {
            throw std::invalid_argument("File doesn't exist");
        }

        /* And this is an easier way */
        auto found{false};
        std::string word{};
        while(input >> word)
        {
            // Where to start the check? (from index 1 if the first symbol is '-')
            auto check_from = word.front() == '-' ? 1 : 0;
            if (word.find_first_not_of("0123456789", check_from) == std::string::npos)
            {
                add_unique( std::stoi(word) );
                found = true;
            }
        }

        if (sorted_)
        {
            std::sort(numbers_.begin(), numbers_.end());
        }

        return found;
    }

    const std::vector<long>& NumberFinder::numbers() const
    {
        return numbers_;
    }

    void NumberFinder::add_unique(long number)
    {
        if (!unique_)
        {
            numbers_.push_back(number);
        }
        else {
            for (auto n: numbers_) {
                if (n == number) {
                    // nothing to do
                    return;
                }
            }
            numbers_.push_back(number);
        }
    }
}

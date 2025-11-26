#ifndef INCLUDED_NUMBER_FINDER_H
#define INCLUDED_NUMBER_FINDER_H

#include <vector>
#include <string>

#include "Options.h"

namespace exam
{
    class NumberFinder
    {
    public:
        NumberFinder(bool unique, bool sorted);
        bool find(const std::string& file_name);
        const std::vector<long>& numbers() const;
    private:
        void add_unique(long number);
        bool unique_;
        bool sorted_;
        std::vector<long> numbers_;
    };
}


#endif // INCLUDED_NUMBER_FINDER_H
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
        const std::vector<long>& numbers() const;
        bool find(const std::string& file_name);

    private:
        [[maybe_unused]]
        bool unique_;
        [[maybe_unused]]
        bool sorted_;
        std::vector<long> numbers_;
        
        bool IsInteger(const std::string& word);
        void processNumber(long number);
    };
    
    
}


#endif // INCLUDED_NUMBER_FINDER_H
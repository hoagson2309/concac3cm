#ifndef INCLUDED_OPTIONS_H
#define INCLUDED_OPTIONS_H

#include <vector>
#include <string>
#include <iostream>

namespace exam
{
    struct Options
    {
        bool unique_values;
        bool sorted;
        bool help;
        std::vector<std::string> files;
    };

    Options parse_options(int argc, char* argv[]);

    std::ostream& operator<<(std::ostream& os, const Options& options);
}

#endif // INCLUDED_OPTIONS_H
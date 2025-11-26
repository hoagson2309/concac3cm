#include "Options.h"

#include <iostream>
#include <iomanip>
#include <algorithm>


exam::Options exam::parse_options(int argc, char* argv[])
{
    Options options;
    for(int i = 1; i < argc; i++){
        std::string arg = argv[i];
        if( arg == "-h" || arg == "--help"){
            options.help = true;
            return options;
        } 

        if(arg[0] == '-'){
            if(arg[1] != '-'){
                for(size_t j = 1; i < arg.size(); j++){
                    switch (arg[j]){
                    case 'u': options.unique_values = true; break;
                    case 's': options.sorted = true; break;
                    }
                }
            } else {
                if(arg == "--unique") options.unique_values = true;
                else if(arg == "--sorted") options.sorted = true;
            } 
        } else {
            //it's a file name
            options.files.push_back(arg);  //????
        }
    }
    return options;
}

std::ostream& exam::operator<<(std::ostream& os, const exam::Options& options)
{
    os << "Options:\n";
    os << "  unique_values: " << std::boolalpha << options.unique_values << '\n';
    os << "  sorted: " << std::boolalpha << options.sorted << '\n';
    os << "  help: " << std::boolalpha << options.help << '\n';
    os << "  files:\n";
    for (const auto& file : options.files)
    {
        os << "    " << file << '\n';
    }
    return os;
}
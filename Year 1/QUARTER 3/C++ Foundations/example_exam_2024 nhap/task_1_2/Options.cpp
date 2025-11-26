#include "Options.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>


exam::Options exam::parse_options(int argc, char* argv[])
{
    if(argc < 2){
        throw std::invalid_argument("This program expects a file name as argument");
    }
    Options opts;
    for (int i = 1; i < argc; i++){
        std::string arg = argv[i];
        if(arg == "--help") opts.help = true;
        else if(arg == "--sorted") opts.sorted = true;
        else if(arg == "--unique") opts.unique_values = true;  
       
        if(arg[0] == '-'){  
                if(arg[1] != '-'){
                    for(size_t j = 1; j < arg.size(); j++){
                        switch (arg[j]) {
                            case 'u': opts.unique_values = true; break;
                            case 'h': opts.help = true; break;
                            case 's': opts.sorted = true; break;
                            default: throw std::invalid_argument("Unrecognized short flag..");
                    }
                }
            } 
                
             
        } else {
            opts.files.push_back(arg);
        }
    }
    return opts;
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
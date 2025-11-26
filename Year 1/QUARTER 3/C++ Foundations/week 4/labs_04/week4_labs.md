# Week 3 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 4/3/2025

# LABS
```cpp
//OPTIONS.CPP
#include "options.h"
#include <stdexcept>

namespace repeat
{
// TODO: implement this function and return the actual, parsed options
Options parse(int argc, char * argv[])
{
    Options result;

    for(int i = 1; i < argc; ++i){
        // convert argv[i] to string
        std::string arg{ argv[i] };

        //handle flags
        if( arg == "-h" || arg == "--help"){
            result.help = true;
        } else if ( arg == "-C" || arg == "--capitalize"){
            result.capitalize = true;
        } else if ( arg == "-n" || arg == "--newline"){
            result.append_newline = true;
        }


        //handle combined short flags (e.g., -Cn) and short options (-cred, -cblue)
        else if( arg[0] == '-' && arg[1] != '-' && arg.length() > 1){
            for(size_t j = 1; j < arg.length(); ++j){
                switch( arg[j] ){
                    case 'h':
                        result.help = true;
                        break;
                    case 'C':
                        result.capitalize = true;
                        break;
                    case 'n':
                        result.append_newline = true;
                        break;
                    case 'r':
                        // Handle -r flag (repeat)
                        if (j + 1 < arg.length()) {
                            std::string repeatValue = arg.substr(j + 1);
                            try {
                                result.repeat = std::stoi(repeatValue);
                                if (result.repeat < -1) {
                                    throw std::invalid_argument("Repeat value must be -1 or greater.");
                                }
                            } catch (const std::invalid_argument&) {
                                throw std::invalid_argument("Invalid repeat value: " + repeatValue);
                            }
                            j = arg.length(); // Skip the rest of the flags
                        } else {
                            throw std::invalid_argument("Missing repeat value for -r flag.");
                        }
                        break;
                    case 'c':
                        // Handle -c flag (color)
                        if (j + 1 < arg.length()) {
                            std::string colorValue = arg.substr(j + 1);
                            try {
                                result.color = from_string(colorValue);
                            } catch (const std::invalid_argument&) {
                                throw std::invalid_argument("Invalid color value: " + colorValue);
                            }
                            j = arg.length(); // Skip the rest of the flags
                        } else {
                            throw std::invalid_argument("Missing color value for -c flag.");
                        }
                        break;
                    default:
                        throw std::invalid_argument("Unknown short flag: -" + std::string(1, arg[j]));
                }
            }
        }


        //handle long options
        else if (arg.substr (0, 9) == "--repeat="){
            std::string repeatValue = arg.substr(9);
            try{  //try: Used to wrap a block of code that might throw an exception.If an exception is thrown inside the try block, the program jumps to the corresponding catch block.
                result.repeat = std::stoi(repeatValue);
                if(result.repeat < -1){  //if error
                    throw std::invalid_argument("Repeat value must be -1 or greater.");
                }
            }               
            catch (const std::invalid_argument&){         //Used to handle the exception thrown by the try block. You can specify the type of exception you want to catch (e.g., std::exception, std::invalid_argument, etc.).
                throw std::invalid_argument("Invalid repeat value: " + repeatValue);
            }
        } else if ( arg.substr(0, 8) == "--color="){
            std::string colorValue = arg.substr(8);
            try{
                result.color = from_string(colorValue);
            }
            catch (const std::invalid_argument&){
                throw std::invalid_argument("Invalid color value: " + colorValue);
            }
        }

        //handle positional argument
        else if( arg[0] != '-') {
            result.text = arg;
        } else{
            throw std::invalid_argument("unknown argument: " + arg);
        }
    }
    return result;
}

Color from_string(const std::string& text)
{
    if (text == "red")
    {
        return Color::red;
    }
    else if (text == "green")
    {
        return Color::green;
    }
    else if (text == "blue")
    {
        return Color::blue;
    }
    else if (text == "none")
    {
        return Color::none;
    }
    else
    {
        throw std::invalid_argument{"Invalid color"};
    }
}

std::ostream& operator<<(std::ostream& out, Color color)
{
    switch(color)
    {
        case Color::red:
            return out << "red";
        case Color::green:
            return out << "green";
        case Color::blue:
            return out << "blue";
        case Color::none:
            return out << "none";
        default:
            return out << "unknown";
    }
}

std::ostream& operator<<(std::ostream& out, Options const& options)
{
    out << "Options:\n";
    out << "  help: " << std::boolalpha << options.help << '\n';
    out << "  capitalize: " << std::boolalpha << options.capitalize << '\n';
    out << "  append_newline: " << std::boolalpha << options.append_newline << '\n';
    out << "  color: " << options.color << '\n';
    out << "  repeat: " << options.repeat << '\n';
    out << "  text: " << options.text << '\n';
    return out;
}
    
} // namespace repeat
```
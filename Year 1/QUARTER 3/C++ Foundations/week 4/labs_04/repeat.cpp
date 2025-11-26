#include "repeat.h"

namespace repeat
{

std::string to_upper(const std::string& text)
{
    std::string result{ text };
    for (auto& c : result)
    {
        c = static_cast<char>( std::toupper(c & 0xff) );
    }
    return result;
}

std::string decorate(const std::string& text, const Options& opt)
{
    if (opt.append_newline)
    {
        return text + '\n';
    }
    return text;
}


void set_term_text_color(Color color)
{
    switch(color)
    {
        case Color::red:
            std::cout << "\033[31m";
            break;
        case Color::green:
            std::cout << "\033[32m";
            break;
        case Color::blue:
            std::cout << "\033[34m";
            break;
        case Color::none:
            std::cout << "\033[0m";
            break;
        default:
            break;
    }
}

}
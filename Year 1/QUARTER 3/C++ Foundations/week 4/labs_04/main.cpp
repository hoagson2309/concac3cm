#include <iostream>

#include "options.h"
#include "repeat.h"

static auto help_text = 
        "Prints text to the terminal, possibly in color and infinitely many times.\n\n"
        "Usage: repeat [options] text\n"
        "Options:\n"
        "  -h, --help            Show this help message and exit\n"
        "  -C, --capitalize      Capitalize the text\n"
        "  -n, --newline         Append a newline to the text\n"
        "  -r  --repeat=NUM      Repeat the text NUM times (-1 repeats infinitely) \n"
        "  -c  --color=COLOR     Color the text (red, green, blue, none, default is none)\n";

int main(int argc, char * argv[])
{

    /*
     * TODO The `parse` function is located in options.cpp
     */

    using namespace repeat;

    // parse the command line arguments
    auto options = parse(argc, argv);

    // This is for debugging only, set the condition to false when you are done
    if (true)
    {
        std::cout << options << '\n';
    }

    // print help if needed
    if (options.help)
    {
        std::cout << help_text;
        return 0;
    }

    if (options.text.empty())
    {
        std::cerr << "Error: no text to print\n";
        return 1;
    }

    if (options.capitalize)
    {
        options.text = to_upper(options.text);
    }

    options.text = decorate(options.text, options);

    set_term_text_color(options.color);

    if (options.repeat == -1)
    {
        while (true)
        {
            std::cout << options.text;
        }
    }
    else
    {
        while (options.repeat-- > 0)
        {
            std::cout << options.text;
        }
    }

    // restore color
    set_term_text_color(Color::none);

    return 0;

}












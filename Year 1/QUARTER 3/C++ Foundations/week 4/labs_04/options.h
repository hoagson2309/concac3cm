#ifndef INCLUDED_OPTIONS_H
#define INCLUDED_OPTIONS_H

#include <string>
#include <iostream>

namespace repeat
{

/// Enum for the color of the text
enum struct Color { none, red, green, blue };

/// For easily printing the color to a stream
std::ostream& operator<<(std::ostream& out, Color color);

// Parses the color from a string
Color from_string(const std::string& text);


/// Struct to hold all the options
struct Options
{
    bool help{false};           // Show help message and exit (default is false)
    bool capitalize{false};     // Capitalize the text if true (default is false)
    bool append_newline{true};  // Append a newline to the text if true (default is true)
    Color color{Color::none};   // Color the text (default is Color::none)
    int repeat{-1};             // Repeat the text NUM times (-1 repeats infinitely) (default is -1)
    std::string text{};         // The text to print (default is empty)
};

/// Stream output for Options
std::ostream& operator<<(std::ostream& out, Options const& options);

/// Parses the command line arguments and returns the options
Options parse(int argc, char * argv[]);

}

#endif // INCLUDED_OPTIONS_H
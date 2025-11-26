#ifndef INCLUDED_REPEAT_H
#define INCLUDED_REPEAT_H

#include <string>
#include "options.h"

namespace repeat
{

/// Convert a string to upper case
std::string to_upper(const std::string& text);

/// Decorates the string according to options
std::string decorate(const std::string& text, const Options& opt);

/// Sets terminal output color
void set_term_text_color(Color color);

}

#endif // INCLUDED_REPEAT_H
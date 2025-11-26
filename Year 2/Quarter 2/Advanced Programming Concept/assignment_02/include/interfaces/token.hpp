#ifndef INCLUDED_INTERFACES_TOKEN_HPP
#define INCLUDED_INTERFACES_TOKEN_HPP

#include <string>

namespace sax
{
    struct Token
    {
        enum struct TokenType
        {
            Number,
            Operation,
            Unknown
        };

        TokenType type;
        std::string value;
        double number_value = 0.0;
    };

} // namespace sax


#endif /* INCLUDED_INTERFACES_TOKEN_HPP */

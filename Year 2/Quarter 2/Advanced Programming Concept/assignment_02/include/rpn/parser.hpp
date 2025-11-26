#ifndef INCLUDED_PARSER_HPP
#define INCLUDED_PARSER_HPP

#include "../interfaces/iparser.hpp"

#include <string>
#include <sstream>
#include <charconv>
#include <cctype>
#include <stdexcept>

//"3 5 + sqrt"

namespace sax
{
    struct RPNParser : public IParser
    {
        RPNParser() = default;

        // TODO: Implement the IParser interface
        TokenStream parse(std::string_view expression) const override {
            TokenStream tokens;
            std::string token;  
            std::string ex(expression); //std::string_view cannot be streamed directly => convert to normal std::string
            std::istringstream iss(ex); 

            while(iss >> token){
                Token t;
                t.value = token;
                
                try{
                    size_t idx = 0;
                    double v = std::stod(token, &idx); //convert token into double 
                    if(idx == token.size()){
                        t.type = Token::TokenType::Number;
                        t.number_value = v; //return 3.0 for example
                    } else {
                        t.type = Token::TokenType::Operation;
                    }
                } catch (...){ //catch std::invalid_argument and std::out_of_range from std::stod
                    t.type = Token::TokenType::Operation;
                } 
                tokens.push_back(std::move(t));        
            }
            return tokens;
        }
    };
}      

#endif /* INCLUDED_PARSER_HPP */

//std::stod("3x", &idx);
//parses 3 as a valid number 
//=> idx = 1
//x is not a number
//check idx == token.size() => 1 == 2 => unmatch => the entire token was not a valid number
//=> treat as operation

//std::stod throw exception when seeing invalid argument at first std::stod("abc"); std::stod("e10"); std::stod("+"); 
//std::stod("3x", &idx); is still valid it'll stop at x

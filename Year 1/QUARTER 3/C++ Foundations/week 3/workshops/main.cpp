#include "rational_calc.h"
#include <iostream>

int main(int argc, char* argv[]){
    if(argc > 1){
        std::string filename = argv[1];
        if(!process(filename)){
            std::cerr << "Error processing file: " << filename << std::endl;
            return 1;
        }
    } else {
        std::string expr;
        while(std::getline(std::cin, expr)){
            Rational result = calculate(expr);
            std::cout << result.str() << std::endl;
        }
    }
    
    return 0;
}
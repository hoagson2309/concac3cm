#include "rational_calc.h"
#include <fstream>
#include <sstream>
#include <iostream>

Rational calculate(const std::string& expr){ //free function
    std::istringstream iss(expr); //This makes it easy to extract data
    std::string part1, op, part2;
    
    //check if the expression starts with "sqrt"
    if(expr.substr(0, 4) == "sqrt"){
        std::string sqrtArg = expr.substr(5); // extract the argument after "sqrt" and a space
        Rational r(sqrtArg);
        return r.sqrt();
    }

    //otherwis, parse the expression into two numbers and an operator
    iss >> part1 >> op >> part2;

    Rational a(part1);
    Rational b(part2);

    //perform the operation based on the operator
    if (op == "+") return a.add(b);
    if (op == "-") return a.sub(b);
    if (op == "*") return a.mul(b);
    if (op == "/") return a.div(b);
    if (op == "^") return a.pow(std::stoi(part2));
    if (op == "sqrt") return a.sqrt();

    //if the operator is invalid, return NaN
    return Rational(0, 0); //NaN
}

bool process(const std::string& file_name){
    std::ifstream infile(file_name);
    if(!infile) return false;

    std::ofstream outfile(file_name + ".out");
    if(!outfile) return false;

    std::string line;
    while (std::getline(infile, line)){
        Rational result = calculate(line);
        outfile << result.str() << std::endl;
    }
    return true;
}
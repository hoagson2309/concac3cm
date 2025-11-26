#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

//recursive evaluator
int eval(std::istringstream& in){
    //ignore whitespaces
    //peek(): look at the next character without consuming it
    //get(): to consume
    //(1+2) and ( 1 + 2 ) both work
    while(in.peek() == ' ') in.get();

    //case 1: integer
    if(std::isdigit(in.peek())){
        int value;
        in >> value;
        return value;
    }

    //case 2: parenthesized expression
    if(in.peek() == '('){
        in.get(); //consume '('

        int left = eval(in);    
        //skip spaces
        while(in.peek() == ' ') in.get();

        char op;
        in >> op; //read operator

        int right = eval(in);

        //skip spaces
        while(in.peek() == ' ') in.get();

        if(in.get() != ')') throw std::runtime_error("Missing closing parenthesis");
    

        //apply operator 
        switch(op){
            case '+': return left + right;
            case '*': return left * right;
            case '%': 
                if (right == 0) throw std::runtime_error("Modulo by zero");
                return left % right;
            default:
                throw std::runtime_error("Invalid operator");
        }
    }
    throw std::runtime_error("Invalid expression");
}
int main() {
    /* TODO:
        Write a program that reads an expression that consists of positive integers, parentheses, and
        the operators +, * and % (modulo) from standard input, and evaluates the expression.

        On each side of an operator you will either find an integer or a parenthesized expression,
        so there is no need to consider operator precedence.

        Example input: ((1 + 2) * (3 + 4)) % 11
        Example output: 10

        Hint: Create a stringstream from the input line, and pass it to a recursive function
        that evaluates the expression and returns the result.
    */
    std::string line;
    while(std::getline(std::cin, line)){
        if(line.empty()) continue;  //continue: skip this iteration, start the loop again
        try{
            std::istringstream in(line);
            int result = eval(in);
            std::cout << result << std::endl;
        } catch (const std::exception& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}

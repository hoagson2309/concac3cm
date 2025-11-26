#ifndef INCLUDED_CALCULATOR_RPN_HPP
#define INCLUDED_CALCULATOR_RPN_HPP

#include <string_view>
#include <vector>
#include <memory>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <stack>
#include <stdexcept>

#include "../interfaces/icalculator.hpp"
#include "../interfaces/iparser.hpp"
#include "../interfaces/ioperation.hpp"

namespace sax
{
    class RPNCalculator : public ICalculator
    {
        public:
            RPNCalculator(std::unique_ptr<IParser> parser) : parser_(std::move(parser)) {
                 if(!parser_) throw std::invalid_argument("Parser must not be null");
            }

            double evaluate(std::string_view expression) const override{
                //parse -> tokens
                TokenStream tokens = parser_->parse(expression);  
                std::vector<double> stack;
                
                for(const auto &t : tokens){ //traverse each Token t in TokenStream tokens
                    if(t.type == Token::TokenType::Number){
                        stack.push_back(t.number_value);  //push num
                        continue;
                    } else if (t.type == Token::TokenType::Operation){
                        //find operation by symbol
                        IOperation* op = find_operation(t.value); //get match symbol(operator)
                        if(!op){
                            throw std::domain_error("Unknown operation: " + std::string(t.value));
                        }
                        //try nullary (pi, e_constant)
                        if(auto nop = dynamic_cast<INullaryOperation*>(op)){
                            double res = nop->evaluate(); //start calculating in operation
                            stack.push_back(res);
                            continue;
                        }

                        //try unary
                        if(auto uop = dynamic_cast<IUnaryOperation*>(op)){
                            //must have 1 operand
                            if(stack.size() < 1) throw std::domain_error("Not enough operands for unary operation");
                            double operand = stack.back();
                            stack.pop_back();
                            double res = uop->evaluate(operand); //start calculating in operation
                            stack.push_back(res);
                            continue;
                        }

                        //try binary
                        if(auto bop = dynamic_cast<IBinaryOperation*>(op)){
                            //must have 2 left and right
                            if(stack.size() < 2) throw std::domain_error("Not enough operands for binary operation");
                            double right = stack.back();
                            stack.pop_back();
                            double left = stack.back();
                            stack.pop_back();
                            double res = bop->evaluate(left, right); //start calculating in operation
                            stack.push_back(res);
                            continue;
                        }
                        throw std::domain_error("Operation has unsupported arity");
                    }
                }
                if(stack.size() != 1) throw std::domain_error("Expression did not reduce to single value");
                return stack.back();
            }

            void add_operation(std::unique_ptr<IOperation> operation) override {
                if (!operation) throw std::invalid_argument("operation must not be null");
                operations_.push_back(std::move(operation));
            }

            void clear_operations() override{
                operations_.clear();
            }

            std::vector<std::string_view> supported_operations() const override {
                std::vector<std::string_view> res;
                res.reserve(operations_.size());
                for (const auto &op : operations_) res.push_back(op->symbol());
                return res;
            }

            std::vector<std::string_view> help() const override {
                std::vector<std::string_view> res;
                res.reserve(operations_.size());
                for (const auto &op : operations_) res.push_back(op->help());
                return res;
            }


        private:
            std::unique_ptr<IParser> parser_;
            std::vector<std::unique_ptr<IOperation>> operations_;

            IOperation* find_operation(std::string_view symbol) const{ //symbol = t.value (if it's operation)
                for(const auto &op : operations_){
                    if(op->symbol() == symbol)
                    return op.get(); //if match the operation in IOperation => get
                }
                return nullptr;
            }
    };
}

#endif /* INCLUDED_CALCULATOR_RPN_HPP */

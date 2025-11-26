#include "NumberFinder.h"
#include <sstream>
#include <fstream>  
#include <algorithm>
#include <cctype>

namespace exam{
    
    NumberFinder::NumberFinder(bool unique, bool sorted) : unique_(unique), sorted_(sorted) {}

    const std::vector<long>& NumberFinder::numbers() const{
        return numbers_;
    }

    bool NumberFinder::find(const std::string& file_name){
        std::ifstream file(file_name);
        if(!file){
            throw std::invalid_argument("file doesn't exist");
        }
        std::string line;
        bool found_any = false;
        while(std::getline(file, line)){
            std::istringstream iss(line);
            std::string word;
            
            while(iss >> word){
                if(IsInteger(word)){
                    long num = std::stol(word); //convert string to long
                    processNumber(num);
                    found_any = true;             
                }
            }
        }
        return found_any;
    }
    void NumberFinder::processNumber(long number){
        if(unique_){
            if(std::find(numbers_.begin(), numbers_.end(), number) != numbers_.end()){
                return;
            }
        }
        numbers_.push_back(number);
        if(sorted_){
            std::sort(numbers_.begin(), numbers_.end());
        }
    }

    bool NumberFinder::IsInteger(const std::string& str){
        if(str.empty()) return false;

        size_t start = 0;
        if(str[0] == '-'){
            if(str.length() == 1) return false;
            start = 1;
        }

        for(size_t i = start; i < str.length(); i++){
            if(!isdigit(str[i])) return false;
        }
        return true;
    }
}

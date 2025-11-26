//*
// @file:   buggy.cpp
// @brief:  A buggy program to debug
// @note:  Compile with -ggdb3 -O0 -fno-omit-frame-pointer
//         E.g.: g++ -ggdb3 -O0 -fno-omit-frame-pointer -o buggy.a buggy.cpp 
//*

#include <iostream>
#include <string>
#include <memory>
#include <charconv>
#include <cstring>

struct Words {
    int count;
    std::string * data;
};

/// @brief Print words in reverse order
/// @param words words to print
void print_words(const Words& words){    
    for (auto i = words.count ; i > 0; i--){
        std::cout << words.data[i] << '\n';
    }
}

int main(int argc, char * argv[]){

    int count;
    auto [ptr, ec] = std::from_chars(argv[1], argv[1] + strlen(argv[1]), count);
  
    Words words = {
                    .count = count, 
                    .data = new std::string[count]{}
                };

    for (auto i = 0; i < count; i++){
        std::cout << "Enter word " << (i + 1) << ": ";
        std::cin >> words.data[i];
    }

    print_words(words);
}
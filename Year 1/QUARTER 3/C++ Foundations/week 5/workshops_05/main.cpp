#include "OutputFile.h"
#include <iostream>

int main(){
    io::OutputFile fw{"test.txt"};
    if(fw.is_open()){
        fw << "Alice has " << 3 << " rats.\n";

        std::cout << "Written " << fw.size() << " chars and " << fw.lines() << " line.\n";

        fw << "True or false: does Alice like rats?\n" << "Answer: " << true << "\n";

        std::cout << "Written " << fw.size() << " chars and " << fw.lines() << " line.\n";
    } else{
        std::cerr << "False to open file!\n";
    }

    return 0;
}
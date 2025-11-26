#include <iostream>
#include <filesystem>
#include "options.h"
#include "grepper.h"
#include <fstream>
#include <sstream>

void read(std::string fname){
    
    if(std::ifstream input{fname}){
        // std::string line{};
        // while(std::getline(input, line)){
        //     auto pos = line.find_first_of(":");
        //     if(pos != std::string::npos){
        //         auto first = line.substr(0, pos);
        //         auto second = line.substr(pos);

        //         std::cout << '[' << first << "] [" << second << "]\n"
        std::string first{}, second{};
        while(std::getline(input, first, ':') && std::getline(input, second)){
            auto pos = first.find_last_not_of(" ");

        }
    }
        }

int main__(){
    read("data.in");
}
//greppy -i --ignore-case pattern file_name

int main(int argc, const char* argv[]) {

    Options ops{};
    if(ops.parse(argc, argv)){
        Grepper grep{};
        grep.process(ops);
    }
    else{
        std::cerr << "U moron";
    }

//     if (argc == 1)
//     {
//         std::cout <<
//         R"(
//         greppy version 0.1, (c) Alice & Bob 2024;)
//         A very limited grep implementation.

//         Usage:
//         greppy [options] pattern file0 file1 ... filen

//         Options:
//         -c                  Print matches in color
//         -i                  Ignore case

//         pattern             A text pattern to search. No regex support.

//         file0 file1 ...     Files to search fot he pattern.
//         )";
//         return EXIT_SUCCESS;
//     }


//     Options ops{};
//     ops.parse(argc, argv);

// //    ops.print();

//     Grepper grep{};
//     grep.set_options(ops.pattern, ops.color, ops.ignore_case);

//     for (auto file : ops.files)
//     {
//         grep.process(file);
//     }

//     return EXIT_FAILURE;
}

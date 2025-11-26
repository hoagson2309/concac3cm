#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <iomanip>  
#include <algorithm>
#include <string.h> 

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cerr << "No argument count\n";
        return 0;
    }

    int single_dash_count = 0;
    int double_dash_count = 0;
    int no_dash_count = 0;

    for(int i = 1; i < argc; i++){
        std::string arg = argv[i];
        if(arg.front() == '-' && !arg.starts_with("--")){
            std::cout << arg << "\n";
            single_dash_count++;
        }
    }
    
    for(int i = 1; i < argc; i++){
        std::string arg = argv[i];
        if(arg.starts_with("--")){
            std::cout << argv[i] << "\n";
            double_dash_count++;
        }
    }

    for(int i = 1; i < argc; i++){
        std::string arg = argv[i];
        if(arg.front() != '-'){
            std::cout << argv[i] << "\n";
            no_dash_count++;
        }
    }

    std::cout << single_dash_count << "\n";
    std::cout << double_dash_count << "\n";
    std::cout << no_dash_count << "\n";

    return 0;
}

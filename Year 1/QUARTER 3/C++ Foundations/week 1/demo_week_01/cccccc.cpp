
#include <string>
#include <cctype>
#include <iostream>
#include <stdlib.h>
#include <sstream> //iss
#include <iomanip>
#include <fstream> //std::ifstream ofstream
#include <algorithm> //find_first_of find last of

bool is_empty_line(const std::string line){
    return line.find_first_not_of(" \t\n\r") == std::string::npos;
}

std::string clean_line(std::string line){
    //erase space b4 firsst character
    line.erase(line.begin(), line.begin() + line.find_first_not_of(" \t\n\r"));
    line.erase(line.find_last_not_of("  \t\n\r") + 1);

    std::istringstream iss(line);
    std::string word, cleaned_line;
    while(iss  >> word){
        if(!cleaned_line.empty()){
            cleaned_line += " ";
        }
        cleaned_line += word;
    }

    std::string punctuations = ",.;:-";
    for(size_t i = 0; i < cleaned_line.length(); i ++){
        if(punctuations.find(cleaned_line[i]) != std::string::npos && i > 0 && cleaned_line[i - 1] == ' '){
            cleaned_line.erase(i-1, i);
            --i; //adjust target after erasing

        }
    }
    return cleaned_line;
}

int main(int argc, char * argv[]){
    if(argc < 2){
        std::cerr << "Usage :" << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if(!input_file){
        std::cerr << "Error : cannot open\n";
        return 1;
    }

    std::string input_filename(argv[1]);
    size_t last_dot =  input_filename.find_last_of('.');
    std::string output_filename = input_filename.substr(0, last_dot) + " .clean";

    std::ofstream output_file(output_filename);
    if(!output_file){
        std::cerr << " Cannot";
        return 1;
    }

    std::string line;
    while(std::getline(input_file, line)){
        if(!is_empty_line(line)){
            std::string cleaned_line = clean_line(line);
            output_file << cleaned_line << "\n";
        }
    }

    input_file.close();
    output_file.close();

    std::cout << "fileoepnasdad";
    return 0;
}
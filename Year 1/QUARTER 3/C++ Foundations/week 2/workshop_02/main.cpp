#include <iomanip>
#include <string>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <algorithm>
#include "textredactor.h"

int main(int argc, char* argv[]){
    if (argc != 3){
        std::cerr << "Usage: " << argv[0] << " <input file> <replacements file>\n";
        return 1;
    }

    TextRedactor tr;
    if(!tr.read_replacements(argv[2])){
        std::cerr << "Error reading replacements from " << argv[2] << '\n';
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if(!input_file){
        std::cerr << "Error opening input file " << argv[1] << '\n';
        return 1;
    }

    std::stringstream buffer;
    buffer << input_file.rdbuf();
    std::string redacted_text = tr.redact(buffer.str());

    std::string output_file_name = std::string(argv[1]) + ".redacted";
    std::ofstream  output_file(output_file_name);
    if(!output_file){
        std::cerr << "Error creating output file " << output_file_name << "\n";
        return 1;
    }

    output_file << redacted_text;
    std::cout << "Redacted text saved to " << output_file_name << '\n';

    return 0;
}
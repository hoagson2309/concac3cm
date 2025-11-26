# Week 1 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 5/2/2025

# LABS
```cpp
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <iomanip>  
#include <algorithm>
#include <string> 

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "No arguments provided.\n";
        return 1;  
    }

    int single_dash_count = 0;
    int double_dash_count = 0;
    int no_dash_count = 0;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg.starts_with("--")) {
            std::cout << arg << "\n";
            double_dash_count++;
        } else if (arg.front() == '-') {
            std::cout << arg << "\n";
            single_dash_count++;
        } else {
            std::cout << arg << "\n";
            no_dash_count++;
        }
    }

    std::cout << "Single dash arguments: " << single_dash_count << "\n";
    std::cout << "Double dash arguments: " << double_dash_count << "\n";
    std::cout << "No dash arguments: " << no_dash_count << "\n";

    return 0;
}
```
# WORKSHOPS - TEXTCLEANER
```cpp
#include <iostream>  // For input/output operations
#include <fstream>   // For file handling
#include <sstream>   // For string stream operations
#include <algorithm> // For std::find_first_not_of and std::find_last_not_of

// function to check if a line is empty or contains only whitespace
bool is_empty_line(const std::string& line) {
    return line.find_first_not_of(" \t\n\r") == std::string::npos;
}

// function to clean a line by removing extra spaces and trimming leading/trailing spaces
std::string clean_line(std::string line) {
    // remove leading spaces
    line.erase(line.begin(), line.begin() + line.find_first_not_of(" \t\n\r"));
    // Remove trailing spaces
    line.erase(line.find_last_not_of(" \t\n\r") + 1);

    //replace multiple spaces with a single space
    std::istringstream iss(line);
    std::string word, cleaned_line;
    while (iss >> word) {
        if (!cleaned_line.empty()) {
            cleaned_line += ' ';
        }
        cleaned_line += word;
    }

    //remove spaces before punctuation
    std::string punctuations = ".,;:-";
    for (size_t i = 0; i < cleaned_line.length(); ++i) {
        if (punctuations.find(cleaned_line[i]) != std::string::npos && i > 0 && cleaned_line[i - 1] == ' ') {
            cleaned_line.erase(i - 1, 1);
            --i; //adjust index after erasing
        }
    }

    return cleaned_line;
}

int main(int argc, char* argv[]) {
    // check if the correct number of arguments is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    // open the input file
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cerr << "Error: Cannot open input file '" << argv[1] << "'\n";
        return 1;
    }

    // create the output file name by replacing the extension with .clean
    std::string input_filename(argv[1]);
    size_t last_dot = input_filename.find_last_of('.');
    std::string output_filename = input_filename.substr(0, last_dot) + ".clean";

    // o pen the output file
    std::ofstream output_file(output_filename);
    if (!output_file) {
        std::cerr << "Error: Cannot create output file '" << output_filename << "'\n";
        return 1;
    }

    //process the input file line by line
    std::string line;
    while (std::getline(input_file, line)) {
        if (!is_empty_line(line)) {
            std::string cleaned_line = clean_line(line);
            output_file << cleaned_line << '\n';
        }
    }

    //close the files
    input_file.close();
    output_file.close();

    std::cout << "File cleaned successfully. Output saved to '" << output_filename << "'\n";
    return 0;
}
```
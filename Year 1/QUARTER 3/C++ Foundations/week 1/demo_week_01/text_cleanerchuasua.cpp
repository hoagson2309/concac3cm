#include <iostream> // header with in/out stream (printing to the console)
#include <fstream> //for file handling (reading and writing files)
#include <sstream> //for stream operations (for splitting stirngs into words)
#include <iomanip>  // nobody knows
#include <algorithm> // For std::find_first_not_of and std::find_last_not_of (for advanced string operations)

//function to check the line is empty or contains only whitespace
bool is_empty_line(const std::string line){
    return line.find_first_not_of(" \t\n\r") == std::string::npos; //If find_first_not_of returns std::string::npos, it means the line contains only whitespace characters (or is empty), so the function returns true.
} //find_first_not_of(" \t\n\r") looks for the first character that is not a space, tab, or newline. If no such character is found, the line is empty, and the function returns true.

//function to clean the line by removing extra spaces and trimming leading/trailing spaces
std::string clean_line(std::string line){
    //remove leading spaces
    line.erase(line.begin(), line.begin() + line.find_first_not_of(" \t\n\r"));
    //remove trailing spaces
    line.erase(line.find_last_not_of(" \t\n\r") + 1);

    std::istringstream iss(line);
    std::string word, cleaned_line;
    while(iss >> word){
        if(!cleaned_line.empty()){
            cleaned_line += ' ';
        }
        cleaned_line += word;
    }

    //remove space b4 punctuation
    std::string punctuations = ".,;:-";
    for(size_t i = 0; i < cleaned_line.length(); ++i){
        if(punctuations.find(cleaned_line[i]) != std::string::npos && i > 0 && cleaned_line[i - 1] == ' '){
            cleaned_line.erase(i - 1, 1);
            --i;//adjust index after erasing
        }
    }

    return cleaned_line;
}

int main(int argc, char* argv[]){
    //check if the correct number of argument is provided
    if(argc < 2){
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    //open the input file
    std::ifstream input_file(argv[1]);
    if(!input_file){
        std::cerr << "Error: Cannot open input file '" << argv[1] << "'\n";
        return 1;
    }

    //create the output file name by replacing the extension with .clean
    std::string input_filename(argv[1]);
    size_t last_dot = input_filename.find_last_of('.');
    std::string output_filename = input_filename.substr(0, last_dot) + ".clean";

    //open the output file
    std::ofstream output_file(output_filename);
    if(!output_file){
        std::cerr << "Error: Cannot creat the output file '" << output_filename << "'\n";
        return 1;

        //Process the input file line by line
        std::string line;
        while(std::getline(input_file, line)){
            if(!is_empty_line(line)){
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
}



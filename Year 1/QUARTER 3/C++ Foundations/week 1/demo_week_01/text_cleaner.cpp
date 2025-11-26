#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

bool is_empty_line(const std::string& line) {
    return line.find_first_not_of(" \t\n\r") == std::string::npos;
}

std::string clean_line(const std::string& line) {
    std::istringstream iss(line);
    std::string word, cleaned_line;
    while (iss >> word) {
        if (!cleaned_line.empty()) {
            cleaned_line += " ";
        }
        cleaned_line += word;
    }
    
    // Remove spaces before punctuation marks
    std::string result;
    for (size_t i = 0; i < cleaned_line.size(); ++i) {
        if (i > 0 && std::isspace(cleaned_line[i - 1]) && (cleaned_line[i] == '.' || cleaned_line[i] == ',' || cleaned_line[i] == ':' || cleaned_line[i] == ';' || cleaned_line[i] == '-')) {
            result.pop_back(); // Remove the space before punctuation
        }
        result += cleaned_line[i];
    }
    return result;
}

std::string get_clean_filename(const std::string& filename) {
    size_t last_dot = filename.find_last_of('.');
    if (last_dot == std::string::npos) {
        return filename + ".clean";
    }
    return filename.substr(0, last_dot) + ".clean";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::string input_filename = argv[1];
    std::ifstream input_file(input_filename);
    if (!input_file) {
        std::cerr << "Error: File '" << input_filename << "' not found.\n";
        return 1;
    }

    std::string output_filename = get_clean_filename(input_filename);
    std::ofstream output_file(output_filename);

    std::string line;
    while (std::getline(input_file, line)) {
        if (!is_empty_line(line)) {
            output_file << clean_line(line) << '\n';
        }
    }

    std::cout << "Processed file saved as: " << output_filename << "\n";
    return 0;
}

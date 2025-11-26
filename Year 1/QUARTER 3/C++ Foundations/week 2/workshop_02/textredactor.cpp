    #include "textredactor.h"
#include <fstream> // provides file input/output functionality (e.g., reading from and writing to files).
#include <sstream> //allows string stream operations, useful for reading and manipulating strings.
#include <cctype> //provides functions for character classification (e.g., isdigit to check if a character is a digit).

bool TextRedactor::read_replacements(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter_pos = line.find('|');
        if (delimiter_pos != std::string::npos) {
            std::string original = line.substr(0, delimiter_pos);
            std::string replacement = line.substr(delimiter_pos + 1);
            //trim whitespace
            original.erase(0, original.find_first_not_of(' '));
            original.erase(original.find_last_not_of(' ') + 1);
            replacement.erase(0, replacement.find_first_not_of(' '));
            replacement.erase(replacement.find_last_not_of(' ') + 1);
            replacements_.add(original, replacement);
        }
    }
    return true;
}

std::string TextRedactor::redact_dates(const std::string& text) const {
    //implement date redaction logic 
    return text;
}

std::string TextRedactor::redact_numbers(const std::string& text) const {
    std::string result = text;
    for (size_t i = 0; i < result.size(); ++i) {
        if (isdigit(result[i])) {
            size_t start = i;
            while (i < result.size() && isdigit(result[i])) ++i;
            result.replace(start, i - start, "XXX");
            i = start + 2; //adjust index after replacement (Since "XXX" is 3 characters long, the new index should be start + 3 - 1 = start + 2 (because the loop increments i at the end of each iteration))
        }   
    }
    return result;
}

std::string TextRedactor::redact_replacements(const std::string& text) const {
    std::string result = text;
    for (int i = 0; i < replacements_.size(); ++i) {
        std::string key = replacements_.key(i);
        std::string value = replacements_.get(key);
        size_t pos = result.find(key);
        while (pos != std::string::npos) {
            result.replace(pos, key.length(), value);
            pos = result.find(key, pos + value.length()); //searches for the next occurrence of key starting from the position immediately after the last replacement (pos + value.length()).
        }                                                 //(EXAMPLE) result = "The kissa and the dog are friends." => Find the next occurrence of "cat" starting from 4 + 5 = 9 (length of "kissa" is 5) 
    }
    return result;
}

std::string TextRedactor::redact(const std::string& text) const {
    std::string result = text;
    result = redact_replacements(result);
    result = redact_dates(result);
    result = redact_numbers(result);
    return result;
}
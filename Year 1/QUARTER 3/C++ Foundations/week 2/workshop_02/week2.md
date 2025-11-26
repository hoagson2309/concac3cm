# Week 2 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 10/2/2025

# WORKSHOPS
```cpp
//DICTIONARY.H
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <array>
#include <string>

struct KeyValue {
    std::string key;
    std::string value;
};

struct Dictionary {
    static constexpr int capacity_ = 100;
    std::array<KeyValue, capacity_> pairs_;
    int size_ = 0;

    void add(const std::string& key, const std::string& value);
    bool contains(const std::string& key) const;
    std::string get(const std::string& key) const;
    int size() const;
    std::string key(int index) const;
};

#endif // DICTIONARY_H

//DICTIONARY.CPP
#include "dictionary.h"

void Dictionary::add(const std::string& key, const std::string& value) {
    if (contains(key)) return;
    if (size_ < capacity_) {
        pairs_[size_].key = key;
        pairs_[size_].value = value;
        ++size_;
    }
}

bool Dictionary::contains(const std::string& key) const {
    for (int i = 0; i < size_; ++i) {
        if (pairs_[i].key == key) return true;
    }
    return false;
}

std::string Dictionary::get(const std::string& key) const {
    for (int i = 0; i < size_; ++i) {
        if (pairs_[i].key == key) return pairs_[i].value;
    }
    return "";
}

int Dictionary::size() const {
    return size_;
}

std::string Dictionary::key(int index) const {
    if (index >= 0 && index < size_) {
        return pairs_[index].key;
    }
    return "";
}

//TEXTREDACTOR.H
#ifndef TEXT_REDACTOR_H
#define TEXT_REDACTOR_H

#include "dictionary.h"
#include <string>

struct TextRedactor {
    Dictionary replacements_;

    bool read_replacements(const std::string& file_name);
    std::string redact_dates(const std::string& text) const;
    std::string redact_numbers(const std::string& text) const;
    std::string redact_replacements(const std::string& text) const;
    std::string redact(const std::string& text) const;
};

#endif // TEXT_REDACTOR_H

//TEXTREDACTOR.CPP
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

//MAIN.CPP
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
```
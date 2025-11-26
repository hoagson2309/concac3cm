#include "counter.h"
#include <fstream>
#include <sstream>
#include <algorithm>

//constructor implementation
Counter::Counter(const Options& opts) : opts_(opts) {}

// Function to process a file and return its counts
FileCounts Counter::process(const std::string& file_name) {
    std::ifstream file(file_name); //open file for reading
    if (!file) {
        throw std::runtime_error("Cannot open file: " + file_name); //Use std::runtime_error when the error is caused by an external, runtime condition. Use std::invalid_argument when the error is due to incorrect function input.
    }

    //create a FileCounts object to store the counts for this file
    FileCounts counts;
    counts.file_name = file_name; //set the file name

    std::string line;
    while (std::getline(file, line)) {
        counts.lines++;
        counts.words += count_words(line);
        counts.charaters += count_characters(line);
        counts.bytes += line.size() + 1; // +1 for newline character
        counts.maximum_line_length = std::max(counts.maximum_line_length, line.size()); //update the longest line length
    }

    return counts;
}

std::size_t Counter::count_words(const std::string& text) const{
    std::istringstream stream(text);  //create string stream for the text
    std::size_t word_count = 0;
    std::string word;
    while(stream >> word){ //extract word from stream
        word_count++;
    }
    return word_count;
}

std::size_t Counter::count_characters(const std::string& text) const {
    return text.size();   //return the size of the string (number of characters)                                                                           
}
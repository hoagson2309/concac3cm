#ifndef COUNTER_H
#define COUNTER_H

#include "file_counts.h" //for FileCounts struct
#include "options.h"     //for Options class
#include <string>        //for std::string

//Counter class to process files and count lines, words...
class Counter {
public: 
// Constructor that takes an Options object to configure counting behavior
    Counter(const Options& opts);
 // Function to process a file and return its counts
    FileCounts process(const std::string& file_name);

private:
    Options opts_; // Store the options passed to the constructor
    std::size_t count_words(const std::string& text) const;
    std::size_t count_characters(const std::string& text) const;
};

#endif //COUNTER_H
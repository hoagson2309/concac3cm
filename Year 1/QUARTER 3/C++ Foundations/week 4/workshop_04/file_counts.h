#ifndef FILE_COUNTS_H
#define FILE_COUNTS_H

#include <string> //std::string
#include <ostream> //std::ostream
#include "options.h" 

// define the `FileCounts` struct to store counts for a file
struct FileCounts {
    std::size_t lines{};               //number of lines
    std::size_t words{};
    std::size_t charaters{};
    std::size_t bytes{};
    std::size_t maximum_line_length{}; //length of the longest line
    std::string file_name{};           //name of the file  

    //function to print count to the output stream
    void print(std::ostream& out, const Options& opt) const;

};

#endif //FILE_COUNTS_H
# Week 3 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 4/3/2025

# LABS
```cpp
//OPTIONS.H
#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector> //std::vector
#include <string> //std::string
#include <iostream> // std::ostream

//Options class
class Options{
public:
//Constructors
    Options(int argc, char *argv[]); //constructor takes command-line arguments
    Options(); // default constructor

//Accessors function to check if specific options are enabled
    bool lines() const;
    bool words() const;
    bool characters() const;
    bool bytes() const;
    bool longest_line() const;
    bool help() const;
    bool version() const;

// Accessors function to get the list of file names. Contains a vector with file names to process
    const std::vector<std::string>& file_names() const;

//Modifiers
//Parses command-line arguments and replaces the the current values of file names with new, parsed values
    void parse(int argc, char *argv[]);

//Debug/ helper functions
    //check if verbose mode is enabled
    bool verbose() const;
    //print the parsed options to the output stream
    void print(std::ostream& out) const;

private:
//private data members to store the state of options
    bool lines_;
    bool words_;
    bool characters_;
    bool bytes_;
    bool longest_line_;
    bool help_;
    bool version_;
    bool verbose_;
    std::vector<std::string> file_names_;

    //reset function to reset all options to default values
    void reset();

};

std::ostream& operator<<(std::ostream& out, const Options& opt);

#endif // OPTIONS_H

//OPTIONS.CPP
#include "options.h"
#include <stdexcept> //std::invalid_argument

Options::Options(int argc, char *argv[]){
    parse(argc, argv); //call parse function to initialize options
}

Options::Options(){
    reset(); //initialize all options to default values
}

//function to reset all options to default value
void Options::reset() {
    lines_ = false;
    words_ = false;
    characters_ = false;
    bytes_ = false;
    longest_line_ = false;
    help_ = false;
    version_ = false;
    verbose_ = false;
    file_names_.clear(); //clear the list of file names
}

//function to parse command-line arguments
void Options::parse(int argc, char *argv[]){
    reset();// reset b4 parsing new arguments  
    for(int i = 1; i < argc; ++i){
        std::string arg = argv[i];  //same  std::string arg { argv[i] };
        if(arg[0] == '-'){
            if(arg == "--help"){
                help_ = true;
            } else if(arg == "--version"){
                version_ = true;
            } else if (arg == "--verbose") {
                verbose_ = true;
            } else{
                //handle short options
                for (size_t j = 1; j < arg.size(); ++j) {
                    switch (arg[j]) {
                        case 'l': lines_ = true; break;
                        case 'w': words_ = true; break;
                        case 'm': characters_ = true; break;
                        case 'c': bytes_ = true; break;
                        case 'L': longest_line_ = true; break;
                        default:
                        //throw an exception for invalid options
                            throw std::invalid_argument("invalid option passed: " + arg);
                    }
                }
            } 
        }   else{
                //if the argument is not an option treat it as a file name
                file_names_.push_back(arg); // this is a member function of std::vector that appends the value of arg to the end of the vector, increasing its size by one. file_names_.push_back(arg); is a simple and effective way to collect and store file names from command-line arguments in a std::vector.
            }
    }
}

//accessors functions to check if specific options are enabled
bool Options::lines() const { return lines_; }
bool Options::words() const { return words_; }
bool Options::characters() const { return characters_; }
bool Options::bytes() const { return bytes_; }
bool Options::longest_line() const { return longest_line_; }
bool Options::help() const { return help_; }
bool Options::version() const { return version_; }
bool Options::verbose() const { return verbose_; }

//accessor function to get the list of file names
const std::vector<std::string>& Options::file_names() const {
    return file_names_;
}   

//function to print the parsed options to the output stream   
void Options::print(std::ostream& out) const{
    out << "Options:"   
        << "\n\tlines: "        << std::boolalpha << lines_
        << "\n\twords: "        << std::boolalpha << words_
        << "\n\tcharacters: "   << std::boolalpha << characters_
        << "\n\tbytes: "        << std::boolalpha << bytes_
        << "\n\tlongest_line: " << std::boolalpha << longest_line_
        << "\n\thelp: "         << std::boolalpha << help_
        << "\n\tversion: "      << std::boolalpha << version_
        << "\n\tfiles: ";
    for(const auto& fn : file_names_){
        out << "\n\t * " << fn;
    }
}

std::ostream& operator<<(std::ostream& out, const Options& opt){
    opt.print(out); //call print function
    return out;
}

//FILE_COUNTS.H
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

//FILE_COUNTS.CPP
#include "file_counts.h"

//function to print the counts to the output stream
void FileCounts::print(std::ostream& out, const Options& opt) const{
    if(opt.lines()) out << lines << " ";
    if(opt.words()) out << words << " ";
    if(opt.characters()) out << charaters << " ";
    if(opt.bytes()) out << bytes << " ";
    if(opt.longest_line()) out << maximum_line_length << " ";
    out << file_name << "\n"; //print the file name
}

//COUNTER.H
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

//COUNTER.CPP
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

//MAIN.CPP
#include <iostream>
#include <stdexcept>
#include "options.h"
#include "counter.h"
#include "file_counts.h"

//define a multi-line string for the help text
auto help_text = R"(
    Usage: wc [OPTION]... [FILE]...
    Print newline, word, and byte counts for each FILE, and a total line if more than one FILE is specified.
    With no FILE, or when FILE is -, read standard input.
    
    The options below may be used to select which counts are printed, always in the following order:
    lines, words, characters, bytes, maximum line length.
    
      -c, --bytes            print the byte counts
      -m, --chars            print the character counts
      -l, --lines            print the newline counts
      -w, --words            print the word counts
      -L, --max-line-length  print the length of the longest line
          --help             display this help and exit
          --version          output version information and exit
    )";

int main (int argc, char *argv[]){
    try{
    //parse command-line arguments using the Options class
        Options opts{argc, argv};

    //if verbose mode enable print the parsed options
        if(opts.verbose()){
            opts.print(std::cout);
        }

        if(opts.help()){
            std::cout << help_text;
            return EXIT_SUCCESS;
        }

        if(opts.version()){
            std::cout << "wc (my implementation) 1.0\n";
            return EXIT_SUCCESS;
        }

        if(opts.file_names().empty()){
            std::cout << "No file name passed.\n";
            std::cout << "Try 'wc --help' for more information.\n";
            return EXIT_FAILURE;
        }
        // Create a Counter object with the parsed options
        Counter counter{opts};
        FileCounts totals; //create a FileCounts object to store totals (if multiple files are processed)

        // Process each file and print its counts
        for (const auto& file_name : opts.file_names()){
            auto counts = counter.process(file_name);
            counts.print(std::cout, opts);
        }
        return EXIT_SUCCESS;
    } catch (std::invalid_argument& exc){ //catch to handle throw exception in process function
        std::cout << exc.what() << '\n';
        std::cout << "Try 'wc --help' for more informantion.\n";
        return EXIT_FAILURE;
    } catch (const std::runtime_error& exc){
        std::cout << exc.what() << '\n';
        return EXIT_FAILURE;
    }
}
```
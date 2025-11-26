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
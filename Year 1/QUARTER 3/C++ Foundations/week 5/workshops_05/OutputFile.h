#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <string>
#include <cstdio>

namespace io{

class OutputFile{
public:
    //constructor that opens a file
    OutputFile(const std::string& file_name);

    //Default constructor
    OutputFile();

    //destructor that closes a file
    ~OutputFile();

    //open a file
    void open(const std::string& file_name);

    //close a file 
    void close();

    //check if the file is open
    bool is_open() const;

    //check if error occurs
    bool error() const;

    //check if the end of file has been reached
    bool eof() const;

    //get the filename
    std::string name() const;

    //operator overloads for <<
    OutputFile& operator<<(const std::string& value);
    OutputFile& operator<<(const char* value);
    OutputFile& operator<<(char value);
    OutputFile& operator<<(int number);
    OutputFile& operator<<(double number);
    OutputFile& operator<<(bool value);

    //optional: count lines and characters
    int lines() const;
    int size() const;

private:
    std::string file_name_; 
    FILE* file_;
    int lines_written_;
    int chars_written_;
};

} //namespace io

#endif //OUTPUTFILE_H
#include "OutputFile.h"
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <algorithm> //for std::count
namespace io{

OutputFile::OutputFile(const std::string& file_name)
: file_name_(file_name), file_(nullptr), lines_written_(0), chars_written_(0) { open(file_name); } //automatically open the file when the object is created. 

OutputFile::OutputFile()
: file_name_(""), file_(nullptr), lines_written_(0), chars_written_(0) {} //This constructor is used when you want to create an OutputFile object but don’t yet know the file name or don’t want to open a file immediately.

//destructor close file
OutputFile::~OutputFile(){
    close();
}

void OutputFile::open(const std::string& file_name){
    if(file_){
        close();
    }
    file_name_ = file_name;
    file_ = std::fopen(file_name.c_str(), "w");
    if(!file_){
        throw std::invalid_argument("Couldn't open file,\n");
    }
}

void OutputFile::close(){
    if(file_){
        std::fclose(file_);
        file_ = nullptr;
    }
}

bool OutputFile::is_open() const{
    return file_ != nullptr;
}

bool OutputFile::error() const{
    return file_ ? std::ferror(file_) != 0 : true;
    // if (file_ != nullptr) {
    //     return std::ferror(file_) != 0;
    // } else {
    //     return true;
    // }
}

bool OutputFile::eof() const{
    return file_ ? std::feof(file_) != 0 : true;
}

std::string OutputFile::name() const{
    return file_name_;
}

OutputFile& OutputFile::operator<<(const std::string& value){ //c++ style string
        if(file_){
            chars_written_ += std::fprintf(file_, "%s", value.c_str()); //The return value of std::fprintf is the number of characters written
            //std::fputs could also be used to write strings to the file, but it does not return the number of characters written. Instead, it returns a non-negative value on success or EOF on failure.
            //Since we need to track the number of characters written, std::fprintf is more suitable because it provides this information directly.

            lines_written_ += std::count(value.begin(), value.end(), '\n');//Each time a string is written to the file, we count the number of '\n' characters in that string and add it to lines_written_.
            //std::fprintf does not provide information about the content of the string being written (e.g., how many newline characters it contains). It only tells us how many characters were written.
            //To count lines, we need to explicitly examine the content of the string for newline characters, which is why std::count is used.
        }
        return *this; 
}

OutputFile& OutputFile::operator<<(const char* value) { //c style string
    if(file_){
        chars_written_ += std::fprintf(file_, "%s", value);
        lines_written_ += std::count(value, value + std::strlen(value), '\n');
    }
    return *this;
}

OutputFile& OutputFile::operator<<(char value){
    if(file_){
        chars_written_ += std::fprintf(file_, "%c", value);
        if(value == '\n'){
            lines_written_++;
        }
    }
    return *this;
}

OutputFile& OutputFile::operator<<(int number) {
    if(file_){
        chars_written_ += std::fprintf(file_, "%d", number);
    }
    return *this;
}

OutputFile& OutputFile::operator<<(double number) {
    if (file_) {
        chars_written_ += std::fprintf(file_, "%f", number);
    }
    return *this;
}

OutputFile& OutputFile::operator<<(bool value){
    if(file_){
        const char* str = value ? "true" : "false"; //const char* str to use C-style function like fprintf
        // const char* str;
        //   if (value) {
        //     str = "true";
        // } else {
        //     str = "false";
        // }
        chars_written_ += std::fprintf(file_, "%s", str);
        lines_written_ += std::count(str, str + std::strlen(str), '\n');
    }
    return *this;
}

//number of line
int OutputFile::lines() const{
    return lines_written_;
}

int OutputFile::size() const{
    return chars_written_; // size = number of characters
}

} //namespace io


// Use const char*:
// When working with string literals.
// When you need compatibility with C-style functions like std::fprintf.
// When you want to avoid the overhead of std::string.

// Use const std::string&:
// When you need the functionality of std::string.
// When the string data is already stored in a std::string object.
// When working with code that expects std::string.

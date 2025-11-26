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

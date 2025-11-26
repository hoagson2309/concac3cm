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

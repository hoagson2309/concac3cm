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
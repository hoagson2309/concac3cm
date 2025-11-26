#ifndef DEMO_WEEK_02_OPTIONS_H
#define DEMO_WEEK_02_OPTIONS_H
#include <string>
#include <vector>


struct Options {
    std::vector<std::string> files;
    std::string pattern;

    bool color;
    bool ignore_case;

    void parse(int argc, const char* argv[]);

    void print() const;

};


#endif //DEMO_WEEK_02_OPTIONS_H

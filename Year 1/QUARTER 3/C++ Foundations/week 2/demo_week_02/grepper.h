//
// Created by dza02 on 2/26/2024.
//

#ifndef DEMO_WEEK_02_GREPPER_H
#define DEMO_WEEK_02_GREPPER_H
#include <string>

struct Grepper {
    std::string pattern;
    bool color;
    bool ignore_case;
    void set_options(std::string pat, bool c, bool ic);

    void process(std::string file_name) const;
};


#endif //DEMO_WEEK_02_GREPPER_H

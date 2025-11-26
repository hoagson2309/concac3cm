#include "dictionary.h"

int main()
{
    demo::Dictionary dict{};

    demo::read_from_file("words.txt", dict);

    std::cout << dict << std::endl;

    auto copy = dict;

    demo::Dictionary another{};

    another = dict;

    //another.operator=(dict);

    return 0;
}

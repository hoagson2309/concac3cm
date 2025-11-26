#include <iostream> // header with in/out stream
#include <fstream>  // file stream
#include <iomanip>  // nobody knows

int main(int argc, char * argv[]){
    if(argc < 2)
    {
        std::cerr << "Error";
        return 1;
    }

    std::ifstream input{argv[1]};

    if(input)
    {
        std::string line;

        while(std::getline(input,line))
        {
            std::string word;

            std::istringstream line_stream{line};

            while(line_stream >> word)
            {
                //std::ispunct(word[0]);
                std::cout << word << ' ';
            }
            std::cout << '\n';
        }
    }
    else{
        std::cerr << "Cannot open file";
    }
}
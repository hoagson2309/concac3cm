#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //std::quoted
#include <fstream>  // for std::ifstream, std::ofstream
#include "counter.h" // for sax::counter

// std::vector<std::string>::iterator partition(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end){
//     auto pivot = *(end - 1); //pivot is the last element
//     auto i = begin;         //i = boundary of <= pivot elements

//     // *i: actual value of element
//     // i: iterator

//     for(auto j = begin; j < end - 1; ++j){
//         sax::counter::instance().inc_comparisons(); //count comparison
//         if(*j <= pivot){
//             std::swap(*i, *j);
//             sax::counter::instance().inc_swaps(); //count swap
//             ++i;
//         }
//     }
//     std::swap(*i, *(end - 1)); //final swap to move pivot to the middle
//     sax::counter::instance().inc_swaps();  //count final swap
//     return i;
// }

// //recursive quick sort 
// void quick_sort(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end){
//     if(end - begin <= 1) return;  //0 or 1 => already sorted 
//     auto pivot_pos = partition(begin, end);  //get pivot position
//     quick_sort(begin, pivot_pos);       //sort elements b4 pivot
//     quick_sort(pivot_pos + 1, end);     //sort elements after pivot
// }

//CORRECT BUT FIX FOR ASSIGNMENT 5
std::vector<std::string>::iterator partition(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end){
    auto mid = begin + (std::distance(begin, end) / 2); //pointer of middle element  (gives the number of elements in the current range.) Dividing by 2 and adding to begin gives the iterator pointing to the middle element
    auto pivot_value = *mid;  

    //move pivot to the end temporarily
    std::iter_swap(mid, end - 1);
    sax::counter::instance().inc_swaps();

    std::vector<std::string>::iterator store = begin;  //store keeps track of the boundary of elements smaller than the pivot.
    for (std::vector<std::string>::iterator it = begin; it != end; it++){
        sax::counter::instance().inc_comparisons();
        if(*it < pivot_value){
            std::iter_swap(it, store);
            sax::counter::instance().inc_swaps();
            ++store;
        }
    }
    std::iter_swap(store, end - 1);
    sax::counter::instance().inc_swaps();
    return store;
}

    //recursive quick sort 
    void quick_sort(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end){
        if(std::distance(begin, end) > 1){                
            auto pivot_pos = partition(begin, end);  //get pivot position
            quick_sort(begin, pivot_pos);       //sort elements b4 pivot
            quick_sort(pivot_pos + 1, end);   //sort elements after pivot
        }  
    }

int main() {
    /* TODO:
        Write a program that reads the names of two files from the standard input, 
        reads the strings from the first file into a vector, sorts the vector using quick sort,
        and then writes the sorted strings to the second file.

        When sorting the strings, the program should count the number of comparisons and swaps performed,
        and print these counts to standard output.
        
        Use the sax::counter class for this (see counter.h and counter.cpp).
    */
    //read filenames from stdin
    std::string input_name, output_name;
    std::getline(std::cin, input_name);
    std::getline(std::cin, output_name);

    //read input
    std::ifstream fin(input_name);
    if(!fin){
        std::cerr << "Error opening input file " << std::quoted(input_name) << "\n";
        return 1;
    }

    std::vector<std::string> data;
    std::string word;
    while(fin >> word){
        data.push_back(word);
    }
    fin.close();

    //sort with quicksort
    quick_sort(data.begin(), data.end());

    //write output
    std::ofstream fout(output_name);
    if(!fout){
        std::cerr << "Error opening output file " << std::quoted(output_name) << "\n";  //std::quoted makes string in " "
        return 1;
    }

    for(const auto& s : data){
        fout << s << "\n";
    }

    fout.close();

    //print stats from sax::counter
    std::cout << "Data size: " << data.size() << "\n";
    std::cout << "Comparisons: " << sax::counter::instance().comparisons() << "\n";
    std::cout << "Swaps: " << sax::counter::instance().swaps() << "\n";

    return 0;
}

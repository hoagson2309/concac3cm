#include <iostream>
#include <vector>
#include "utils.h"
#include <string>

using std::vector;
using std::string;

void partition_array(vector<int>& arr, int value){
    int pos = 0;                       //placement pointer (where the next "kept" element should go)
    for(int i = 0; i < arr.size(); i++){  //i => scanning pointer 
        if(arr[i] != value){
            std::swap(arr[i], arr[pos]);
            pos++;
        }
    }
}

int main() {
    // TODO: write a program that receives three arguments over stdin, separated by spaces:
    // a vector of integers, followed by the word "move" and an integer
    // The program must partition the array so that all occurences of the integer
    // are placed at the end of the array.
    // Use the two-pointer technique and element swapping for this
    // See the utils.h file for writing / reading vectors
    vector<int> arr;
    int value;
    string command;

    std::cin >> arr >> command >> value;
    partition_array(arr, value);
    std::cout << arr;

    return 0;
}

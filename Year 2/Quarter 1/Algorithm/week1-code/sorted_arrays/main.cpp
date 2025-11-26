#include <iostream>
#include <vector>
#include <string>
#include "utils.h"

using std::vector;
using std::string;


int binary_search(const vector<int>& arr, int value){
    int lo = 0;
    int hi = arr.size(); 
    while (lo < hi){
        int mid = lo + (hi - lo) / 2; 
        if(arr[mid] == value){
            return mid; //found
        } else if (arr[mid] < value){
            lo = mid + 1; //search in higher half
        } else {
            hi = mid; //search in lower half
        }
    }
    return lo; //insertion position
}

bool contains(const vector<int>& arr, int value){
    int pos = binary_search(arr, value);
    return pos < arr.size() && arr[pos] == value; //return true
}

void insert(vector<int>& arr, int value){
    int pos = binary_search(arr, value);
    if (pos < arr.size() && arr[pos] == value) return; //if already contained
    arr.insert(arr.begin() + pos, value); //O(n) shift
} 

void remove(vector<int>& arr, int value){
    int pos = binary_search(arr, value);
    if(pos < arr.size() && arr[pos] == value){
        arr.erase(arr.begin() + pos); //O(n) shift
    }
}

int main() {
    // TODO: write a program that receives three arguments (through stdin):
    // a vector of integers, followed by a command ("insert", "remove" or "contains") and an integer
    // 
    // The output of the program must:
    //  if command is "insert" or "remove": the modified vector after applying the command
    //  if command is "contains": "true" (or "false") if the vector contains the element (or not)
    //
    // See the utils.h file for writing / reading vectors
    vector<int> arr;
    int value;
    string command;
    
    std::cin >> arr >> command >> value;

    if(command == "contains"){
        std::cout << (contains(arr, value) ? "true" : "false");
    } else if (command == "insert"){
        insert(arr, value);
        std::cout << arr;
    } else if (command == "remove"){
        remove(arr, value);
        std::cout << arr;
    }
    return 0;
}



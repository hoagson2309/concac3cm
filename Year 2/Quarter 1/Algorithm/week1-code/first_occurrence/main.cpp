#include <iostream>
#include <vector>
#include "utils.h"

using std::vector;

// The program MUST use binary search to find the first occurrence of the integer
// and return its index. If the integer is not found, it should return the index
// at which the value should be inserted to maintain sorted order.
int binary_search(const vector<int>& arr, int value){
    int lo = 0;
    int hi = arr.size();

    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        if(arr[mid] < value){
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;  //insertion position or first occurrence
}

int main() {
    // TODO: write a program that receives two arguments over stdin, separated by spaces:
    // a vector of integers, followed by an integer to search for
    //
    // The program MUST use binary search to find the first occurrence of the integer
    // and return its index. If the integer is not found, it should return the index
    // at which the value should be inserted to maintain sorted order.

    // See the utils.h file for writing / reading vectors
    vector<int> arr;
    int value;

    std::cin >> arr >> value;

    int pos = binary_search(arr, value);
    std::cout << pos;

    return 0;
}
#include <iostream>
#include <vector>
#include "utils.h"

using std::vector;

vector<int> intersect(const vector<int>& s1, const vector<int>& s2){
    vector<int> result;
    int i = 0, j = 0;

    while(i < s1.size() && j < s2.size()){
        if(s1[i] == s2[j]){
            result.push_back(s1[i]);
            i++;
            j++;
        } else if(s1[i] < s2[j]){
            i++;
        } else {
            j++;
        }
    }
    return result;
}

int main() {
    // TODO: write a program that receives two vectors of integers as arguments over stdin
    // You may assume that the vectors are sorted in non-decreasing order, and that all
    // elements are unique.
    //
    // The program must find the intersection of the two sets and write the resulting
    // vector to stdout.
    // REQUIREMENT: the algorithm to compute the intersection must run in O(n + m) time
    //  (where n and m are the sizes of the input vectors)
    // Use the two-pointer technique to achieve this result!

    // See the utils.h file for writing / reading vectors
    vector<int> a, b;
    std::cin >> a >> b;

    vector<int> result = intersect(a, b);
    std::cout << result;
    
    return 0;
}

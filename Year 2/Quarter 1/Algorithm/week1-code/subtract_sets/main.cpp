#include <iostream>
#include <vector>
#include "utils.h"

using std::vector;

vector<int> subtract(const vector<int>& s1, const vector<int>& s2){
    vector<int> result;
    int i = 0, j = 0;

    while(i < s1.size() && j < s2.size()){
        if(s1[i] == s2[j]){
            i++;
            j++;
        } else if(s1[i] < s2[j]){  //sorted array, s1[i] < s2[i] => s1[i] cannot be appear later in s2 => s1[i] is unique to s1
            result.push_back(s1[i]);
            i++;
        } else { 
            j++; //if s1[i] > s2[j] => s2[j] can still catch up so skip it for later comparision, either '=' or '<' cases
        }
    }

    //in case s1 longer than s2 => add the remaining elements
    while (i < s1.size()){
        result.push_back(s1[i]);
        i++;
    }
    return result;
}

int main() {
    // TODO: write a program that receives two vectors of integers as arguments over stdin
    // You may assume that the vectors are sorted in non-decreasing order, and that all
    // elements are unique.
    //
    // The program must subtract the second vector from the first vector and write the resulting
    // vector to stdout.
    // REQUIREMENT: the algorithm to compute the subtraction must run in O(n + m) time
    //  (where n and m are the sizes of the input vectors)
    // Use the two-pointer technique to achieve this result!

    // See the utils.h file for writing / reading vectors
    vector<int> A, B;
    std::cin >> A >> B;

    vector<int> result = subtract(A, B);
    std::cout << result;

    return 0;
}

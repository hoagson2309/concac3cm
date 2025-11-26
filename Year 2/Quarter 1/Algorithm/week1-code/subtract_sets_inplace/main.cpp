#include <iostream>
#include <vector>
#include "utils.h"

// Function prototype - you must implement this function
/// @brief Subtracts set b from set a, modifying a in place.
/// @param a First set (will be modified to contain the result)
/// @param b Second set (will not be modified)
void subtract_sets_inplace(std::vector<int>& a, const std::vector<int>& b);

void subtract_sets_inplace(std::vector<int>& a, const std::vector<int>& b){
    int i = 0;
    int j = 0;
    int k = 0;

    while(i < a.size() && j < b.size()){
        if(a[i] == b[j]){ //skip
            i++;
            j++;
        } else if (a[i] < b[j]){  //element is unique to a => keep
            a[k] = a[i];
            i++;
            k++;
        } else {
            j++;
        }
    }
    while (i < a.size()){
        a[k++] = a[i++];
    }
    a.resize(k); //cut off the garbage at the back.
}

int main() {
    // TODO: write a program that receives two vectors of integers as arguments over stdin
    // You may assume that the vectors are sorted in non-decreasing order, and that all
    // elements are unique.
    //
    // The program must subtract the second vector from the first vector and write the resulting
    // vector to stdout.
    // REQUIREMENT (1): the algorithm to compute the subtraction must run in O(n + m) time
    //  (where n and m are the sizes of the input vectors)
    // REQUIREMENT (2): the algorithm must modify the first vector in place
    //  Use the provided function prototype for this
    // Use the two-pointer technique to achieve this result!

    // See the utils.h file for writing / reading vectors
    std::vector<int> a, b;
    std::cin >> a >> b;

    subtract_sets_inplace(a, b);

    std::cout << a;
    return 0;
}

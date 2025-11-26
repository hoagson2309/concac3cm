#include <iostream>
#include <vector>
#include "utils.h"

int main() {
    /* TODO:
        Write a program that reads a vector of integers from standard input,
        followed by a number N. The program should find a contiguous (i.e. without gaps) subvector
        of the input vector that sums to N.
        If such a subvector is found, the program should print it.
        If no such subvector exists, the program should print an empty vector ("[]").

        Example input: [1, 2, 3, 4, 5] 9
        Example output: [2, 3, 4]
    */
    std::vector<int> arr;
    std::cin >> arr;

    if(!std::cin){
        std::cerr << "Failed to read input vector\n";
        return 1;
    }

    int target;
    std::cin >> target;

    size_t left = 0;        //start of sum window
    int current_sum = 0;    //running sum of window
    bool found = false;

    //sliding window
    for(size_t right = 0; right < arr.size(); right++){
        current_sum += arr[right]; //expand window

        //shrink window if sum too largex
        while(current_sum > target && left <= right){
            current_sum -= arr[left];
            ++left;
        }

        //check for match
        if(current_sum == target){
            std::vector<int> sub(arr.begin() + left, arr.begin() + right + 1);  //point to last but take the one b4 last
            std::cout << sub << std::endl;
            found = true;
            break;
        }
    }
    if(!found){
        std::cout << "[]" << std::endl;
    }
    return 0;
}

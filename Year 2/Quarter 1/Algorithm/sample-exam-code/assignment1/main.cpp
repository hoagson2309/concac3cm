#include <iostream>
#include "utils.h"   // for reading vectors
#include <vector>

int main() {
    int target;
    std::vector<int> values{};

    std::cin >> values >> target;
    int size = values.size();

    int left = 0, current_sum = 0;

    int best_left = 0, best_right = 0;
    int best_sum = 0;
    int INT = 1e9;
    int best_diff = INT;

    for(int right = 0; right < size; right++){
        current_sum += values[right];

        while(current_sum > target && left <= right){  //[10, 15, 20, 25] 31
            int diff = std::abs(current_sum - target); //45 -> 35 still > 31 so keep subtracting -> 20 then exit while loop (EXPLAIN DOWN)
            if(diff < best_diff){ // Now, when current_sum = 35, it updates best_sum before subtracting 15 → correctly captures [15, 20].
                best_diff = diff;  //After subtracting, it will check current_sum = 20 → ignored because diff = 11 > 4.
                best_sum = current_sum;
                best_left = left; 
                best_right = right;
            }
            current_sum -= values[left++];
            
        }
        // if(current_sum == target){   //could not be exactly equals cuz they also want to check to closest element to the sum
            int diff = std::abs(current_sum - target);
            if(diff < best_diff){  //lower diff =>  better => close to the current sum
                best_diff = diff;
                best_sum = current_sum;
                best_left = left; //must keep track of your best cuz it doesnt stop it loop until the end after finding find best_diff
                best_right = right;
            }
    }

    
    if(best_diff == INT){
        std::cout << "COULD NOT FIND" << std::endl;
    } else{
        std::vector<int> sub(values.begin() + best_left, values.begin() + best_right + 1);
        std::cout << sub << " (sum = " << best_sum << ")" << std::endl;
    }

    return 0;
}


// Example: [10, 15, 20, 25], target = 31
    // right = 2 → add 20 → current_sum = 45
    // Enter while(current_sum > target && left < right):
    // First iteration: subtract values[0] = 10 → current_sum = 35, left = 1
    // Second iteration: current_sum = 35 > 31 → subtract values[1] = 15 → current_sum = 20, left = 2
    // After the while loop ends, current_sum = 20 → diff = |20-31| = 11
    // You never considered the 35 (before subtracting 15), which is actually closer to 31.


// values = [5, 10, 20]
// target = 35
// window = [5,10,20] → current_sum = 35 → diff = 0 ✅ perfect match
// If you shrink first inside the while, current_sum becomes 30 → diff = 5 → you miss the exact match!
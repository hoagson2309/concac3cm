#include <iostream>
#include "utils.h"   // for reading vectors
#include <vector>

using namespace std;

int BubbleDown(vector<int>& heap, int i){
    int swaps = 0;
    int n = heap.size();
    while (true){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if(left < n && heap[left] < heap[smallest]) smallest = left;
        if(right < n && heap[right] < heap[smallest]) smallest = right;

        if(smallest != i){
            swap(heap[i], heap[smallest]);
            swaps++;
            i = smallest;
        } else break;
    }
    return swaps;
}

int heapify(vector<int>& arr){
    int swaps = 0;
    for(int i = arr.size()/2 - 1; i >= 0; --i){ //the last non-leaf node and goes up to the root.
        swaps += BubbleDown(arr, i);
    }
    return swaps;
}
//If either of these values is greater than or equal to n (array size),that node has no children — meaning it’s a leaf.

// Step 3: Why we start heapifying from index 2
// If you start heapifying at a leaf (like index 3, 4, 5, 6), it has no children, so no swaps are ever needed.
// Starting from index 2 ensures you begin from the lowest parent, fix its subtree first, and then move upward.
// This way, when you get to the root, all its children are already valid heaps.
/*
Why arr.size()/2 - 1?
    In a binary heap (stored as an array):
    The children of node i are at indices 2*i + 1 and 2*i + 2.
    So, all nodes from index arr.size()/2 to arr.size() - 1 are leaves (no children).
    We only need to heapify internal nodes, starting from the last parent node.
    We go backward (from bottom to top), because when you fix lower sub-heaps first, higher ones can rely on them already being valid heaps.
*/

//make_heap(arr.begin(), arr.end(), greater<int>()); doesnt return swaps

int main() {
    /* TODO:
        Write a program that reads an array from its standard input, given as an array between
        square brackets (e.g. `[1,3,5,7,9]` - see week 1), and prints the number of *swaps* that
        would be performed when turning this array into a valid binary *min-heap* using
        the `std::make_heap` function from the C++ Standard Library.

        You can't use the `std::make_heap` function directly, instead you must implement the
        heapify algorithm as described in the lecture, and count the number of swaps performed
        during the process.

        The time complexity of your solution must be O(n), where n is the number of elements
        in the input array.

        Example input:
            [1, 5, 6, 2, 3, 4, 7]
        output:
            2
    */
    vector<int> arr;
    cin >> arr;

    int swaps = heapify(arr);
    cout << swaps << endl;
    return 0;
}


// int bubble_down(std::vector<int>& heap, int i){
//     int n = heap.size();
//     int swap = 0;
//     while(true){
//         int left = 2 * i + 1;
//         int right = 2 * i + 2;
//         int smallest = i;

//         if(left < n && heap[left] < heap[smallest]) smallest = left;
//         if(right < n && heap[right] < heap[smallest]) smallest = right;

//         if(smallest != i){
//             std::swap(heap[i], heap[smallest]);
//             swap++;
//             i = smallest;
//         } else break;
//     }
//     return swap;
// }

// int heapify(std::vector<int> &arr){
//     int swaps = 0;
//     for(int i = arr.size()/2 - 1; i >= 0; i--){  //last non leaf not
//         swaps += BubbleDown(arr, i);
//     }
//     return swaps;
// }

int bubble_up(std::vector<int>& heap, int i){
    int parent = (i - 1) / 2;
    while(i > 0){
    if(heap[i] < heap[parent]){
        std::swap(heap[i], heap[parent]);
        i = parent;
    }else break;
}
}
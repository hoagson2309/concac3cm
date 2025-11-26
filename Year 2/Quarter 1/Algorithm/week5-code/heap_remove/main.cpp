#include <iostream>
#include "utils.h"
#include <vector>

//min-heap

using namespace std;

void BubbleUp(vector<int>& heap, int i){
    while(i > 0){
        int parent = (i - 1) / 2;
        if(heap[i] < heap[parent]){
            swap(heap[i], heap[parent]);
            i = parent;
        } else break;
    }
}

void BubbleDown(vector<int>& heap, int i){
    int n = heap.size();
    while(true){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if(left < n && heap[left] < heap[smallest]) smallest = left;
        if(right < n && heap[right] < heap[smallest]) smallest = right;

        if(smallest != i){
            swap(heap[i], heap[smallest]);
            i = smallest;
        } else break;
    }
}

int main() {
    /* TODO:
        Write a program that reads a binary *min-heap* from its standard input, given as an array,
        and an integer that represents a value to be removed from the heap.

        The program must remove the specified value from the heap while maintaining the heap
        property, and print the resulting heap in the same format as the input. If the value
        is not present in the heap, the program must print the original heap unchanged.

        Example input:
            [3, 4, 10, 23, 50, 90] 50
        Example output:
            [3, 4, 10, 23, 90]
    */
    vector<int> heap;
    int value;

    //Example input:  [3, 4, 10, 23, 50, 90] 50      
    cin >> heap >> value;

    //find index of value
    int idx = -1;
    for(int i = 0; i < (int)heap.size(); i++){
        if(heap[i] == value){
            idx = i;
            break;
        }
    }

    if(idx != -1){
        //replace with last element
        heap[idx] = heap.back();
        heap.pop_back();

        if(!heap.empty()){
            if(idx > 0 && heap[idx] < heap[(idx - 1) / 2]){
                BubbleUp(heap, idx);
            } else {
                BubbleDown(heap, idx);
            }
        }
    }

    cout << heap << endl;
    return 0;
}

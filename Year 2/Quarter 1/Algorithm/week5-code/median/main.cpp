#include <iostream>
#include <queue>
#include <iomanip>
/*
We use two heaps:
    Max-heap (lowers) → stores the smaller half of the numbers
        (so its top element is the largest of the smaller half)
    Min-heap (uppers) → stores the larger half of the numbers
        (so its top element is the smallest of the larger half)
    This setup lets us find the middle value (median) efficiently
*/

using namespace std;

int main() {
    /* TODO:
        Write a program that reads a sequence of numbers from its standard input and, after reading each number,
        prints the median of all numbers read so far.

        You should use two binary heaps to implement the required functionality: a max-heap to store
        the lower half of the numbers, and a min-heap to store the upper half of the numbers.

        The time complexity of your program must be O(n log n), where n is the total number of numbers.
    */
    priority_queue<int> lowers; //priority_queue<int, vector<int>, less<int>> pq; in short 
     //prioritty_queue<int> is a max-heap by default => keep the lower-half of the numbers
    priority_queue<int, vector<int>, greater<int>> uppers; //min-heap => keep the upper half of the numbers

    double median;
    int x;

    while(cin >> x){
        if(lowers.empty() || x <= lowers.top()){
            lowers.push(x);
        } else {
            uppers.push(x);
        }

        if(lowers.size() > uppers.size() + 1){   //only 1 element different not more 
            uppers.push(lowers.top());  
            lowers.pop();
        } else if (uppers.size() > lowers.size() + 1){
            lowers.push(uppers.top());
            uppers.pop();
        }
        // If the lowers (max-heap) has more than one extra element than uppers,
        // move the largest element from lowers (its top) into uppers (min-heap).
        // This makes sense because that element is the largest in the smaller half,
        // so it actually belongs to the upper half.

        if(lowers.size() == uppers.size()){
            median = (lowers.top() + uppers.top()) / 2.0;
        } else if (lowers.size() > uppers.size()){
            median = lowers.top();
        } else {
            median = uppers.top();
        }
        cout << median << " ";  //cannot do cout << median << endl; cuz it prints ex: 1\n2\n...
    }
    cout << endl;  
    return 0;
}

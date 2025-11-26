#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Coord{
    int x, y;
    bool operator==(const Coord& other) const{
        return x == other.x && y == other.y;
    }
};

struct CoordHash{     //converts a key (like a coordinate) into an integer number that can be used to quickly look up items in a hash table (unordered_map, unordered_set, etc).
    size_t operator()(const Coord& c) const{           //^ (XOR) -> mix the bits together
        return hash<int>()(c.x) ^ (hash<int>()(c.y) << 1);  //<< 1 -> shift one of them left by one bit
    }
};
/*
size_t operator()(const Coord& c) const	    This overloads the () operator, so CoordHash acts like a function.
hash<int>()(c.x)	                        Generates a hash for the integer x.
hash<int>()(c.y)	                        Generates a hash for the integer y.
^ (XOR)	                                    Combines the two hashes together so both x and y affect the final hash.
<< 1	                                    Shifts one hash left by 1 bit to mix the bits better and reduce collisions.
*/

int main() {
    /* TODO:
        Write a program that inputs a string consisting of the characters "U", "D", "L", and "R",
        representing movements Up, Down, Left, and Right on a 2D grid, starting from the origin (0, 0).

        The program must then compute and print the top three of *the most visited unique coordinates*
        that are visited during the sequence of movements, including the starting point (0, 0).

        Ties should be broken by the order in which the coordinates were first visited.

        For example, given the input string "UUDLURD", the program must print `(0, 1), (0, 2), (0, 0)`,
        because the visited coordinates are (0, 0), (0, 1), (0, 2), (0, 1), (-1, 1), (-1, 2), (0, 2), and (0, 1).

        The time complexity of your solution must be O(n + 3 log(n)), which can be simplified to O(n + log(n))
        where n is the length of the input string.

        To efficiently store and check for unique coordinates, you should use a hash table (e.g.
        `std::unordered_set` or `std::unordered_map` in C++). Note that you will have to define a custom hash
        function for the coordinate pairs, as well as an equality operator. Also, you must copy the coordinates
        into a vector or similar structure to be able to sort them by their visit counts.

        As a final note, you are not allowed to use the nth_element algorithm from the standard library.
    */
    string moves;
    cin >> moves;
    unordered_map<Coord, pair<int, int>, CoordHash> visits;
    //Coord => visits[{x, y}]
    //pair<int, int> => ex: {1, step}
    //first (1) = number of times this coordinate was visited
    //second (step) = step index when this coordinate was first visited (used for tie-breaking when counts are equal)

    int x = 0, y = 0;
    int step = 0;
    visits[{x, y}] = {1, step++};  //ex: visits[{0,1}] = {3, 1}; => Coordinate (0,1) was visited 3 times => First visited at step 1

    //the moves
    for(char move : moves){
        if(move == 'U') y++;
        else if(move == 'D') y--;
        else if (move == 'L') x--;
        else if(move == 'R') x++;

        Coord current = {x, y};  //current will be used as a key in the unordered_map visits
        if(visits.find(current) == visits.end()){  //visits.find(current) looks for current in the hash table
                                                    //visits.end() represents "not found"
            visits[current] = {1, step++};
        } else {
            visits[current].first++;  //We do not change the first-visit step (second), because that only records the first time it was visited.
         }
    }

    //sort to get top 3                                                    //unordered_map does not store items in order, so we cannot sort it directly.
    vector<pair<Coord, pair<int,int>>> all(visits.begin(), visits.end());  //copy all entries of unordered_map into a vector of the same type
    // pair<Coord, pair<int,int>>
    // all[i].first → the coordinate
    // all[i].second.first → number of visits
    // all[i].second.second → first-visit step
                                                        //[] Capture list — empty here, meaning the lambda doesn’t use any outside variables.
    sort(all.begin(), all.end(), [](auto &a, auto &b){ //{ ... } Body — code that compares a and b and returns true or false.
        if((a.second.first != b.second.first))         // (auto &a, auto &b)Parameters — two elements from the vector all passed by reference. auto automatically deduces their type (pair<Coord, pair<int,int>>).
            return a.second.first > b.second.first; //bigger count comes first
        return a.second.second < b.second.second;   //otherwise smaller step comes first
    });                                           

    int count = 0;
    for(auto &p : all){   //p: reference to each element
        cout << "(" << p.first.x << ", " << p.first.y << ")";
        count++;            //track how many coordinates we printed
        if(count == 3 || count == (int)all.size()) break;
        cout << ", ";
    }
    cout << endl;


    return 0;
}
/*
unordered_map = a mailbox with numbered slots. The hash function (CoordHash) decides which slot your letter goes into.
Copying to a vector = taking all the letters out of the mailbox and putting them on a table. 
Now you can sort or inspect them freely — you don’t need the mailbox numbering anymore.
*/
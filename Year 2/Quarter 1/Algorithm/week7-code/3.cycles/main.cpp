#include <iostream>
#include <unordered_map>
#include "utils.h"
#include <vector>
#include <string>

//DSU structure
std::unordered_map<std::string, std::string> parent;
std::unordered_map<std::string, int> size;

//find function with path compression
std::string find(const std::string &x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]); //path compression
}

bool union_set(const std::string &a, const std::string &b){
    std::string rootA = find(a);
    std::string rootB = find(b);
    if(rootA == rootB) return false; //cuz cycle detected  //if both node have the same root they are already connected
                                     //so adding edge between them would make cycle
    if(size[rootA] < size[rootB]){
        std::swap(rootA, rootB);
    }
    parent[rootB] = rootA;
    size[rootA] += size[rootB];
    return true;
}


int main() {
    /* TODO:
        Write a program that reads a list of edges representing an *undirected* graph from its standard
        input (given as a comma-separated list between square brackets, e.g. `[(A, B),(B, C),(C, D)]`).

        The program must add these edges, one by one, to an initially empty graph, and before adding each
        edge, it must determine whether that edge would introduce a cycle into the graph.

        In case the edge would introduce a cycle, the edge must not be added to the graph and the program
        should stop processing further edges. Otherwise, the edge is added to the graph and the program
        continues with the next edge.

        The program must then print how many edges were added before the first cycle was created.

        Your program must run in `O(m log(n))` time, where `n` is the number of nodes and `m` is the number of
        edges.
    */
   //didnt use sax::edge cuz we dont need weights
    std::vector<std::pair<std::string, std::string>> edges;
    std::cin >> edges;
    int added = 0;

    for(auto &edge : edges){
        //initialize parent and size if new node
        if(!parent.count(edge.first)){
            parent[edge.first] = edge.first;
            size[edge.first] = 1;
        }
        if(!parent.count(edge.second)){
            parent[edge.second] = edge.second;
            size[edge.second] = 1;
        }
        if(!union_set(edge.first, edge.second)){
            //cycle detected
            break;
        }
        added++;
    }
    std::cout << added << "\n";
    return 0;
}

//Ex: A->B->C->C
//A → C
//B → C
//C → C

// New nodes → initialize them:
// parent[A] = A
// parent[B] = B
// size[A] = 1
// size[B] = 1

//Edge 1: (A, B)
// Now union_set(A, B) is called:
// find(A) → A
// find(B) → B
// roots are different → no cycle
// connect them
//parent[B] = A
//size[A] = 2
// A is root
// B → A
// => added = 1

//  Edge 2: (B, C)
// New node C:
// parent[C] = C
// size[C] = 1
// Run union_set(B, C):
// find(B) → find(A) → A (path compression)
// find(C) → C
// Roots are different → no cycle
// Attach smaller tree to larger:
// parent[C] = A
// size[A] = 3
// Edge added!
// added = 2

//Step	Edge	RootA	RootB	Cycle?	Added count
// 1	(A, B)	  A	      B	     No	         1
// 2	(B, C)	  A	      C	     No	         2
// 3	(C, D)	  A	      D	     No	         3
// 4	(A, D)	  A	      A	     Yes	    stop

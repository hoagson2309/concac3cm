#include <iostream>
#include "utils.h"   // for reading vectors
#include <unordered_map>
#include <unordered_set>
#include <vector>

int CountPath(int current, int end, std::unordered_map<int, std::vector<int>>& graph, std::unordered_set<int>& visited){
    if(current == end) return 1; //path found

    visited.insert(current);
    int total = 0;

    for(int neighbor : graph[current]){
        if(!visited.count(neighbor)){   //contain return true false, count return 1, 0
            total += CountPath(neighbor, end, graph, visited);
        }
    }
    visited.erase(current);  
    return total;
}

// 4 <- 1 -> 2 -> 3
//2 path
//1 → 2 → 3
//1 → 4 → 2 → 3

// If we don’t erase 1 after exploring,
// then when we backtrack and try another route (like 1 → 4 → ...),
// 1 is still marked as visited —  so that path gets blocked.
// visited.insert(current) → “I’m visiting this node now.”
// visited.erase(current) → “I’m done; let’s allow it for other paths.”

int main() {
    /* TODO:
        Write a program that reads a list of edges representing an *undirected* graph from
        its standard input (given as a comma-separated list between square brackets),
        followed by two integers representing the start and end nodes.

        The program must then compute and print the number of *different* "simple" paths
        from the start node to the end node. A simple path is a path that does not visit
        any node more than once - in other words, cycles are not allowed.
    */
    std::vector<std::pair<int,int>> edges;
    int start, end;
    if(!(std::cin >> edges >> start >> end)){
        std::cerr << "Failed reading input" << std::endl;
        return 1;
   }
    std::unordered_map<int, std::vector<int>> graph;
    for(auto& edge : edges){
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first); // undirected graph
    }
    std::unordered_set<int> visited;
    int total_paths = CountPath(start, end, graph, visited);

    std::cout << total_paths << std::endl;

    return 0;
}

//EX:
//Edges: [(0,1),(0,2),(1,2),(2,3)]
//Start: 0
//End: 3
    //0 → 1 → 2 → 3 (YES)
    //0 → 2 → 3 (YES)
    //0 → 2 → 1 → 2 → 3 (NO) (not simple, revisits 2)
    
//DONT NEED all_nodes because:
    // We only care about paths starting at start and ending at end.
    // We don’t have to explore every node in the graph — only the part that’s reachable from start.
    // The recursion begins at start and naturally explores all neighbors.
    // If a node is not connected to start, it will never be visited anyway.

    //In largest component or cycle detection, we needed all_nodes 
    //because the graph can have multiple disconnected components, and we must check every node to ensure we didn’t miss anything.
#include <iostream>
#include "utils.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <algorithm> //std::reverse

// DFS-based topological sort works like this:
    // Start at an unvisited node.
    // Recursively visit all its neighbors (dependencies).
    // When finished visiting all neighbors, add the node to the ordering.
    // Use visited/visiting states to detect cycles.

//0: unvisited
//1: visiting
//2: visited
bool dfs(char node, const std::unordered_map<char, std::vector<char>>& graph, std::unordered_map<char, int>& state, std::vector<char>& ordering){
    state[node] = 1; //visiting

    for(char neighbor : graph.at(node)){
        if(state[neighbor] == 1) return true; //cycle detected
        if(state[neighbor] == 0){
            if(dfs(neighbor, graph, state, ordering)) return true;
        }
    }
    state[node] = 2; //visited
    ordering.push_back(node);
    return false;
}

int main() {
    /* TODO:
        Write a program that reads a list of dependencies from its standard input (given
        as a comma-separated list between square brackets, e.g. `[(A,B),(B,C)]`), where
        each dependency `(A,B)` indicates that task A must be completed before task B
        can be started.

        The program must then compute and print a valid order in which the tasks can be
        completed, or `CYCLE` if no such order exists (i.e., if there is a cycle in the
        dependencies).

        If a valid order exists, it must be printed as a comma-separated list between
        square brackets (e.g. `[A,B,C]`).
    */
    std::vector<std::pair<char, char>> edges;
    if(!(std::cin >> edges)){
        std::cerr << "Failed reading input" << std::endl;
        return 1;
    }

    std::unordered_map<char, std::vector<char>> graph;
    std::unordered_set<char> all_nodes;
    for(const auto& edge : edges){
        graph[edge.first].push_back(edge.second);
        graph[edge.second]; //ensure node exist
        all_nodes.insert(edge.first);
        all_nodes.insert(edge.second);
    }


    std::unordered_map<char, int> state;
    std::vector<char> ordering;
    for(char node : all_nodes){
        state[node] = 0;
    }
    //dfs
    for(char node : all_nodes){
        if(state[node] == 0){
            if(dfs(node, graph, state, ordering)){
                std::cout << "CYCLE" << std::endl;
                return 0;
            }
        }
    }
    //[C, B, A] => [A, B, C]
    //reverse to get correct topological order
    std::reverse(ordering.begin(), ordering.end());

    std::cout << "[";
    for(size_t i = 0; i < ordering.size(); i++){
        std::cout << ordering[i];
        if(i < ordering.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}

// for(char node : all_nodes){
//         if(state[node] == 0){
//             if(dfs(node, graph, state, ordering)){
    // looping through all_nodes guarantees:
    // We start DFS from every node that hasn’t been visited yet.
    // This ensures we catch cycles and include all tasks in the final order.
    //This is necessary because topological sorting requires a full ordering of all nodes, not just those reachable from one start node.


//dfs(start, graph, visited);
    //We only care about whether there’s a path from one specific node to another.
    // You start from a given start node and explore as far as you can go.
    // You don’t need to visit all other parts of the graph — only the connected component that includes start.
    // So it’s totally fine to run a single DFS from the start node.

//In DFS topological sort, we add a node to the list after exploring all of its dependencies.
    //Nodes with no outgoing edges (no dependencies) get added first.
    //Nodes that depend on others get added later.
    //So the result list is backwards — it’s in reverse topological order.
    //DFS visiting order:
        //ex: (A, B)  →  A before B
        //    (B, C)  →  B before C
            //Visit A → go to B → go to C
            //Add C, then B, then A → ordering = [C, B, A] so then we have to use std::reverse
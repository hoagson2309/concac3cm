#include <iostream>
#include "utils.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

int dfs(char node, std::unordered_map<int, std::vector<int>>& graph, std::unordered_set<int>& visited){
    visited.insert(node);
    int size = 1;
    for(char neighbor : graph.at(node)){
        if(!visited.contains(neighbor)){
            size += dfs(neighbor, graph, visited);
        }
    }
    return size;
}

int main()
{
    /* TODO:
        Write a program that reads a list of edges representing an *undirected* graph
        from its standard input (given as a comma-separated list between square brackets).
        The graph may be disconnected, meaning that there may be multiple connected components.

        The program must then compute and print the size of the largest connected component
        in the graph.

        The time complexity of your solution must be `O(n + m)`, where `n` is the number of nodes
        and `m` is the number of edges in the graph.
    */
    std::vector<std::pair<int, int>> edges;
    if(!(std::cin >> edges)){
        std::cerr << "Failed reading input" << std::endl;
        return 1;
    }

    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_set<int> all_nodes;
    for(const auto& edge : edges){
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);  //undirected graph
        all_nodes.insert(edge.first);
        all_nodes.insert(edge.second);
    }

    std::unordered_set<int> visited;
    int largest = 0;

    for(int node : all_nodes){
        if(!visited.contains(node)){
            int size = dfs(node, graph, visited);
            largest = std::max(largest, size);
        }
    }

    std::cout << largest << std::endl;
    return 0;
}

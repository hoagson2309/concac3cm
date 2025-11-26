#include <iostream>
#include "utils.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

bool dfs(char node,
         const std::unordered_map<char, std::vector<char>>& graph,
         std::unordered_map<char, int>& state,
         std::vector<char>& path,
         char &cycle_start)
{
    state[node] = 1;   // visiting
    path.push_back(node);

    for (char neighbor : graph.at(node)) {
        if (state[neighbor] == 0) {              // unvisited
            if (dfs(neighbor, graph, state, path, cycle_start))
                return true;                  
        }
        else if (state[neighbor] == 1) {         
            cycle_start = neighbor;  //A
            return true;
        }
    }
    state[node] = 2;      // finished
    path.pop_back();      // backtrack
    return false;
}

int main() {
    std::vector<std::pair<char, char>> edges;
    std::cin >> edges;

    if (std::cin.fail()) {
        std::cerr << "Failed to read graph edges from input." << std::endl;
        return 1;
    }

    // Build graph
    std::unordered_map<char, std::vector<char>> graph;
    std::unordered_set<char> all_nodes;

    for (auto& edge : edges) {
        graph[edge.first].push_back(edge.second);
        graph[edge.second];
        all_nodes.insert(edge.first);
        all_nodes.insert(edge.second);
    }

    std::unordered_map<char, int> state;
    for (char node : all_nodes) state[node] = 0;

    std::vector<char> path;
    char cycle_start = 0;
    bool found = false;

    // DFS for each component
    for (char node : all_nodes) {
        if (state[node] == 0) {
            if (dfs(node, graph, state, path, cycle_start)) {
                found = true;
                break;
            }
        }
    }

    if (!found) {
        std::cout << "No cycle found" << std::endl;
        return 0;
    }

    // Extract cycle from path
    auto it = std::find(path.begin(), path.end(), cycle_start);
    std::vector<char> cycle(it, path.end());

    // Print formatted cycle
    for (size_t i = 0; i < cycle.size(); i++) {
        std::cout << cycle[i];
        if (i < cycle.size() - 1) std::cout << " -> ";
    }
    std::cout << " -> " << cycle[0] << std::endl;

    return 0;
}

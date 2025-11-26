#include <iostream>
#include <unordered_map>
#include <algorithm> // std::find
#include "utils.h"
#include <unordered_set>

bool dfs(int node, std::unordered_map<int, std::vector<int>>& graph, 
    std::unordered_map<int, int>& state, 
    std::unordered_map<int, int>& parent,   //track parent tp reconstruct cycle
    int& cycle_start, int& cycle_end){

    state[node] = 1; //1: visiting

    for(char neighbor : graph.at(node)){
        if(state[neighbor] == 0){
            parent[neighbor] = node;
            if(dfs(neighbor, graph, state, parent, cycle_start, cycle_end)) return true;
        } else if(state[neighbor] == 1){  //cycle detected
            cycle_start = neighbor;    //1 is where the cycle starts (the node we loop back to)
            cycle_end = node;   //3 is where the cycle ends (the node that creates the back edge)
            return true;
        }
    } 
    //if visited
    state[node] = 2;
    return false;
}

int main() {
    /* TODO:
        Write a program that reads a list of edges representing a *directed* graph
        from its standard input (given as a comma-separated list between square
        brackets, e.g. `[(0,1),(1,2),(2,0)]` - see assignment 1).

        The program must then determine whether the graph contains a cycle.
        If a cycle exists, the program must print the edges in the cycle as a
        comma-separated list between square brackets (e.g. `[(0,1),(1,2),(2,0)]`),
        otherwise it must print `[]`.
    */
    std::vector<std::pair<int,int>> edges;
    if(!(std::cin >> edges)){
        std::cerr << "Failed reading input\n";
        return 1;
   }

    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_set<int> all_nodes;
    for(const auto& edge : edges){
        graph[edge.first].push_back(edge.second);
        graph[edge.second]; //ensure node exist in the map
        all_nodes.insert(edge.first);
        all_nodes.insert(edge.second);
    }

    std::unordered_map<int, int> state; 
    std::unordered_map<int, int> parent;
    for(int node : all_nodes){
        state[node] = 0;
    } 

    int cycle_start = -1, cycle_end = -1;
    bool found = false;                     

    for(int node : all_nodes){
        if(state[node] == 0){
            if(dfs(node, graph, state, parent, cycle_start, cycle_end)){
                found = true;
                break;
            }
        }
    }
    if(!found){
        std::cout << "[]" << std::endl;
        return 0;
    }

    //reconstruct cycle edges
    std::vector<std::pair<int,int>> cycle_edges;
    int current = cycle_end;    
    cycle_edges.push_back({current, cycle_start}); //Ex: (3, 1)  //adds the edge that closes the cycle to make sure the cycle complete //the closing edge that makes the loop exist in the first place.
    while(current != cycle_start){
        int prev = parent[current];
        cycle_edges.push_back({prev, current});    //ex: (2,3), (1,2)
        current = prev;
    }
    //OR PUT THIS LINE AFTER THE LOOP FOR THE CLOSING EDGE
    //cycle_edges.push_back({cycle_end, cycle_start});
    
    std::reverse(cycle_edges.begin(), cycle_edges.end()); //then reverse => [(1,2), (2,3), (3,1)]

    std::cout << "[";
    for(size_t i = 0; i < cycle_edges.size(); i++){
        std::cout << "(" << cycle_edges[i].first << ", " << cycle_edges[i].second << ")";
        if(i != cycle_edges.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}

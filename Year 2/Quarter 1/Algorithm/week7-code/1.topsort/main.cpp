#include <iostream>
#include "utils.h"   // for reading vectors
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm> //std::min


std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
std::unordered_map<std::string, int> state; 
std::vector<std::string> topo;
bool has_cycle = false;

void dfs(const std::string& u){
    state[u] = 1;
    for(auto &[v, w] : graph[u]){   //v: dest node(), w: edge weight(int)
        if(state[v] == 0) dfs(v);
        else if(state[v] == 1) has_cycle = true;
    }
    state[u] = 2;
    topo.push_back(u);  //C->B->A
}

int main() {
    /* TODO:
        Write a program that reads a list of edges representing a *weighted directed* graph from its standard input.
        The graph is given as a comma-separated list between square brackets, e.g. `[(A, B, 5),(B, C, 10),(C, D, 2)]`.
        Use the class `Edge<T>` defined in `utils.h` to represent the edges of the graph.

        The program must check if the graph contains a cycle, and if it does not it must compute the shortest path (i.e. with the lowest path costs) between two given nodes.
        It must do so by topologically sorting the nodes of the graph and then using this ordering to compute the shortest path, in `O(n + m)` time, where `n` is the number of nodes and `m` is the number of edges in the graph.
    */
    std::vector<sax::edge<std::string>> edges;  //src, dest, weight(int)
    std::cin >> edges;
    std::string start, end;
    std::cin >> start >> end;
    
    std::unordered_set<std::string> all_nodes;
    for(auto &edge : edges){
        graph[edge.src].push_back({edge.dest, edge.weight});
        all_nodes.insert(edge.src);
        all_nodes.insert(edge.dest);
    }
    for(auto &node : all_nodes){
        if(state[node] == 0){
            dfs(node);
        }
    }
    if(has_cycle){
        std::cout << "CYCLE\n";
        return 0;
    }
    std::reverse(topo.begin(), topo.end()); //=> A->B->C

    const int INF = 1e9;  //infinity
    std::unordered_map<std::string, int> dist;  //initially dont know the distance so set the distance INF 
    for(auto &node : all_nodes) dist[node] = INF;
        dist[start] = 0;  //base case

    for(auto &u : topo){
        if(dist[u] != INF){
            for(auto &[v, w] : graph[u]){
                dist[v] = std::min(dist[v], dist[u] + w);
            }
        }
    }
    if(dist[end] == INF){
        std::cout << "NO PATH\n";
    } else {
        std::cout << dist[end] << "\n";
    }
    return 0;
}

//Ex: graph
// A → B (5)
// A → C (2)
// B → C (1)
    //initialize:
    // dist[A] = 0
    // dist[B] = INF
    // dist[C] = INF
        //topo order 
        //at A : 
            // dist[B] = min(INF, 0 + 5) = 5
            // dist[C] = min(INF, 0 + 2) = 2
        //at B:
            // dist[C] = min(2, 5 + 1) = 2  // no change

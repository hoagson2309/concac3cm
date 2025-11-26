// #include <iostream>
// #include "utils.h"
// #include "coordinate.h"
// #include <unordered_map>
// #include <cmath>
// #include <algorithm>
// #include <vector>
// #include <edge.h>
// #include <string>

// std::unordered_map<std::string, std::string> parent;
// std::unordered_map<std::string, int> size;

// std::string find(const std::string &x){
//     if(parent[x] == x) return x;
//     return parent[x] = find(parent[x]);
// }

// bool union_set(const std::string &a, const std::string &b){
//     std::string rootA = find(a);
//     std::string rootB = find(b);
//     if(rootA == rootB) return false; //cycle detect

//     if(size[rootA] < size[rootB]){
//         std::swap(rootA, rootB);
//     }
//     parent[rootB] = rootA;
//     size[rootA] += size[rootB];
//     return true;
// }   

// // In an MST or any undirected graph, there can be multiple routes between two nodes.
// // The old DFS stopped after the first one it found,
// // but the new DFS tries all paths and keeps the smallest cost.
// void dfs(const std::string &current, const std::string &target, std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> &graph,
//         std::unordered_map<std::string, bool> &visited, int current_cost, int &min_cost){
//     if(current == target){
//         min_cost = std::min(min_cost, current_cost);
//         return;
//     } 
//     visited[current] = true;
//     for(auto &[neighbor, w] : graph[current]){
//         if(!visited[neighbor]){
//             dfs(neighbor, target, graph, visited, current_cost + w, min_cost);
//         }
//     }
//     visited[current] = false;
// }

// int main() {
//     /* TODO:
//         Given an undirected graph, write a program that computes the minimum spanning tree of the graph using
//         either Prim's or Kruskal's algorithm, and then computes the shortest path (i.e., with the lowest path
//         cost) between two given nodes on the minimum spanning tree.

//         The program receives a list of edges representing an *undirected weighted* graph from its standard
//         input (given as a comma-separated list between square brackets, e.g. `[(A, B, 5),(B, C, 10),(C, D, 2)]`),
//         followed by two characters representing the start and end nodes (e.g. `A D`) - similar to assignment 1
//         of this week.
        
//         The program's output must be the cost of the shortest path between the start and end nodes on the minimum
//         spanning tree, or `NO PATH` if there is no path between the start and end nodes.
//     */
//     //ex: [(A,B,5),(B,C,10),(C,D,2)] A D
//     std::vector<sax::edge<std::string>> edges;
//     std::cin >> edges;
//     std::string start, end;
//     std::cin >> start >> end;

//     for(auto &edge : edges){
//         if(!parent.count(edge.src)){
//             parent[edge.src] = edge.src;  //set parent and size for later use in union_set
//             size[edge.src] = 1;
//         }
//         if(!parent.count(edge.dest)){
//             parent[edge.dest] = edge.dest;
//             size[edge.dest] = 1;
//         }
//     }
//     //Kruskal’s algorithm - build MST
//     std::sort(edges.begin(), edges.end(), [](auto &a, auto &b){
//         if (a.weight != b.weight) return a.weight < b.weight;
//         if (a.src != b.src) return a.src < b.src;
//         return a.dest < b.dest;
//     });

//     std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
//     for(auto &edge : edges){
//         if(union_set(edge.src, edge.dest)){  //build graph after union_set to avoid cycle
//             graph[edge.src].push_back({edge.dest, edge.weight});
//             graph[edge.dest].push_back({edge.src, edge.weight});
//         }
//     }
//     std::unordered_map<std::string, bool> visited;
//     const int INF = 1e9;
//     int min_cost = INF;

//     dfs(start, end, graph, visited, 0, min_cost);

//     if (min_cost != INF){
//         std::cout << min_cost << std::endl;
//     }
//     else{
//         std::cout << "NO PATH" << std::endl;
//     }
//     return 0;
// }


// // When multiple edges have the same weight, Kruskal’s algorithm can choose any of them first.
// // That means your MST structure can change slightly depending on how std::sort() orders equal-weight edges (which isn’t guaranteed to be consistent).
// // By adding tie-breakers (sorting by src and then dest), you made the sorting deterministic — edges with the same weight are always processed in the same order.
// // This ensures Kruskal’s algorithm always builds the same MST, matching what the test expects.

// //the BEFORE code for dfs:
// //     bool dfs(..., int current_cost, int &min_cost) {
// //     if (current == target) {
// //         min_cost = std::min(min_cost, current_cost);
// //         return true;
// //     }
// //     visited[current] = true;
// //     bool found = false;
// //     for (auto &[neighbor, w] : graph[current]) {
// //         if (!visited[neighbor]) {
// //             if (dfs(neighbor, target, graph, visited, current_cost + w, min_cost))
// //                 found = true;
// //         }
// //     }
// //     visited[current] = false;
// //     return found;
// // }

// //Removed the bool return value → now it explores all possible paths, not just the first one found.
// // Before: it stopped searching as soon as it found one path, even if it wasn’t the shortest.

// // Now: it continues searching all paths and keeps updating min_cost when a smaller one is found.
// // Removed the early return after finding a path -> ensures every possible route is checked.
// // Made dfs return void -> simplifies recursion and focuses only on updating min_cost.
// // Result:
// // Now DFS fully explores the MST, finds all paths between the two nodes, and returns the true minimum cost, not just the first valid one.
// // That’s why your test went from “got 6, expected 5” -> correct output 5.


#include <iostream>
#include "utils.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include "edge.h"

std::unordered_map<std::string, std::string> parent;
std::unordered_map<std::string, int> size;

std::string find(const std::string &x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

bool union_set(const std::string& a, const std::string& b){
    std::string rootA = find(a);
    std::string rootB = find(b);
    if(rootA == rootB) return false; //cycle detected

    if(size[rootA] < size[rootB]){
        std::swap(rootA, rootB);
    }
    parent[rootB] = rootA;
    size[rootA] += size[rootB];
    return true;
}

void dfs (std::string &current, std::string &target, std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> &graph, 
    std::unordered_map<std::string, bool> &visited,
    int current_cost, int &min_cost){
        if(current == target){
            min_cost = std::min(min_cost, current_cost);
            return;  //found
        }
        visited[current] = true;
        for(auto &[neighbor, w] : graph[current]){
            if(!visited[neighbor]){
                dfs(neighbor, target, graph, visited, current_cost + w, min_cost);
            }
        }
        visited[current] = false;
    }

int main(){
    std::vector<sax::edge<std::string>> edges;
    std::cin >> edges;
    std::string start, end;
    std::cin >> start >> end;

    //setting representative
    for(auto &edge : edges){ 
        if(!parent.count(edge.src)){
            parent[edge.src] = edge.src;
            size[edge.src] = 1;
        }
        if(!parent.count(edge.dest)){
            parent[edge.dest] = edge.dest;
            size[edge.dest] = 1;
        }
    }

    //sort edges
        std::sort(edges.begin(), edges.end(), [](auto &a, auto &b){  //SORT OUTSIDE THE LOOP
            if(a.weight != b.weight) return a.weight < b.weight; //smaller weight comes first OMG REMEMBER THIS SHIT
            if(a.src != b.src) return a.src < b.src;
            return a.dest < b.dest;
        });
    
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
    for(auto &edge : edges){
        if(union_set(edge.src, edge.dest)){
        graph[edge.src].push_back({edge.dest, edge.weight});
        graph[edge.dest].push_back({edge.src, edge.weight});
        }
    }
    std::unordered_map<std::string, bool> visited;
    int INF = 1e9;
    int min_cost = INF;  //min_cost unknown as first so set inf

    dfs(start, end, graph, visited, 0, min_cost);

    if (min_cost != INF){ //check if min_cost updated
        std::cout << min_cost << std::endl;
    }
    else{
        std::cout << "NO PATH" << std::endl;
    }
    return 0;
}
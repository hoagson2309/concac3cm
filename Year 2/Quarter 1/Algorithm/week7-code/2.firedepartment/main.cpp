// #include <iostream>
// #include "utils.h"   // for reading vectors
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>
// #include <string>
// #include <queue>
// #include <algorithm>

// int main() {
//     /* TODO:
//         A municipality wants to place a fire department in one of its neighborhoods such that the sum of the distances
//         from the fire department to all other neighborhoods is minimized.

//         Write a program that computes its optimal placement and prints the smallest sum of distances from the fire
//         department to all other neighborhoods.

//         The program must read a list of edges representing an *undirected* graph from its standard input (given as a
//         comma-separated list between square brackets, e.g. `[(A, B, 5),(B, C, 10),(C, D, 2)]`), where each edge `(A, B, w)`
//         indicates that there is a road between neighborhoods A and B with length w.

//         The program must then compute at which neighborhood the fire department should be placed, and print the neighborhood
//         as well as the sum of the distances from that neighborhood to all other neighborhoods (e.g. `B, 15`).

//         The time complexity of your solution must be `O(n m log n)`, where `n` is the number of nodes and `m` is the number
//         of edges in the graph.
//     */
//     std::vector<sax::edge<std::string>> edges;
//     std::cin >> edges;
    
//     std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
//     std::unordered_set<std::string> all_nodes;

//     for(auto& edge : edges){
//         graph[edge.src].push_back({edge.dest, edge.weight});
//         graph[edge.dest].push_back({edge.src, edge.weight});
//         all_nodes.insert(edge.src);
//         all_nodes.insert(edge.dest);
//     }

//     const int INF = 1e9;
//     std::string best_node;
//     int best_sum = INF;

//     //dijkstra from each node
//     for(auto& start : all_nodes){
//         std::unordered_map<std::string, int> dist;
//         for(auto &node : all_nodes) dist[node] = INF;
//         dist[start] = 0;

//         //in Dijkstra’s algorithm, we want the smallest distance (the “closest” node first).
//         //So we need to flip the order to make it a min-heap => that’s what std::greater<> does.
//         std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<>> pq; //min-heap
//         pq.push({0, start});

//         while(!pq.empty()){
//             auto [d, u] = pq.top();  //u: current node being visited  //top() gives node with the smallest dist cuz min-heap smaller comes first
//             pq.pop();                //d: current distance from start to u  //pop() the smallest
//             if(d > dist[u]) continue;  //we maay input shorter path to the same node later. If this path (d) is already worse (longer) than the best-known path to u, skip it.

//             for(auto &[v, w] : graph[u]){
//                 if(dist[v] > dist[u] + w){
//                     dist[v] = dist[u] + w;
//                     pq.push({dist[v], v});
//                 }
//             }
//         }
//         int total = 0;
//         for(auto &[n, d] : dist){
//             if(d != INF) total += d;
//         }

//         if(total < best_sum){
//             best_sum = total;
//             best_node = start;
//         }
//     }
//     std::cout << best_node << ", " << best_sum << "\n";
//     return 0;
// }

// // Start	To A	To B	To C	Total
// // A	     0	     2	     5	      7
// // B	     2	     0	     3	      5
// // C	     5	     3	     0	      8

// // Start = A => total = 7
// // => best_sum = 7, best_node = "A"

// // Start = B → total = 5
// // => 5 < 7 => update: best_sum = 5, best_node = "B"

// // Start = C => total = 8
// // => 8 > 5 => no update


#include <iostream>
#include "utils.h"   // for reading vectors
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>

int main(){
    std::vector<sax::edge<std::string>> edges;
    std::cin >> edges;
    if(!(std::cin)){
        std::cerr << "Failed reading edges" << std::endl;
    }

    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
    std::unordered_set<std::string> all_nodes;
    for(auto &edge : edges){
        graph[edge.src].push_back({edge.dest, edge.weight});
        graph[edge.dest].push_back({edge.src, edge.weight});
        all_nodes.insert(edge.src);
        all_nodes.insert(edge.dest);
    }

    const int INF = 1e9;
    std::string best_node;
    int best_sum = INF;

    for(auto &start : all_nodes){
        std::unordered_map<std::string, int> dist;
        for(auto &node : all_nodes){
            dist[node] = INF;
        }
        dist[start] = 0;
    
        std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<>> pq;
        pq.push({0, start});

        while(!pq.empty()){
            auto [d, u] = pq.top();
            pq.pop();
            if( d > dist[u]) continue; 
            for(auto &[v, w] : graph.at(u)){
                if(dist[u] != INF){
                    if(dist[v] > dist[u] + w){
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});
                    }
                }
            }
        } 
        int total = 0;
        for(auto &[u, d] : dist){
            if(d != INF) total += d;
        }
        if(total < best_sum){
            best_sum = total;
            best_node = start;
        }
    }
    std::cout << best_node << ", " << best_sum << "\n";
    return 0;

}
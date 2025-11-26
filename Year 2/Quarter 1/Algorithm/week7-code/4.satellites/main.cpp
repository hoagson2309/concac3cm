#include <iostream>
#include "utils.h"
#include "coordinate.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <vector>
#include <edge.h>

// Euclidean Distance
// For two coordinates (x1, y1, z1) and (x2, y2, z2):
// sqrt((x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2)

// Kruskal’s algorithm steps:
    // Compute all possible edges (for every pair of satellites).
    // Sort edges by weight (distance).
    // Initialize DSU (each satellite is its own parent).
    // For each edge (smallest first):
    // If connecting them doesn’t form a cycle (union_set() returns true), add its weight to total cost.
    // Stop when you have added n − 1 edges.


//cannot use sax::edge cuz it's always int weight
struct Edge{
    int src, dest;
    double weight;
};

// We use std::vector<int> parent, size; instead of unordered_map because:
    // Satellite nodes are numbered 0 to n−1, not arbitrary names.
    // Vectors allow direct fast access (O(1)), while maps need hash lookups (slower).
    // We can initialize all nodes easily with a simple loop. 
// std::unordered_map<int, int> parent;
// std::unordered_map<int, int> size;
std::vector<int> parent, size; 

int find(int x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);  //path compression
}

bool union_set(int a, int b){
    int rootA = find(a);
    int rootB = find(b);
    if(rootA == rootB) return false; //cycle detected

    if(size[rootA] < size[rootB]){
        std::swap(rootA, rootB);
    }
    parent[rootB] = rootA;
    size[rootA] += size[rootB];
    return true;
}

// //compute Euclidean distance between two coordinates
// double distance(const sax::coordinate &a, const sax::coordinate &b){
//     double dx = a.x - b.x;
//     double dy = a.y - b.y;
//     double dz = a.z - b.z;
//     return std::sqrt(dx*dx + dy*dy + dz*dz);
// }

int main()
{
//     /* TODO:
//         A communication network consists of a number of satellites that need to be connected to each other.
//         Satellites can be connected directly to each other, or indirectly through other satellites - similar to
//         how the internet works.

//         Since communication is costly, the network must be designed such that the total cost of connecting all
//         satellites is minimized. Also, the network must not contain any cycles, since that would be a waste of
//         resources. In other words, there should be just one unique communication path between any two satellites.

//         Given (x, y, z) coordinates of satellites, write a program that computes the minimum cost to connect all
//         satellites in a communication network, where the cost to connect two satellites is given by the Euclidean
//         distance between them.

//         The program receives a list of satellites from its standard input (given as a comma-separated list between
//         square brackets, e.g. `[(0,0,0),(1,1,1),(2,2,2)]`), where each satellite is represented by its (x, y, z)
//         coordinates. Use the `sax::coordinate` type to represent the coordinates of a satellite.

//         The program must then compute the minimum cost to connect all satellites in a communication network, and print
//         this cost to its standard output with two digits after the decimal point (e.g. `3.41`).
//    */
    std::vector<sax::coordinate> satellites;
    std::cin >> satellites;

    int n = satellites.size();
    if(n <= 1){
        std::cout << "0.00\n";
        return 0;
    }

    std::vector<Edge> edges;

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            edges.push_back({i, j, satellites[i].distance_to(satellites[j])});
        }
    }
    //ex: satellites[0] = (0, 0, 0)  => index = 0
    //    satellites[1] = (1, 0, 0)  => index = 1
    //    satellites[2] = (0, 1, 0)  => index = 2

    //edges.push_back({0, 1, satellites[0].distance_to(satellites[1])});
    //=> Edge created: {src=0, dest=1, weight=1.00}

    //edges.push_back({0, 2, satellites[0].distance_to(satellites[2])});
    //=> Edge created: {src=0, dest=2, weight=1.00}

    //edges.push_back({1, 2, satellites[1].distance_to(satellites[2])});
    //=>Edge created: {src=1, dest=2, weight=1.41}

    //sort edges by weight
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){
        if (a.weight != b.weight) return a.weight < b.weight;
        if (a.src != b.src) return a.src < b.src;
        return a.dest < b.dest;
    });

    //using vector not unordered_map so need to change to this
    parent.resize(n);           //allocate space for all n satellites
    size.resize(n, 1);          //size is initialized to 1 for each node
    //DSU - set parent and size for later use in union_set and find
    for(int i = 0; i < n; i++){
        parent[i] = i;
        // size[i] = 1;
    }

    double total = 0.0;
    int edges_used = 0;

// Kruskal’s Algorithm
    // Kruskal doesn’t care about the coordinates, only about the indices (0,1,2).
    // It uses these indices in the DSU (Union-Find) to merge sets:
    // Connect 0–1 
    // Connect 0–2 
    // Don’t connect 1–2 (would make a cycle )
    // Minimum total = 1.00 + 1.00 = 2.00

    for(auto &edge : edges){
        if(union_set(edge.src, edge.dest)){
            total += edge.weight;
            edges_used++;

            if(edges_used == n-1){
                break; //MST complete
            } 
        }
    }
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    std::cout << total << "\n";
    return 0;
}

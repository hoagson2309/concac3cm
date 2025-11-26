#include <iostream>
#include "utils.h"   // for reading vectors
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>


//std::unordered_map<char, std::vector<char>>& graph: this is the adjacency list of the graph that BFS will read to know which nodes are connected. 
//unordered_map<char, vector<char>> => Maps each node (char) to its neighbors (vector<char>).

//std::unordered_map<char, char>& parent: this keeps track of how each node was reached so we can reconstruct the path later
bool bfs(char start, char end, const std::unordered_map<char, std::vector<char>>& graph, std::unordered_map<char, char>& parent){
    std::unordered_set<char> visited;
    //unordered_set<char> => Stores unique characters (char) in no particular order
    std::queue<char> q;

    visited.insert(start);
    q.push(start);

    while(!q.empty()){
        char node = q.front();
        q.pop();  //pop always remove the front element of the queue

        if(node == end){
            return true; //found the end node
        }   

        for(char neighbor : graph.at(node)){
            if(!visited.contains(neighbor)){
                visited.insert(neighbor);
                parent[neighbor] = node;  //track how we reached this neighbor ex: neigbor = B => parent[B] = A -> record that we reached B via A
                q.push(neighbor);
            }
        }
    }
    return false;
}

int main() {
    /* TODO:
        Write a program that reads a list of edges representing an *undirected* graph
        from its standard input (given as a comma-separated list between square brackets),
        followed by two characters representing the start and end nodes.

        The program must then find out whether there exists a path from the start node to
        the end node. If such a path exists, the program must print the path as a
        comma-separated list of edges between square brackets (e.g. `[(A, B), (B, C)]`),
        otherwise it must print `[]`.
    */
   //std::pair is useful when you want to store two related values together as a single object.
    std::vector<std::pair<char, char>> edges;
    char start, end;

    //[(A, B),(B, C),(C, D)] A D
    if(!(std::cin >> edges >> start >> end)){
        std::cerr << "Error reading input" <<std::endl;
        return 1;
    }

    //build adjacency list for undirected graph
    std::unordered_map<char, std::vector<char>> graph;
    for(const auto& edge : edges){
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }

    //parent map for reconstructing the path
    std::unordered_map<char, char> parent;

    bool found = bfs(start, end, graph, parent);

    if(!found){
        std::cout << "[]" << std::endl;
        return 0;
    }

    //reconstruct path (end -> start)
    std::vector<std::pair<char, char>> path;
    char current = end;
    while(current != start){
        char prev = parent[current];  //B = parent[C]
        path.push_back({prev, current}); //Add the edge (prev, current) to the path. (B, C)
        current = prev; //Move backward in the path — now current becomes the parent node. This continues until we reach the start node.
    } 

    //reverse path so it goes from start to end
    std::reverse(path.begin(), path.end());   

    std::cout << "[";
    for(size_t i = 0; i < path.size(); i++){
        std::cout << "(" << path[i].first << ", " << path[i].second << ")";
        if(i < path.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    return 0;
}

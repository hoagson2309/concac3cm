#include <iostream>
#include "utils.h"   // for reading vectors
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>


int bfs_shortest_path(char start, char end, const std::unordered_map<char, std::vector<char>>& graph){
    std::unordered_set<char> visited;
    std::queue<std::pair<char, int>> q;  //queue of node + distance from start

    visited.insert(start);
    q.push({start, 0}); //start node, distance 0

    while(!q.empty()){
        auto[node, dist] = q.front();
        q.pop();

        if(node == end){
            return dist;    //found shortest path
        }

        for(char neighbor : graph.at(node)){
            if(!visited.contains(neighbor)){
                visited.insert(neighbor);
                q.push({neighbor, dist + 1}); // increasing the dist by 1 everytime going from node to neighbor
            }
        }
    }
    return -1; //end not reachable

// The function finds the shortest path because BFS (Breadth-First Search) explores nodes level by level — meaning:
// First, it visits all nodes 1 edge away from the start,
// Then all nodes 2 edges away,
// Then 3 edges away, and so on.
// the first time BFS reaches the end node, it must be via the fewest possible edges — that’s the shortest path in an unweighted graph.

}
int main() {
    /* TODO:
        Write a program that reads a list of edges representing an *undirected* graph
        from its standard input (given as a comma-separated list between square
        brackets, e.g. `[(A, B),(B, C),(C, D)]`), followed by two characters representing
        the start and end nodes.

        The program must then find the path with the fewest edges between the start and
        end nodes, and print the number of edges of that path, or `-1` if no such path exists.
    */
   std::vector<std::pair<char,char>> edges;
   char start, end;

   if(!(std::cin >> edges >> start >> end)){
    std::cerr << "Failed reading input" << std::endl;
    return 1;
   }

   std::unordered_map<char, std::vector<char>> graph;
   for(const auto& edge : edges){
    graph[edge.first].push_back(edge.second);
    graph[edge.second].push_back(edge.first);
   }

   int shortest_dist = bfs_shortest_path(start, end, graph);
   std::cout << shortest_dist << std::endl;
    return 0;
}

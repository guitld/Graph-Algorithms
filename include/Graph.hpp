#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <list>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using std::fstream;
using std::list;
using std::unordered_map;
using std::stack;
using std::vector;

// The graph is represented as a hash map (key: value)
// "key" stands for a vertex
// "value" stands for a pair (vertex, weight)

class Graph {
public:
     unordered_map <int, list<pair<int, int>>> adj_lists;
     int size() {return adj_lists.size();}
     int edgeCount(int u) {return adj_lists[u].size();}
     list <pair<int, int>> vert_list(int u){return adj_lists[u];}
     void addEdge(int u, int v, int weight);
     void add_directed_edge(int u, int v, int weight);
     void fromPajek(string filename);
     void printMap();
     void hierholzerPath();
     int BFS(int u, int v);
     int DFS(int u);
     void DFS_Util_Connected_Components(int u, vector <int>&, vector <int>&);
     void connected_components();
     bool is_cyclic_util(vector<bool>, int u);
     bool is_cyclic();
     vector <int> dijkstra(int node);
     int minimum_tree_cost();
};

#endif
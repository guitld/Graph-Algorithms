#include "Graph.hpp"

// Adds undirected edge to graph
void Graph::addEdge(int u, int v, int weight){
     adj_lists[u].push_back(pair<int, int> (v, weight));
     adj_lists[v].push_back(pair<int, int> (u, weight));
}

// Adds directed edge to graph
void Graph::add_directed_edge(int u, int v, int weight){    
     adj_lists[u].push_back(pair<int, int> (v, weight));
     adj_lists[v].push_back(pair<int, int> (u, weight));
     adj_lists[v].pop_back();
}

// Prints the graph representation in adjacency lists
void Graph::printMap(){     
     for (auto elem : adj_lists){
          cout << elem.first << ": ";
          for (auto const &i : elem.second)
               cout << i.first << "(" << i.second << ")" << ", ";
          cout << endl;
     }
}

// Reads a graph from a .pajek file
void Graph::fromPajek(string filename){

     ifstream pajekFile(filename);

     string line;
     string directed;
     string token1;
     string token2;
     string token3;
     getline(pajekFile, line);
     getline(pajekFile, directed);

     // 'Arcs' represents a directed graph
     if (directed[1] == 'A'){
          while (getline(pajekFile, line)){
               if(!isdigit(line[0])) continue;
               token1 = line.substr(0, line.find(' '));
               token2 = line.substr(token1.size(), line.find(' ', token1.size() + 1));
               token2.erase(token2.begin());
               token3 = line.substr(token1.size() + token2.size(), line.find('\n'));
               this->add_directed_edge(stoi(token1), stoi(token2), stoi(token3));
          }
          pajekFile.close();
     }
     // 'Edges' representes an undirected graph 
     else {
          while (getline(pajekFile, line)){
               if(!isdigit(line[0])) continue;  
               token1 = line.substr(0, line.find(' '));
               token2 = line.substr(token1.size(), line.find(' ', token1.size() + 1));
               token2.erase(token2.begin());
               token3 = line.substr(token1.size() + token2.size(), line.find('\n'));
               this->addEdge(stoi(token1), stoi(token2), stoi(token3));
          }
          pajekFile.close();
     }


}

// Prints the Eulerian path. It considers that the graph is Eulerian
void Graph::hierholzerPath(){

     // Hash map to count the number of edges connected to a vertex
     unordered_map <int, int> edge_count;

     for (auto elem : this->adj_lists)
          edge_count[elem.first] = edgeCount(elem.first);

     // Creating a stack and a vector for the path for the algorithm and path
     stack <int> stack;
     vector <int> circuit;

     stack.push(this->adj_lists.begin()->first);
     int curr_v = this->adj_lists.begin()->first;
     
     while (!stack.empty()){
          // Check if there are edges connected to vertex
          if (edge_count[curr_v]){
               // Pushing vertex to the stack
               stack.push(curr_v);
               // Getting next vertex from its adjacency list
               int next_v = this->adj_lists[curr_v].back().first;
               // Removing the edge
               if (curr_v != next_v){
                    for (auto &elem : this->adj_lists[next_v])
                         if (elem.first == curr_v)
                              this->adj_lists[next_v].remove(elem);
               }
               this->adj_lists[curr_v].pop_back();
               edge_count[curr_v]--;
               edge_count[next_v]--;
               curr_v = next_v;
          }

          else{
               // Popping the stack
               circuit.push_back(curr_v);
               curr_v = stack.top();
               stack.pop();
          }
     }

     // Printing the path
     for (int i=circuit.size()-1; i>=0; i--){
          cout << circuit[i];
          if (i)
               cout<<" -> ";
     }
     cout << endl;
}

// BFS Algorithm
int Graph::BFS(int u, int v){
     if (adj_lists.find(u) == adj_lists.end() || adj_lists.find(v) == adj_lists.end()){
          cout << "Vertex not found" << endl;
          return 0;
     }

     // Defining structures for the algorithm
     vector <int> visited;
     queue <int> queue;
     queue.push(u);
     unordered_map <int, int> parentNode;
     
     while (!queue.empty()){
          // Popping first item of the queue
          int curr_v = queue.front();
          queue.pop();
          // Looping through its neighbors
          for (auto const &neighbor : adj_lists[curr_v]){
               // If the neighbor vertex is not marked as visited, the vertex is added to the queue and marked as visited
               // The father vertex is setted in the parent hash map
               if (find(visited.begin(), visited.end(), neighbor.first) == visited.end()){
                    parentNode[neighbor.first] = curr_v;
                    visited.push_back(neighbor.first);
                    queue.push(neighbor.first);
               }
               // If the vertex was found, loops through the parent hash map to print the BFS path
               if (neighbor.first == v){
                    cout << v << "<-";
                    parentNode[get<0>(neighbor)] = curr_v;
                    int count = 0;
                    while (v != u){
                         v = parentNode[v];
                         cout << v;
                         if (v != u)
                              cout << "<-";
                         count++;
                    }
                    cout << endl;
                    return count;
               }
          }
     }
     cout << "No path found" << endl;
     return 0;
}

// DFS Algorithm
int Graph::DFS(int u){
     if (adj_lists.find(u) == adj_lists.end()){
          cout << "Vertex not found" << endl;
          return 0;
     }

     // Defining structures for the algorithm
     vector <int> visited;
     stack <int> stack;
     stack.push(u);
     visited.push_back(u);

     while (!stack.empty()){
          // Popping the top of the stack
          int curr_v = stack.top();
          // Printing the path
          cout << curr_v << "->";
          stack.pop();
          // Looping through its neighbors
          for (auto const &neighbor : adj_lists[curr_v]){
               // If the neighbor vertex is not marked as visited, the vertex is pushed to the stack and marked as visited
               if (find(visited.begin(), visited.end(), neighbor.first) == visited.end()){
                    visited.push_back(neighbor.first);
                    stack.push(neighbor.first);
               }
          }    
     }
     cout << endl;
     return 0;
}

// Auxiliar DFS to the connected components function
void Graph::DFS_Util_Connected_Components(int u, vector <int> &visitedNodes, vector <int> &componentsSize){
     if (adj_lists.find(u) == adj_lists.end()){
          cout << "Vértice não se encontra no grafo" << endl;
     }

     vector <int> visited;
     stack <int> stack;
     stack.push(u);
     visited.push_back(u);

     while (!stack.empty()){
          int curr_v = stack.top();
          stack.pop();

          for (auto const &neighbor : adj_lists[curr_v]){
               if (find(visited.begin(), visited.end(), neighbor.first) == visited.end()){
                    visited.push_back(neighbor.first);
                    stack.push(neighbor.first);
               }
          }    
     }
     componentsSize.push_back(visited.size());
     visitedNodes.insert(visitedNodes.end(), visited.begin(), visited.end());
}

// Counts the connected components of the graph
void Graph::connected_components(){

     // Defining structures for the algorithm
     vector <int> visitedNodes;
     vector <int> componentsSize;
     int numberOfComponents = 0;

     // Looping through the graph. If the current vertex is not marked as visited, then it belongs to a new component
     for (auto node : adj_lists){
          if (find(visitedNodes.begin(), visitedNodes.end(), node.first) == visitedNodes.end()){
               // Calls a DFS to mark new nodes
               DFS_Util_Connected_Components(node.first, visitedNodes, componentsSize);
               numberOfComponents++;
          }
     }

     // Sorting the components in descending order
     sort(componentsSize.begin(), componentsSize.end(), greater<int>());
     cout << numberOfComponents << endl;
     for (auto elem : componentsSize){
          cout << elem << endl;
     }
}

// Recursive function for detecting cycles
bool Graph::is_cyclic_util(vector<bool> visited, int node){

     // If the node is marked as visited, cycle detected
     if (visited[node - 1])
          return true;

     // Marking current node
     visited[node - 1] = true;

     // Looping through neighbors of current vertex
     for (auto &neighbor : this->adj_lists[node]){
          if (is_cyclic_util(visited, neighbor.first))
               return true;
     }

     return false;

}

// Returns whether the graph is cyclic or not
bool Graph::is_cyclic(){

     // Bool vector to mark nodes as visited
     vector<bool> visited (this->size(), false);

     // Looping through the nodes and use the recursive function to find a cycle or not
     for (auto &node : this->adj_lists){

          visited[node.first - 1] = true;

          for (auto &neighbor : node.second){
               if (is_cyclic_util(visited, neighbor.first))
                    return true;
          }
          visited[node.first - 1] = false;
     }
     return false;
}

// Dijkstra Algorithm
vector<int> Graph::dijkstra(int u){

     // Defining structures for the algorithm
     unordered_map<int, bool> visited;
     priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
     vector<int> dists (this->size(), 0);

     pq.push(pair<int, int> (0, u));
     
     while (!pq.empty()){
          // Popping the top of the priority queue
          pair<int,int> curr_v = pq.top();
          pq.pop();
          // Check whether the node was visited or not
          if (!visited[curr_v.second]){
               // Modifying its distance from 'u' vertex
               dists[curr_v.second - 1] = curr_v.first;
               visited[curr_v.second] = true;
               // Looping through its neighbors
               for (auto const &neighbor : this->adj_lists[curr_v.second])
                    if (!visited[neighbor.first])
                         pq.push(pair<int, int> (curr_v.first + neighbor.second, neighbor.first));
          }
     }
     
     return dists;
}

// Prim's Algorithm to return the total cost of a minimum spanning tree
int Graph::minimum_tree_cost(){

     // Defining structures for the algorithm
     unordered_map<int, bool> visited;
     priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
     vector<int> dists (this->size(), 99999999);
     int cost = 0;

     dists[this->adj_lists.begin()->first - 1] = 0;

     pq.push(pair<int, int> (0, this->adj_lists.begin()->first));
     
     while (!pq.empty()){
          // Popping the top of the priority queue
          pair<int,int> curr_v = pq.top();
          pq.pop();
          // Check whether the node was visited or not
          if (!visited[curr_v.second]){
               // Increasing the cost
               cost += curr_v.first;
               visited[curr_v.second] = true;
               // Looping through its neighbors
               for (auto const &neighbor : this->adj_lists[curr_v.second]){
                    int v = neighbor.first;
                    int weight = neighbor.second;
                    if (!visited[neighbor.first] && dists[v - 1] > weight){
                         dists[v - 1] = weight;
                         pq.push(pair<int, int> (dists[v - 1], v));
                    }
               }
          }
     }

     return cost;
}
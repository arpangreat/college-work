#include <climits>
#include <iostream>

using namespace std;

// Function to print the solution matrix
void printSolution(int dist[][10], int V) {
  cout << "Shortest distances between every pair of vertices:" << endl;
  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
      if (dist[i][j] == INT_MAX)
        cout << "INF ";
      else
        cout << dist[i][j] << " ";
    }
    cout << endl;
  }
}

// Function to implement Floyd-Warshall algorithm
void floydWarshall(int graph[][10], int V) {
  int dist[10][10];

  // Initialize the solution matrix same as the input graph matrix
  for (int i = 0; i < V; ++i)
    for (int j = 0; j < V; ++j)
      dist[i][j] = graph[i][j];

  // Add all vertices one by one to the set of intermediate vertices.
  for (int k = 0; k < V; ++k) {
    for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
        if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
            dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }

  printSolution(dist, V);
}

int main() {
  int V = 4; // Number of vertices in the graph

  // Initialize the graph with INF (INT_MAX) for no direct edge and 0 for
  // self-loops
  int graph[10][10] = {{0, 3, INT_MAX, 7},
                       {8, 0, 2, INT_MAX},
                       {5, INT_MAX, 0, 1},
                       {2, INT_MAX, INT_MAX, 0}};

  floydWarshall(graph, V);

  return 0;
}

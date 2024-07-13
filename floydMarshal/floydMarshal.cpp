#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#define INF numeric_limits<int>::max()

void floydWarshall(vector<vector<int>> &graph, int V) {
  vector<vector<int>> dist(graph);

  for (int k = 0; k < V; ++k) {
    for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
        if (dist[i][k] != INF && dist[k][j] != INF &&
            dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  cout << "Shortest distances between every pair of vertices:\n";
  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
      if (dist[i][j] == INF) {
        cout << "INF\t";
      } else {
        cout << dist[i][j] << "\t";
      }
    }
    cout << "\n";
  }
}

int main() {
  int V;
  cout << "Enter the number of vertices in the graph: ";
  cin >> V;
  vector<vector<int>> graph(V, vector<int>(V, INF));

  int E;
  cout << "Enter the number of edges in the graph: ";
  cin >> E;

  cout << "Enter the edges and weights (source destination weight):\n";
  for (int i = 0; i < E; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u][v] = w;
  }

  for (int i = 0; i < V; ++i) {
    graph[i][i] = 0;
  }

  floydWarshall(graph, V);

  return 0;
}

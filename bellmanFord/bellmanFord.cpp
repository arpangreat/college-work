#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Edge {
  int source, destination, weight;
};

void bellmanFord(vector<Edge> &edges, int V, int source) {
  vector<int> distance(V, numeric_limits<int>::max());
  distance[source] = 0;

  for (int i = 1; i <= V - 1; ++i) {
    for (const auto &edge : edges) {
      int u = edge.source;
      int v = edge.destination;
      int weight = edge.weight;
      if (distance[u] != numeric_limits<int>::max() &&
          distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight;
      }
    }
  }

  for (const auto &edge : edges) {
    int u = edge.source;
    int v = edge.destination;
    int weight = edge.weight;
    if (distance[u] != numeric_limits<int>::max() &&
        distance[u] + weight < distance[v]) {
      cout << "Graph contains negative weight cycle\n";
      return;
    }
  }

  cout << "Vertex Distance from Source:\n";
  for (int i = 0; i < V; ++i) {
    cout << i << "\t\t" << distance[i] << "\n";
  }
}

int main() {
  int V, E;
  cout << "Enter the number of vertices: ";
  cin >> V;
  cout << "Enter the number of edges: ";
  cin >> E;

  vector<Edge> edges;
  cout << "Enter the edges (source destination weight):\n";
  for (int i = 0; i < E; ++i) {
    Edge edge;
    cin >> edge.source >> edge.destination >> edge.weight;
    edges.push_back(edge);
  }

  int source;
  cout << "Enter the source vertex: ";
  cin >> source;

  bellmanFord(edges, V, source);

  return 0;
}

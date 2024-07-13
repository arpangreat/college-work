#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

using iPair = pair<int, int>;
void dijkstra(int src, vector<vector<iPair>> &adj, vector<int> &dist) {
  priority_queue<iPair, vector<iPair>, greater<>> pq;
  pq.emplace(0, src);
  dist[src] = 0;

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    for (auto &neighbor : adj[u]) {
      int v = neighbor.first;
      int weight = neighbor.second;

      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.emplace(dist[v], v);
      }
    }
  }
}

int main() {
  int V, E;
  cout << "Enter the number of vertices: ";
  cin >> V;
  cout << "Enter the number of edges: ";
  cin >> E;

  vector<vector<iPair>> adj(V);
  cout << "Enter the edges (source, destination, weight):\n";
  for (int i = 0; i < E; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  int src;
  cout << "Enter the source vertex: ";
  cin >> src;

  vector<int> dist(V, numeric_limits<int>::max());
  dijkstra(src, adj, dist);

  cout << "Vertex Distance from Source\n";
  for (int i = 0; i < V; ++i) {
    cout << i << "\t" << dist[i] << "\n";
  }

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

int prims(vector<vector<pair<int, int>>> &adj) {
  int n = adj.size();
  vector<int> vis(n, 0);
  int mst = 0;
  vector<pair<int, int>> edges;
  priority_queue<
      pair<int, pair<int, int>>,
      vector<pair<int, pair<int, int>>>,
      greater<pair<int, pair<int, int>>>>
      pq;

  pq.push({0, {0, -1}});
  while (!pq.empty()) {
    int node = pq.top().second.first;
    int parent = pq.top().second.second;
    int weight = pq.top().first;
    pq.pop();
    if (vis[node])
      continue;
    vis[node] = 1;
    mst += weight;
    if (parent != -1)
      edges.push_back({parent, node});
    for (auto i : adj[node]) {
      if (!vis[i.second]) {
        pq.push({i.first, {i.second, node}});
      }
    }
  }

  return mst;
}

int main() {
  int n, e;
  cout << "Enter the number of nodes: ";
  cin >> n;
  cout << "Enter the number of Edges: ";
  cin >> e;
  cout << "Enter the Edges with weight :-" << endl;

  vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
  for (int i = 0; i < e; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].emplace_back(w, v);
    adj[v].emplace_back(w, u);
  }

  int res = prims(adj);
  cout << "The MST weight is: " << res;

  return 0;
}
#include <bits/stdc++.h>
using namespace std;

bool isCycleDfs(int node, vector<int> &vis, vector<int> &pathVis, vector<vector<int>> &adj) {
  vis[node] = 1;
  pathVis[node] = 1;
  for (auto i : adj[node]) {
    if (!vis[i]) {
      if (isCycleDfs(i, vis, pathVis, adj))
        return true;
    } else if (pathVis[i]) {
      return true;
    }
  }
  pathVis[node] = 0;
  return false;
}

int main() {

  int n, e;
  cout << "Enter the number of nodes: ";
  cin >> n;
  cout << "Enter the number of Edges: ";
  cin >> e;

  vector<vector<int>> adj(n + 1, vector<int>());
  for (int i = 0; i < e; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  vector<int> vis(n, 0);
  vector<int> pathVis(n, 0);

  bool cycle = false;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      if (isCycleDfs(i, vis, pathVis, adj)) {
        cycle = true;
        break;
      }
    }
  }
  cout << (cycle ? "Cyclic Graph" : "Acyclic Graph");
  return 0;
}
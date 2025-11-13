#include <bits/stdc++.h>
using namespace std;

bool isCycleDfs(int node, int parent, vector<int> &vis, vector<vector<int>> &adj) {
  vis[node] = 1;
  for (auto i : adj[node]) {
    if (!vis[i]) {
      if (isCycleDfs(i, node, vis, adj))
        return true;
    } else if (i != parent) {
      return true;
    }
  }
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
  vector<int> pathVis(n,)

  bool cycle = false;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      if (isCycleDfs(i, -1, vis, adj)) {
        cycle = true;
        break;
      }
    }
  }
  cout << (cycle ? "Cyclic Graph" : "Acyclic Graph");
  return 0;
}
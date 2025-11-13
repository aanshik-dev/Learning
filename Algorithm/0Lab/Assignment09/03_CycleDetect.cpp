#include <bits/stdc++.h>
using namespace std;

bool isCycle(int node, int parent, vector<int> &vis, vector<vector<int>> &adj) {
  vis[node] = 1;
  bool res = false;
  for (auto i : adj[node]) {
    if (!vis[i]) {
      res = isCycle(i, node, vis, adj);
    } else if (i != parent) {
      res = true;
    }
    if (res)
      break;
  }
  return res;
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
    adj[v].push_back(u);
  }

  vector<int> vis(n + 1, 0);

  bool cycle = false;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      if (isCycle(i, -1, vis, adj)) {
        cycle = true;
        break;
      }
    }
  }
  cout << (cycle ? "Cyclic Graph" : "Acyclic Graph");
  return 0;
}
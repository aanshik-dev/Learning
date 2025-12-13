// Implementation of dfs algorithm for the Undirected graph
#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> &vis, vector<vector<int>> &adj) {
  vis[node] = 1;
  for (auto i : adj[node]) {
    if (!vis[i]) {
      cout << i << " ";
      dfs(i, vis, adj);
    }
  }
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
  cout << "1 ";
  dfs(1, vis, adj);
  return 0;
}
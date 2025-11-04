// Implementation of dfs algorithm for the Undirected graph
#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> &vis, vector<vector<int>> &adj) {
  vis[node] = 1;
  for (int i = 0; i < adj[node].size(); i++) {
    if (!vis[adj[node][i]]) {
      cout << adj[node][i] << " ";
      dfs(adj[node][i], vis, adj);
    }
  }
}

int main() {
  int n, m;
  cout << "Enter the number of nodes and edges: ";
  cin >> n >> m;
  vector<vector<int>> adj(n + 1, vector<int>());
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> vis(n + 1, 0);
  dfs(1, vis, adj);
  return 0;
}
#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> &vis, vector<vector<int>> &adj, vector<int> &collect) {
  vis[node] = 1;
  for (auto i : adj[node]) {
    if (!vis[i]) {
      dfs(i, vis, adj, collect);
    }
  }
  collect.push_back(node);
}

int main() {
  int n, e;
  cout << "Enter the number of nodes: ";
  cin >> n;
  cout << "Enter the number of Edges: ";
  cin >> e;
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < e; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  vector<int> vis(n, 0);
  vector<int> collect;

  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      dfs(i, vis, adj, collect);
    }
  }

  reverse(collect.begin(), collect.end());
  for (auto i : collect) {
    cout << i << " ";
  }

  return 0;
}
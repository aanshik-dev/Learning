#include <bits/stdc++.h>
using namespace std;

bool isCycleBfs(int node, vector<vector<int>> &adj, vector<int> &vis) {
  queue<pair<int, int>> q;
  q.emplace(node, -1);
  vis[node] = 1;
  while (!q.empty()) {
    pair<int, int> curr = q.front();
    q.pop();
    int nd = curr.first;
    int parent = curr.second;
    for (auto i : adj[nd]) {
      if (!vis[i]) {
        q.emplace(i, nd);
        vis[i] = 1;
      } else if (i != parent) {
        return true;
      }
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

  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < e; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> vis(n, 0);

  bool cycle = false;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      if (isCycleBfs(i, adj, vis)) {
        cycle = true;
        break;
      }
    }
  }
  cout << (cycle ? "Cyclic Graph" : "Acyclic Graph");

  return 0;
}
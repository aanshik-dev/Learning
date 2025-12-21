#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> &vis, vector<vector<int>> &adj) {
  vis[node] = 1;
  for (auto i : adj[node]) {
    if (!vis[i]) {
      dfs(i, vis, adj);
    }
  }
}

vector<vector<int>> gRev(vector<vector<int>> adj) {
  int n = adj.size();
  vector<vector<int>> res(n, vector<int>());
  for (int i = 0; i < n; i++) {
    for (auto j : adj[i]) {
      res[j].push_back(i);
    }
  }
  return res;
}

bool strngConnect(vector<vector<int>> adj) {
  int n = adj.size();
  vector<int> vis(n, 0);
  dfs(0, vis, adj);
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      return false;
    }
  }
  fill(vis.begin(), vis.end(), 0);
  vector<vector<int>> rev = gRev(adj);
  dfs(0, vis, rev);
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      return false;
    }
  }
  return true;
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

  bool isSC = strngConnect(adj);
  cout << (isSC ? "Strongly Connected" : "Not Strongly Connected");
  return 0;
}
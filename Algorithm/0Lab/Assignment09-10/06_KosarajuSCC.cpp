#include <bits/stdc++.h>
using namespace std;

void dfsFin(int node, vector<int> &vis, vector<vector<int>> &adj, stack<int> &finish) {
  vis[node] = 1;
  for (auto i : adj[node]) {
    if (!vis[i]) {
      dfsFin(i, vis, adj, finish);
    }
  }
  finish.push(node);
}

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

int kosaraju(vector<vector<int>> adj) {
  int n = adj.size();
  vector<int> vis(n, 0);
  stack<int> finish;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      dfsFin(i, vis, adj, finish);
    }
  }
  vector<vector<int>> rev = gRev(adj);
  fill(vis.begin(), vis.end(), 0);
  int SCC = 0;
  while (!finish.empty()) {
    int up = finish.top();
    finish.pop();
    if (!vis[up]) {
      SCC++;
      dfs(up, vis, rev);
    }
  }

  return SCC;
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

  int res = kosaraju(adj);
  cout << "The number of Strongly Connected Components are: " << res;

  return 0;
}
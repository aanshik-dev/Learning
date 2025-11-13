#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> &vis, vector<vector<int>> &adj) {
  vis[node] = 1;
  for (auto it : adj[node]) {
    if (!vis[it]) {
      dfs(it, vis, adj);
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

  int res = 0;
  while (1) {
    int flag = 0;
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        res++;
        dfs(i, vis, adj);
        flag = 1;
      }
    }
    if (flag == 0)
      break;
  }

  cout << "Number of connected components: " << res << endl;

  return 0;
}
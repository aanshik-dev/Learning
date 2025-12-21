#include <bits/stdc++.h>
using namespace std;

bool bfs(int node, vector<vector<int>> &adj, vector<int> &vis) {
  int color = 1;
  queue<int> q;
  q.push(node);
  vis[node] = color;
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    color = -vis[curr];
    for (auto i : adj[curr]) {
      if (!vis[i]) {
        q.push(i);
        vis[i] = color;
      } else if (vis[i] == vis[curr]) {
        return false;
      }
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

  vector<vector<int>> adj(n + 1, vector<int>());
  for (int i = 0; i < e; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> vis(n + 1, 0);
  bool res;
  while (1) {
    int flag = 0;
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        flag = 1;
        res = bfs(i, adj, vis);
        if (!res) {
          flag = 0;
          break;
        }
      }
    }
    if (flag == 0)
      break;
  }
  cout << (res ? "Bipartite" : "Not Bipartite");
  return 0;
}
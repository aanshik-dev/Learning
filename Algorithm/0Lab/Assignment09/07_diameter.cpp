#include <bits/stdc++.h>
using namespace std;

vector<int> shortDist(vector<vector<int>> &adj, int node) {
  int n = adj.size();
  vector<int> vis(n, 0);
  vector<int> dis(n, INT_MAX);
  
  queue<pair<int, int>> q;
  q.push({node, 0});
  dis[node] = 0;
  vis[node] = 1;
  while (!q.empty()) {
    pair<int, int> curr = q.front();
    q.pop();
    for (auto i : adj[curr.first]) {
      if (!vis[i]) {
        q.push({i, curr.second + 1});
        dis[i] = min(dis[i], curr.second + 1);
        vis[i] = 1;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      dis[i] = -1;
    }
  }
  return dis;
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
  vector<int> res;
  int dia = 0;
  for (int i = 0; i < n; i++) {
    res = shortDist(adj, i);
    for (auto i : res)
      dia = max(dia, i);
  }
  cout << "The diameter of the graph is: " << dia;
  return 0;
}
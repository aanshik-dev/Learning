#include <bits/stdc++.h>
using namespace std;

class Solution {

  bool bfs(int node, vector<vector<int>> &adj, vector<int> &vis) {
    queue<int> q;
    q.push(node);
    vis[node] = 1;
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      for (auto i : adj[curr]) {
        if (!vis[i]) {
          q.push(i);
          vis[i] = -vis[curr];
        } else if (vis[i] == vis[curr]) {
          return false;
        }
      }
    }
    return true;
  }

  public:
  bool isBipartite(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> vis(n, 0);
    bool isBip = true;
    for (int i = 0; i < n; i++) {
      if (!vis[i]) {
        isBip = bfs(i, graph, vis);
        if (!isBip)
          break;
      }
    }
    return isBip;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
  bool res = sol.isBipartite(graph);
  cout << res << endl;

  return 0;
}
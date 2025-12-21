#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  void dfs(int node, vector<int> &vis, vector<vector<int>> &adj) {
    vis[node] = 1;
    for (auto i : adj[node]) {
      if (!vis[i]) {
        dfs(i, vis, adj);
      }
    }
  }

  public:
  int findCircleNum(vector<vector<int>> &isConnected) {
    int n = isConnected.size();
    vector<vector<int>> adj(n, vector<int>());
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < isConnected[i].size(); j++) {
        if (isConnected[i][j] == 1 && i != j) {
          adj[i].push_back(j);
          adj[j].push_back(i);
        }
      }
    }

    vector<int> vis(n, 0);
    int count = 0;
    for (int i = 0; i < n; i++) {
      if (!vis[i]) {
        count++;
        dfs(i, vis, adj);
      }
    }
    return count;
  }
};

int main() {
  Solution sol;

  vector<vector<int>> isConnected = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  int res = sol.findCircleNum(isConnected);
  cout << res << endl;

  return 0;
}

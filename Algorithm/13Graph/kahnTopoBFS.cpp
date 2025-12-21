#include <bits/stdc++.h>
using namespace std;

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

  vector<int> indeg(n, 0);
  for (int i = 0; i < n; i++) {
    for (auto j : adj[i]) {
      indeg[j]++;
    }
  }

  queue<int> zeroIndeg;
  for (int i = 0; i < n; i++) {
    if (indeg[i] == 0) {
      zeroIndeg.push(i);
    }
  }

  vector<int> topoOrder;
  while (!zeroIndeg.empty()) {
    int node = zeroIndeg.front();
    zeroIndeg.pop();
    topoOrder.push_back(node);
    for (auto i : adj[node]) {
      indeg[i]--;
      if (indeg[i] == 0) {
        zeroIndeg.push(i);
      }
    }
  }

  for (auto i : topoOrder) {
    cout << i << " ";
  }

  return 0;
}
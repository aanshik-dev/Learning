#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, e;
  cout << "Enter the number of nodes: ";
  cin >> n;
  cout << "Enter the number of Edges: ";
  cin >> e;

  cout << "Enter the Edges with weight :-" << endl;

  vector<vector<pair<int, int>>> adj(n + 1, vector<pair<int, int>>());
  for (int i = 0; i < e; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].emplace_back(w, v);
    adj[v].emplace_back(w, u);
  }
  return 0;
}
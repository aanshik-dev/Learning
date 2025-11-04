#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>> &adj, vector<int> &vis) {

  stack<int> st;
  st.push(node);
  vis[node] = 1;
  while (!st.empty()) {
    int curr = st.top();
    st.pop();
    cout << curr << " ";
    for (int i = 0; i < adj[curr].size(); i++) {
      if (!vis[adj[curr][i]]) {
        st.push(adj[curr][i]);
        vis[adj[curr][i]] = 1;
      }
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
  dfs(1, adj, vis);
  return 0;
}
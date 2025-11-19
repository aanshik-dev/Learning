#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> bfsTree(int start, vector<vector<pair<int, int>>> &adj, vector<int> &vis) {
  queue<int> q;
  q.push(start);
  vis[start] = 1;

  vector<pair<int, int>> treeEdges;

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    for (auto &p : adj[curr]) {
      int node = p.first;
      if (!vis[node]) {
        vis[node] = 1;
        q.push(node);
        treeEdges.push_back({curr, node});
      }
    }
  }
  return treeEdges;
}

pair<int, vector<pair<int, int>>> prims(int n, vector<vector<pair<int, int>>> &adj) {
  vector<int> vis(n + 1, 0);
  priority_queue<
      pair<int, pair<int, int>>,
      vector<pair<int, pair<int, int>>>,
      greater<pair<int, pair<int, int>>>>
      pq;

  pq.push({0, {1, -1}});

  int mstWeight = 0;
  vector<pair<int, int>> mstEdges;

  while (!pq.empty()) {
    auto top = pq.top();
    pq.pop();
    int w = top.first;
    int node = top.second.first;
    int parent = top.second.second;

    if (vis[node])
      continue;
    vis[node] = 1;
    mstWeight += w;

    if (parent != -1)
      mstEdges.push_back({parent, node});

    for (auto &i : adj[node]) {
      if (!vis[i.first]) {
        pq.push({i.second, {i.first, node}});
      }
    }
  }

  return {mstWeight, mstEdges};
}

int main() {
  int n, e;
  cout << "Enter number of nodes: ";
  cin >> n;
  cout << "Enter number of edges: ";
  cin >> e;

  vector<vector<pair<int, int>>> adj(n + 1);

  cout << "Enter edges (u v w):\n";
  for (int i = 0; i < e; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  vector<int> vis(n + 1, 0);
  auto bfs_edges = bfsTree(1, adj, vis);

  auto mstRes = prims(n, adj);
  int mstWeight = mstRes.first;
  auto mst_edges = mstRes.second;

  for (auto &p : bfs_edges)
    if (p.first > p.second)
      swap(p.first, p.second);
  sort(bfs_edges.begin(), bfs_edges.end());

  for (auto &p : mst_edges)
    if (p.first > p.second)
      swap(p.first, p.second);
  sort(mst_edges.begin(), mst_edges.end());

  if (bfs_edges == mst_edges) {
    cout << "\nT is an MST\n";
    cout << "NO replacements\n";
    cout << "Final MST Weight = " << mstWeight << "\n";
    return 0;
  }

  vector<pair<int, int>> toRemove, toInsert;

  int i = 0, j = 0;
  while (i < bfs_edges.size() || j < mst_edges.size()) {
    if (j == mst_edges.size() || (i < bfs_edges.size() && bfs_edges[i] < mst_edges[j])) {
      toRemove.push_back(bfs_edges[i]);
      i++;
    } else if (i == bfs_edges.size() || mst_edges[j] < bfs_edges[i]) {
      toInsert.push_back(mst_edges[j]);
      j++;
    } else {
      i++;
      j++;
    }
  }

  cout << "\nT is NOT MST";

  cout << "\nEdges to INSERT (MST edges): ";
  for (auto &p : toInsert)
    cout << "(" << p.first << "," << p.second << ") ";

  cout << "\nEdges to REMOVE: ";
  for (auto &p : toRemove)
    cout << "(" << p.first << "," << p.second << ") ";

  cout << "\nFINAL MST Edges: ";
  for (auto &p : mst_edges)
    cout << "(" << p.first << "," << p.second << ") ";

  cout << "\nFinal MST Weight = " << mstWeight << "\n";

  return 0;
}

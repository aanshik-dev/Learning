#include <bits/stdc++.h>
using namespace std;

class DSU {
  vector<int> rank, parent, size;

  public:
  DSU(int n) {
    rank.resize(n, 0);
    parent.resize(n, 0);
    size.resize(n, 1);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  public:
  int fParent(int node) {
    if (parent[node] == node) {
      return node;
    }
    return parent[node] = fParent(parent[node]);
  }

  public:
  void rankUnion(int u, int v) {
    int upu = fParent(u);
    int upv = fParent(v);
    if (upu == upv)
      return;
    if (rank[upu] > rank[upv])
      parent[upv] = upu;
    else if (rank[upu] < rank[upv])
      parent[upu] = upv;
    else {
      parent[upu] = upv;
      rank[upv]++;
    }
  }

  public:
  void sizeUnion(int u, int v) {
    int upu = fParent(u);
    int upv = fParent(v);
    if (upu == upv)
      return;
    if (size[upu] > size[upv]) {
      parent[upv] = upu;
      size[upu] += size[upv];
    } else {
      parent[upu] = upv;
      size[upv] += size[upu];
    }
  }
};

int main() {

  vector<pair<int, pair<int, int>>> edges = {{2, {0, 1}}, {4, {1, 2}}, {5, {2, 3}}, {2, {3, 4}}, {6, {4, 0}}, {3, {0, 3}}, {1, {1, 3}}};
  sort(edges.begin(), edges.end());
  int sum = 0;
  DSU dsu(5);
  for (auto p : edges) {
    if (dsu.fParent(p.second.first) != dsu.fParent(p.second.second)) {
      sum += p.first;
      dsu.rankUnion(p.second.first, p.second.second);
    }
  }

  cout << sum;
  return 0;
}
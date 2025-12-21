#include <bits/stdc++.h>
using namespace std;

class DSU {
  vector<int> rank, parent, size;

  public:
  DSU(int n) {
    rank.resize(n, 1);
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
  vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {3, 4}, {5, 6}, {4, 5}, {2, 6}};
  DSU ds(7);
  ds.rankUnion(0, 1);
  ds.rankUnion(1, 2);
  ds.rankUnion(3, 4);
  ds.rankUnion(5, 6);
  ds.rankUnion(4, 5);
  if (ds.fParent(3) == ds.fParent(2)) {
    cout << "true";
  } else {
    cout << "false";
  }
  ds.rankUnion(2, 6);
  if (ds.fParent(3) == ds.fParent(2)) {
    cout << "true";
  } else {
    cout << "false";
  }
  return 0;
}
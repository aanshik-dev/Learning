#include <bits/stdc++.h>
using namespace std;

int main() {
  int nodes;
  cout << "Enter the number of nodes: ";
  cin >> nodes;

  vector<vector<int>> matrix = vector<vector<int>>(nodes, vector<int>(nodes, 0));

  int edges;
  cout << "Enter the number of edges: ";
  cin >> edges;

  cout << "Enter the edges: ";
  for (int i = 0; i < edges; i++) {
    int u, v;
    cin >> u >> v;
    matrix[u][v] = 1;
  }

  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < i; j++) {
      swap(matrix[i][j], matrix[j][i]);
    }
  }

  vector<vector<int>> adList = vector<vector<int>>(nodes);
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (matrix[i][j] == 1) {
        adList[i].push_back(j);
      }
    }
  }

  for (int i = 0; i < adList.size(); i++) {
    cout << i << " -> ";
    for (int j = 0; j < adList[i].size(); j++) {
      cout << adList[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<vector<int>> matrix = {
      {0, 1, 1, 1},
      {1, 0, 1, 0},
      {1, 1, 0, 1},
      {1, 0, 1, 0}};
  int nodes = matrix.size();
  int edges = 0;
  bool isDir = false;
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < i; j++) {
      if (matrix[i][j] == 1) {
        edges++;
      }
      if (matrix[j][i] == 1) {
        edges++;
      }
      if (matrix[i][j] != matrix[j][i]) {
        isDir = true;
      }
    }
  }
  if (isDir) {
    cout << "Directed graph" << endl;
  } else {
    edges /= 2;
    cout << "Undirected graph" << endl;
  }

  int density = (nodes * (nodes - 1)) / 4;
  if (edges > density) {
    cout << "Dense graph" << endl;
  } else {
    cout << "Sparse graph" << endl;
  }

  return 0;
}
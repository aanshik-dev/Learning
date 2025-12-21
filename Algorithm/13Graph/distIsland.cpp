#include <bits/stdc++.h>
using namespace std;

void cover(vector<vector<int>> &area, int i, int j) {
  area[i][j] = 0;
  // Top
  if (i > 0 && area[i - 1][j] == 1) {
    cover(area, i - 1, j);
  }
  // Bottom
  if (i < area.size() - 1 && area[i + 1][j] == 1) {
    cover(area, i + 1, j);
  }
  // Left
  if (j > 0 && area[i][j - 1] == 1) {
    cover(area, i, j - 1);
  }
  // Right
  if (j < area[0].size() - 1 && area[i][j + 1] == 1) {
    cover(area, i, j + 1);
  }
  // Top Left
  if (i > 0 && j > 0 && area[i - 1][j - 1] == 1) {
    cover(area, i - 1, j - 1);
  }
  // Top Right
  if (i > 0 && j < area[0].size() - 1 && area[i - 1][j + 1] == 1) {
    cover(area, i - 1, j + 1);
  }
  // Bottom Left
  if (i < area.size() - 1 && j > 0 && area[i + 1][j - 1] == 1) {
    cover(area, i + 1, j - 1);
  }
  // Bottom Right
  if (i < area.size() - 1 && j < area[0].size() - 1 && area[i + 1][j + 1] == 1) {
    cover(area, i + 1, j + 1);
  }
}

int main() {
  vector<vector<int>> area = {{0, 1, 1, 0},
                              {0, 1, 1, 0},
                              {0, 0, 1, 0},
                              {0, 0, 0, 0},
                              {1, 1, 0, 1}};

  int island = 0;
  for (int i = 0; i < area.size(); i++) {
    for (int j = 0; j < area[0].size(); j++) {
      if (area[i][j]) {
        island++;
        cover(area, i, j);
      }
    }
  }

  cout << island << endl;

  return 0;
}
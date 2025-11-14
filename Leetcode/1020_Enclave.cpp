#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  void cover(vector<vector<int>> &area, int i, int j) {
    area[i][j] = 0;
    if (i > 0 && area[i - 1][j] == 1) {
      cover(area, i - 1, j);
    }
    if (i < area.size() - 1 && area[i + 1][j] == 1) {
      cover(area, i + 1, j);
    }
    if (j > 0 && area[i][j - 1] == 1) {
      cover(area, i, j - 1);
    }
    if (j < area[0].size() - 1 && area[i][j + 1] == 1) {
      cover(area, i, j + 1);
    }
  }

  public:
  int numEnclaves(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    for (int i = 0; i < n; i++) {
      if (grid[i][0] == 1) {
        cover(grid, i, 0);
      }
      if (grid[i][m - 1] == 1) {
        cover(grid, i, m - 1);
      }
    }
    for (int j = 0; j < m; j++) {
      if (grid[0][j] == 1) {
        cover(grid, 0, j);
      }
      if (grid[n - 1][j] == 1) {
        cover(grid, n - 1, j);
      }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 1) {
          res++;
        }
      }
    }
    return res;
  }
};

int main() {
  vector<vector<int>> area = {{0, 1, 1, 0},
                              {1, 0, 1, 0},
                              {0, 1, 0, 0},
                              {0, 0, 0, 0}};

  Solution sol;
  int res = sol.numEnclaves(area);
  cout << res << endl;
  return 0;
}
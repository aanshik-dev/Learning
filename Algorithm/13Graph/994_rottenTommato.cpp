#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int orangesRotting(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    int fresh = 0;
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 1) {
          fresh++;
        } else if (grid[i][j] == 2) {
          q.push({i, j});
        }
      }
    }
    if (!fresh)
      return 0;
    int minute = 0;
    bool isRot = false;
    while (!q.empty()) {
      int k = q.size();
      isRot = false;
      for (int x = 0; x < k; x++) {
        pair<int, int> ij = q.front();
        int i = ij.first;
        int j = ij.second;
        q.pop();
        if (i > 0 && grid[i - 1][j] == 1) {
          grid[i - 1][j] = 2;
          q.push({i - 1, j});
          fresh--;
          isRot = true;
        }
        if (j > 0 && grid[i][j - 1] == 1) {
          grid[i][j - 1] = 2;
          q.push({i, j - 1});
          fresh--;
          isRot = true;
        }
        if (i < n - 1 && grid[i + 1][j] == 1) {
          grid[i + 1][j] = 2;
          q.push({i + 1, j});
          fresh--;
          isRot = true;
        }
        if (j < m - 1 && grid[i][j + 1] == 1) {
          grid[i][j + 1] = 2;
          q.push({i, j + 1});
          fresh--;
          isRot = true;
        }
      }
      isRot ? minute++ : 0;
    }
    return (fresh > 0 ? -1 : minute);
  }
};

int main() {
  vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  Solution sol;
  int res = sol.orangesRotting(grid);
  cout << res << endl;
  return 0;
}

// 2 2 2
// 2 2 0
// 0 2 2

// 2.1
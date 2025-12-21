#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int minPathSum(vector<vector<int>> &grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<int> dp1(col, 0);
    vector<int> dp2(col, 0);
    dp1[0] = grid[0][0];
    for (int i = 1; i < col; i++) {
      dp1[i] = grid[0][i] + dp1[i - 1];
    }
    for (int i = 1; i < row; i++) {
      dp2[0] = grid[i][0] + dp1[0];
      for (int j = 1; j < col; j++) {
        dp2[j] = grid[i][j] + min(dp1[j], dp2[j - 1]);
      }
      dp1 = dp2;
    }
    return dp1[col - 1];
  }
};

int main() {
  vector<vector<int>> grid = {{1}};
  Solution sol;
  int res = sol.minPathSum(grid);
  cout << res << endl;
  return 0;
}
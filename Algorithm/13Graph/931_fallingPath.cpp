#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int minFallingPathSum(vector<vector<int>> &matrix) {
    int row = matrix.size();
    int col = matrix[0].size();
    for (int i = 1; i < row; i++) {
      for (int j = 0; j < col; j++) {
        int left = (j == 0 ? INT_MAX : matrix[i - 1][j - 1]);
        int top = matrix[i - 1][j];
        int right = (j == col - 1 ? INT_MAX : matrix[i - 1][j + 1]);
        matrix[i][j] += min(left, min(top, right));
      }
    }
    int minSum = INT_MAX;
    for (int i = 0; i < col; i++) {
      minSum = min(minSum, matrix[row - 1][i]);
    }
    return minSum;
  }
};

int main() {
  vector<vector<int>> grid = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
  Solution sol;
  int res = sol.minFallingPathSum(grid);
  cout << res << endl;
  return 0;
}

// 2 1 3
// 6 5 4
// 7 8 9

// 2 1 3
// 7 6 5
// 13 13 14
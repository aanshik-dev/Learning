#include <bits/stdc++.h>
using namespace std;

class Solution {
  // public:
  // int paths(int row, int col, vector<vector<int>> &dp) {
  //   if(row == 0 && col == 0) {
  //     return 1;
  //   }
  //   if(row < 0 || col < 0) {
  //     return 0;
  //   }
  //   if(dp[row][col] != -1) {
  //     return dp[row][col];
  //   }
  //   return dp[row][col] = paths(row - 1, col, dp) + paths(row, col - 1, dp);
  // }

  public:
  int uniquePaths(int m, int n) {
    // vector<vector<int>> dp(m, vector<int>(n, -1));
    // return paths(m-1, n-1, dp);
    vector<vector<int>> dp(m, vector<int>(n, -1));
    for (int i = 0; i < m; i++) {
      dp[i][0] = 1;
    }
    for (int j = 0; j < n; j++) {
      dp[0][j] = 1;
    }

    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }
    return dp[m - 1][n - 1];
  }
};

int main() {

  Solution sol;
  int res = sol.uniquePaths(1, 1);
  cout << res << endl;
  return 0;
}
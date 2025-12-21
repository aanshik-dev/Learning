#include <bits/stdc++.h>
using namespace std;

int path(vector<vector<int>> &mat) {
  int n = mat.size(), m = mat[0].size();
  vector<vector<int>> dp(n, vector<int>(m, -1));
  for (int i = 0; i < m; i++) {
    dp[0][i] = mat[0][i];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j > 0 && mat[i - 1][j - 1] < mat[i][j] && dp[i - 1][j - 1] != -1) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + mat[i][j]);
      }
      if (mat[i - 1][j] < mat[i][j] && dp[i - 1][j] != -1) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j] + mat[i][j]);
      }
      if (j < m - 1 && mat[i - 1][j + 1] < mat[i][j] && dp[i - 1][j + 1] != -1) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j + 1] + mat[i][j]);
      }
    }
  }

  int maxIdx = 0;
  for (int i = 0; i < m; i++) {
    if (dp[n - 1][i] > dp[n - 1][maxIdx]) {
      maxIdx = i;
    }
  }
  int sum = dp[n - 1][maxIdx];
  if (sum == -1) {
    cout << "NO Path Exist !!" << endl;
    return -1;
  }
  vector<int> res;
  for (int i = n - 1; i >= 0; i--) {
    res.push_back(mat[i][maxIdx]);
    if (i > 0) {
      int idx = maxIdx;
      if (maxIdx > 0 && dp[i][maxIdx] > dp[i - 1][maxIdx - 1] && dp[i - 1][maxIdx - 1] >= dp[i - 1][idx]) {
        idx = maxIdx - 1;
      }
      if (maxIdx < m - 1 && dp[i][maxIdx] > dp[i - 1][maxIdx + 1] && dp[i - 1][maxIdx + 1] >= dp[i - 1][idx]) {
        idx = maxIdx + 1;
      }
      maxIdx = idx;
    }
  }
  reverse(res.begin(), res.end());
  for (int i : res) {
    cout << i << " -> ";
  }
  return sum;
}

int main() {
  vector<vector<int>> mat = {
      {1, 100, 2}, {3, 4, 5}, {6, 7, 8}};

  int res = path(mat);
  if (res != -1) {
    cout << endl;
    cout << "SUM = " << res;
  }
  return 0;
}
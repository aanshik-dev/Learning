#include <bits/stdc++.h>
using namespace std;

// =====================================================
// 1) RECURSION + MEMO (Independent)
// =====================================================
int lcsRecHelper(
    string &a, string &b, int i, int j,
    vector<vector<int>> &dp, int &ans) {
  if (i == 0 || j == 0)
    return 0;

  if (dp[i][j] != -1)
    return dp[i][j];

  if (a[i - 1] == b[j - 1]) {
    dp[i][j] = 1 + lcsRecHelper(a, b, i - 1, j - 1, dp, ans);
    ans = max(ans, dp[i][j]);
    return dp[i][j];
  }

  return dp[i][j] = 0;
}

int lcsRec(string &a, string &b) {
  int n = a.size(), m = b.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
  int ans = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      lcsRecHelper(a, b, i, j, dp, ans);
    }
  }

  return ans;
}

// =====================================================
// 2) TABULATION (Independent) → returns {length, endPos}
// =====================================================
pair<int, int> lcsTab(string &a, string &b) {
  int n = a.size(), m = b.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  int maxLen = 0;
  int endPos = -1;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i - 1] == b[j - 1]) {
        dp[i][j] = 1 + dp[i - 1][j - 1];

        if (dp[i][j] > maxLen) {
          maxLen = dp[i][j];
          endPos = i - 1;
        }
      }
    }
  }

  return {maxLen, endPos};
}

// =====================================================
// 3) PRINT SUBSTRING (Independent)
// =====================================================
string printLCS(string &a, int maxLen, int endPos) {
  if (maxLen <= 0 || endPos < 0)
    return "";
  return a.substr(endPos - maxLen + 1, maxLen);
}

// =====================================================
// MAIN
// =====================================================
int main() {
  string a = "abcdfghxyz";
  string b = "abedfghz";

  // Recursion
  cout << "Recursion LCS length: " << lcsRec(a, b) << endl;

  // Tabulation
  auto res = lcsTab(a, b);
  int maxLen = res.first;
  int endPos = res.second;

  cout << "Tabulation LCS length: " << maxLen << endl;

  // Print substring
  cout << "Longest Common Substring: " << printLCS(a, maxLen, endPos) << endl;

  return 0;
}

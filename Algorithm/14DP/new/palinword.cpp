#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------------------------
// Function 1: Tabulation to compute LCS (Longest Common Substring)
// ------------------------------------------------------------
vector<vector<int>> lcsTab(const string &a, const string &b) {
  int n = a.size(), m = b.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i - 1] == b[j - 1]) {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      } else {
        dp[i][j] = 0; // reset for substring logic
      }
    }
  }
  return dp;
}

// ------------------------------------------------------------
// Function 2: Print the Longest Common Substring (independent)
// ------------------------------------------------------------
string printLCS(const string &a, const string &b, vector<vector<int>> &dp) {
  int n = a.size(), m = b.size();
  int maxLen = 0, endIndex = -1;

  // find the maximum value in dp table
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (dp[i][j] > maxLen) {
        maxLen = dp[i][j];
        endIndex = i - 1;
      }
    }
  }

  if (maxLen == 0)
    return "";

  return a.substr(endIndex - maxLen + 1, maxLen);
}

// ------------------------------------------------------------
// Function 3: Longest Palindromic Subword (Substring)
// ------------------------------------------------------------
string longestPalindromicSubword(const string &s) {
  string rev = string(s.rbegin(), s.rend());

  // create dp table for s and reverse(s)
  vector<vector<int>> dp = lcsTab(s, rev);

  // extract longest common substring (palindromic substring)
  string res = printLCS(s, rev, dp);

  return res;
}

// ------------------------------------------------------------
// Driver
// ------------------------------------------------------------
int main() {
  string s;
  cout << "Enter string: ";
  cin >> s;

  string ans = longestPalindromicSubword(s);
  cout << "Longest Palindromic Subword = " << ans << endl;

  return 0;
}

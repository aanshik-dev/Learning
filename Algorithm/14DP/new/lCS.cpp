#include <bits/stdc++.h>
using namespace std;

////////////////////////////////////////////////////
// 1) RECURSIVE + MEMOIZATION
////////////////////////////////////////////////////
int lcsRec(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) {
  if (i == 0 || j == 0)
    return 0;

  if (dp[i][j] != -1)
    return dp[i][j];

  if (s1[i - 1] == s2[j - 1])
    return dp[i][j] = 1 + lcsRec(i - 1, j - 1, s1, s2, dp);

  return dp[i][j] = max(lcsRec(i - 1, j, s1, s2, dp),
                        lcsRec(i, j - 1, s1, s2, dp));
}

////////////////////////////////////////////////////
// 2) TABULATION (BOTTOM-UP)
////////////////////////////////////////////////////
vector<vector<int>> buildDP(string &s1, string &s2) {
  int n = s1.size();
  int m = s2.size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  return dp;
}

int lcsTab(string &s1, string &s2) {
  auto dp = buildDP(s1, s2);
  return dp[s1.size()][s2.size()];
}

////////////////////////////////////////////////////
// 3) PRINT THE LCS SUBSEQUENCE
////////////////////////////////////////////////////
string printLCS(string &s1, string &s2) {
  auto dp = buildDP(s1, s2);

  int i = s1.size();
  int j = s2.size();

  string ans = "";

  while (i > 0 && j > 0) {
    if (s1[i - 1] == s2[j - 1]) {
      ans += s1[i - 1]; // match → include character
      i--, j--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }

  reverse(ans.begin(), ans.end());
  return ans;
}

////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////
int main() {
  string s1, s2;
  cout << "Enter first string: ";
  cin >> s1;
  cout << "Enter second string: ";
  cin >> s2;

  int n = s1.size();
  int m = s2.size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

  int recAns = lcsRec(n, m, s1, s2, dp);
  int tabAns = lcsTab(s1, s2);
  string subseq = printLCS(s1, s2);

  cout << "LCS Length (Recursive + Memo) = " << recAns << "\n";
  cout << "LCS Length (Tabulation) = " << tabAns << "\n";
  cout << "LCS Subsequence = " << subseq << "\n";

  return 0;
}

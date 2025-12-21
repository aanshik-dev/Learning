#include <bits/stdc++.h>
using namespace std;

int main() {
  string input = "bacdfea";
  int n = input.length();
  string dp[n];
  dp[0] = input.substr(0, 1);
  dp[1] = dp[0] + input.substr(1, 1);
  for (int i = 2; i < n; i++) {
    dp[i] = min(dp[i - 1] + input.substr(i, 1), dp[i - 2] + input.substr(i, 1));
  }

  cout << "Smallest lexicographic string is: " << dp[n - 1] << endl;
  return 0;
}
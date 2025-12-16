#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int coinChange(vector<int> &coins, int amount) {
    int n = coins.size();
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
      for (int j = 0; j < n; j++) {
        if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
          dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        }
      }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
  }
};

int main() {
  vector<int> coins = {2, 5};
  int amount = 11;
  Solution sol;
  int res = sol.coinChange(coins, amount);
  cout << res << endl;
  return 0;
}

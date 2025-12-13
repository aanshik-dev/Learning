#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int coinChange(vector<int> &coins, int amount, vector<vector<int>> &dp, int i) {
    if (amount == 0)
      return 0;
    if (i == 0) {
      if (amount % coins[0] == 0)
        return amount / coins[0];
      else
        return INT_MAX;
    }
    if (dp[i][amount] != -1)
      return dp[i][amount];
    int notTake = coinChange(coins, amount, dp, i - 1);
    int take = INT_MAX;
    if (amount >= coins[i]) {
      take = coinChange(coins, amount - coins[i], dp, i);
      if (take != INT_MAX)
        take += 1;
    }
    dp[i][amount] = min(take, notTake);
    return dp[i][amount];
  }

  public:
  int coinChange2(vector<int> &coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int>(amount + 1, INT_MAX));

    for (int i = 0; i < n; i++) {
      dp[i][0] = 0;
    }
    for (int i = 0; i <= amount; i++) {
      if (i % coins[0] == 0)
        dp[0][i] = i / coins[0];
      else
        dp[0][i] = INT_MAX;
    }
    for (int i = 1; i < n; i++) {
      for (int j = 1; j <= amount; j++) {
        int notTake = dp[i - 1][j];
        int take = INT_MAX;
        if (j >= coins[i]) {
          take = dp[i][j - coins[i]];
          if (take != INT_MAX)
            take += 1;
        }
        dp[i][j] = min(take, notTake);
      }
    }
    return dp[n - 1][amount] == INT_MAX ? -1 : dp[n - 1][amount];
  }
};

int main() {
  vector<int> coins = {2, 1, 5};
  int amount = 11;
  int n = coins.size();
  Solution sol;
  vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
  int res = sol.coinChange(coins, amount, dp, n - 1);
  cout << res << endl;
  int res2 = sol.coinChange2(coins, amount);
  cout << res2 << endl;
  return 0;
}

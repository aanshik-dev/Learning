#include <bits/stdc++.h>
using namespace std;

int knapSack(vector<int> &prft, vector<int> &wt, int Capacity, int i, vector<vector<int>> &dp) {
  if (Capacity == 0) {
    return 0;
  }
  if (i == 0) {
    if (Capacity >= wt[0])
      return prft[0];
    else {
      return 0;
    }
  }
  int n = prft.size();
  if (dp[i][Capacity] != -1)
    return dp[i][Capacity];
  int notTake = knapSack(prft, wt, Capacity, i - 1, dp);
  int take = 0;
  if (wt[i] <= Capacity) {
    take = knapSack(prft, wt, Capacity - wt[i], i - 1, dp) + prft[i];
  }
  dp[i][Capacity] = max(take, notTake);
  return dp[i][Capacity];
}

int tabKnapSack(vector<int> &prft, vector<int> &wt, int Capacity) {
  int n = prft.size();
  vector<vector<int>> dp(n, vector<int>(Capacity + 1, 0));
  for (int i = 0; i < n; i++) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= Capacity; i++) {
    if (i < wt[0])
      dp[0][i] = 0;
    else
      dp[0][i] = prft[0];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < Capacity + 1; j++) {
      int notTake = dp[i - 1][j];
      int take = 0;
      if (wt[i] <= j) {
        take = dp[i - 1][j - wt[i]] + prft[i];
      }
      dp[i][j] = max(take, notTake);
    }
  }
  return dp[n - 1][Capacity];
}

int main() {

  vector<int> prft = {20, 30, 35, 12};
  vector<int> wt = {2, 5, 7, 3};
  int Capacity = 10;
  int n = prft.size();
  vector<vector<int>> dp(n, vector<int>(Capacity + 1, -1));
  cout << knapSack(prft, wt, Capacity, n - 1, dp) << endl;
  cout << tabKnapSack(prft, wt, Capacity) << endl;
  return 0;
}
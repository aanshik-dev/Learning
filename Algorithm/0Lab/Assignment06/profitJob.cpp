#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> p = {2, 8, 3, 1, 6, 9, 23};
  vector<int> dp;
  dp.push_back(p[0]);
  dp.push_back(max(p[0], p[1]));
  for (int i = 2; i < p.size(); i++) {
    dp.push_back(max(dp[i - 1], dp[i - 2] + p[i]));
  }
  cout << "The maximum profit is: " << dp[p.size() - 1] << endl;
  return 0;
}
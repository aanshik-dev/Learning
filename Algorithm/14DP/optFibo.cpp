#include <iostream>
#include <vector>
using namespace std;

int fibo(int n, vector<int> &dp) {
  if (n <= 1)
    return n;
  if (dp[n] != -1)
    return dp[n];
  int ans = fibo(n - 1, dp) + fibo(n - 2, dp);
  dp[n] = ans;
  return ans;
}

int main() {
  int n;
  cout << "Enter the number: ";
  cin >> n;

  vector<int> arr(n + 1, -1);
  arr[0] = 0;
  arr[1] = 1;
  for (int i = 2; i <= n; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  cout << "Through Loop: " << arr[n] << endl;

  vector<int> dp(n + 1, -1);
  int ans = fibo(n, dp);
  cout << "Through Recursion: " << ans << endl;

  return 0;
}
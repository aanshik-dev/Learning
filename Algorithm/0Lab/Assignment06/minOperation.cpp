#include <bits/stdc++.h>
using namespace std;

//  1 2 3 4 5 6 7 8 9
//  0 1 1 2 3 2 3 3 2
int main() {

  int num;
  cout << "Enter a number: ";
  cin >> num;
  vector<int> dp(num + 1, 0);
  for (int i = 2; i < dp.size(); i++) {
    int one = numeric_limits<int>::max();
    int two = numeric_limits<int>::max();
    int three = numeric_limits<int>::max();

    if (i % 3 == 0) {
      three = dp[i / 3];
    }
    if (i % 2 == 0) {
      two = dp[i / 2];
    }
    one = dp[i - 1];
    dp[i] = min(one, min(two, three)) + 1;
  }

  cout << "The number of ways are: " << dp[num] << endl;

  return 0;
}
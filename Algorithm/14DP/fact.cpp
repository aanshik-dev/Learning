#include <iostream>
#include <vector>
using namespace std;

int fact(int n) {
  if (n <= 1)
    return 1;
  return n * fact(n - 1);
}

int main() {
  int n;
  cout << "Enter the number: ";
  cin >> n;
  int ans = fact(n);
  cout << "Through Recursion:" << ans << endl;
  // Top Down approach - Memoization
  ans = 1;
  for (int i = 1; i <= n; i++) {
    ans *= i;
  }
  cout << "Through Loop:" << ans << endl;
  // Bottom Up approach - Tabulation

  return 0;
}
#include <iostream>
using namespace std;

class Solution {
  public:
  int mySqrt(int x) {
    long long int st = 0, end = x;
    int ans = 0;
    while (st <= end) {
      long long int mid = (st + end) / 2;
      cout << st << " " << end << " " << mid << " " << ans << endl;
      if (mid * mid <= x) {
        ans = mid;
        st = mid + 1;
      } else {
        end = mid - 1;
      }
    }
    return ans;
  }
};

int main() {

  cout << Solution().mySqrt(2147395599) << endl;

  return 0;
}
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
  int maxArea(vector<int> &height) {
    int i = 0, j = height.size() - 1;
    int maxWater = 0;
    while (i < j) {
      int area = (j - i) * min(height[i], height[j]);
      maxWater = max(maxWater, area);
      if (height[i] < height[j]) {
        i++;
      } else {
        j--;
      }
    }
    return maxWater;
  }
};

int main() {
  Solution sol;
  vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  int water = sol.maxArea(height);
  cout << water << endl;
  return 0;
}
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

class Solution {

  public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {

    vector<int> vect1 = nums1, vect2 = nums2;
    int s1 = nums1.size();
    int s2 = nums2.size();

    if (s2 < s1) {
      vector<int> temp = vect1;
      vect1 = vect2;
      vect2 = temp;
      int tempSize = s1;
      s1 = s2;
      s2 = tempSize;
    }

    int start = 0, end = s1;
    while (1) {
      int part1 = (start + end) / 2;
      int part2 = (s1 + s2 + 1) / 2 - part1;
      int pre1 = (part1 == 0) ? numeric_limits<int>::min() : vect1[part1 - 1];
      int suc1 = (part1 == s1) ? numeric_limits<int>::max() : vect1[part1];
      int pre2 = (part2 == 0) ? numeric_limits<int>::min() : vect2[part2 - 1];
      int suc2 = (part2 == s2) ? numeric_limits<int>::max() : vect2[part2];
      if (pre1 <= suc2 && pre2 <= suc1) {
        if ((s1 + s2) % 2 == 0) {
          return (max(pre1, pre2) + min(suc1, suc2)) / 2.0;
        } else {
          return max(pre1, pre2);
        }
      } else if (pre1 > suc2) {
        end = part1 - 1;
      } else {
        start = part1 + 1;
      }
    }
  }
};

int main() {
  return 0;
}
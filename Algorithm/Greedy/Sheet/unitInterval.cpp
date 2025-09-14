// Describe an efficient algorithm that, given a set { x1, x2, . . . , xn } of points on the real line, determines the minimum number of unit-length closed intervals that contains all of the given points. Prove the correctness of your algorithm.

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int countUnit(vector<float> points) {
  int count = 0;
  float prev = -numeric_limits<float>::min();
  sort(points.begin(), points.end());
  for (int i = 0; i < points.size(); i++) {
    if (points[i] > prev) {
      count++;
      prev = points[i] + 1;
    }
  }
  return count;
}

int main() {
  vector<float> points = {0.2, 0.5, 0.9, 1.2};
  cout << "Count: " << countUnit(points) << endl;
  return 0;
}
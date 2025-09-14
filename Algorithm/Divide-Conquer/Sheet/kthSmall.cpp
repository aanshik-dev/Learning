#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> A = {1, 9, 2, 6, 3, 7, 3, 10};
  vector<int> B = {1, 6, 8, 2, 5, 11, 4, 2, 3};

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  return 0;
}
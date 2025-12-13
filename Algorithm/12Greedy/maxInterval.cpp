#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

bool comparator(pair<int, int> p1, pair<int, int> p2) {
  return p1.second < p2.second;
}

vector<pair<int, int>> maxInterval(vector<pair<int, int>> &gaps) {
  sort(gaps.begin(), gaps.end(), comparator);
  vector<pair<int, int>> res;
  int bound = numeric_limits<int>::min();
  for (int i = 0; i < gaps.size(); i++) {
    if (gaps[i].first >= bound) {
      res.push_back(gaps[i]);
      bound = gaps[i].second;
    }
  }
  return res;
}

int main() {
  vector<pair<int, int>> intervals = {{1, 4}, {6, 9}, {10, 12}, {14, 16}, {3, 7}, {3, 7}, {8, 11}, {11, 15}, {11, 15}};

  vector<pair<int, int>> res = maxInterval(intervals);
  cout << endl;
  for (int i = 0; i < res.size(); i++) {
    cout << "[ " << res[i].first << " , " << res[i].second << " ] ";
  }
  cout << "\n\n";
  return 0;
}
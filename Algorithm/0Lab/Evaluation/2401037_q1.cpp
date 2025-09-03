#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> merged(vector<pair<int, int>> &pairs, int st, int end) {
  if (st == end) {
    vector<pair<int, int>> ret;
    ret.emplace_back(pairs[st]);
    return ret;
  }
  int mid = st + (end - st) / 2;
  vector<pair<int, int>> left = merged(pairs, st, mid);
  vector<pair<int, int>> right = merged(pairs, mid + 1, end);

  vector<pair<int, int>> result = left;
  if (result.back().second >= right.front().first) {
    result.back().second = max(result.back().second, right.front().second);
    for (int i = 1; i < right.size(); i++) {
      result.push_back(right[i]);
    }
  } else {
    for (int i = 0; i < right.size(); i++) {
      result.push_back(right[i]);
    }
  }
  return result;
}

int main() {
  int n;
  cout << "Enter the number of pairs : ";
  cin >> n;
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x;
    cin >> y;
    pairs.emplace_back(x, y);
  }
  sort(pairs.begin(), pairs.end());

  vector<pair<int, int>> res;
  res = merged(pairs, 0, pairs.size() - 1);

  for (int i = 0; i < res.size(); i++) {
    cout << "[ " << res[i].first << " , " << res[i].second << " ]" << endl;
  }
  return 0;
}
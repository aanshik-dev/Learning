#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<pair<int, int>>> minGroup(vector<pair<int, int>> &gaps) {
  sort(gaps.begin(), gaps.end());
  vector<vector<pair<int, int>>> groups;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

  for (int i = 0; i < gaps.size(); i++) {
    if (!pq.empty() && pq.top().first <= gaps[i].first) {
      int idx = pq.top().second;
      pq.pop();
      groups[idx].emplace_back(gaps[i]);
      pq.push({gaps[i].second, idx});
    } else {
      int idx = groups.size();
      groups.emplace_back(vector<pair<int, int>>({gaps[i]}));
      pq.push({gaps[i].second, idx});
    }
  }
  return groups;
}

int main() {
  vector<pair<int, int>> intervals = {{1, 10}, {2, 7}, {3, 6}, {8, 9}};

  vector<vector<pair<int, int>>> res = minGroup(intervals);
  cout << endl;
  for (int i = 0; i < res.size(); i++) {
    for (auto j : res[i]) {
      cout << "[ " << j.first << " , " << j.second << " ] ";
    }
    cout << "\n";
  }
  cout << "\n";
  return 0;
}
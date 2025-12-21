#include <bits/stdc++.h>
using namespace std;

vector<int> selectJobs(vector<pair<int, int>> &jobs) {
  sort(jobs.begin(), jobs.end(),
      [](auto &a, auto &b) { return a.first < b.first; });

  vector<int> res;
  int time = 0;

  for (int i = 0; i < jobs.size();) {
    int commondl = jobs[i].first;
    priority_queue<int> pq;

    int j = i;
    while (j < jobs.size() && jobs[j].first == commondl) {
      pq.push(jobs[j].second);
      j++;
    }

    int slots = min(commondl - time, (int)pq.size());
    while (slots-- > 0 && !pq.empty()) {
      res.push_back(pq.top());
      pq.pop();
      time++;
    }
    i = j;
  }
  return res;
}

int main() {
  int size;
  cout << "Enter the size of array : ";
  cin >> size;

  vector<pair<int, int>> jobs(size);
  cout << "Enter the pairs in format (deadline profit):\n";
  for (int i = 0; i < size; i++)
    cin >> jobs[i].first >> jobs[i].second;

  vector<int> res = selectJobs(jobs);
  cout << "Selected profits: ";
  for (int p : res)
    cout << p << " ";
  cout << "\n";
}

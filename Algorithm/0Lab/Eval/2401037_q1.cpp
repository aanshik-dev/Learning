#include <bits/stdc++.h>
using namespace std;

struct Job {
  int dl;
  int pr;
};

int findSlot(vector<int> &hashdl, int x) {
  if (x <= 0)
    return 0;
  if (hashdl[x] == x)
    return x;
  return hashdl[x] = findSlot(hashdl, hashdl[x]);
}

vector<int> selectJobs(vector<Job> &jobs) {
  sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) { return a.pr > b.pr; });

  int maxD = 0;
  for (auto &j : jobs)
    maxD = max(maxD, j.dl);

  vector<int> hashdl(maxD + 1);
  iota(hashdl.begin(), hashdl.end(), 0);

  vector<int> chosen;
  for (auto &j : jobs) {
    int slot = findSlot(hashdl, j.dl);
    if (slot > 0) {
      chosen.push_back(j.pr);
      hashdl[slot] = findSlot(hashdl, slot - 1);
    }
  }
  return chosen;
}

int main() {
  int n;
  cout << "Enter number of jobs: ";
  cin >> n;

  vector<Job> jobs(n);
  cout << "Enter jobs as (dl pr):\n";
  for (int i = 0; i < n; i++)
    cin >> jobs[i].dl >> jobs[i].pr;

  vector<int> selected = selectJobs(jobs);

  int totalpr = accumulate(selected.begin(), selected.end(), 0);

  cout << "Selected job prs: ";
  for (int p : selected)
    cout << p << " ";
  cout << "\nTotal pr: " << totalpr << "\n";
  return 0;
}

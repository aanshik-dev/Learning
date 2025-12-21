// Consider the following scheduling problem: n jobs are given as input. Job j (1 ≤j ≤ n) has a processing time pj (pj > 0) and a non-negative weight wj (wj ≥0). We mustconstruct a schedule for these jobs on a single machine such that at most one job isprocessed at each point in time, and each job must be processed non-preemptively; that is, once a job begins to be processed, it must be processed completely before any other job begins its processing. The objective is to find a schedule that minimizes the weighted sum of completion times: ∑nj=1 wj Cj.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<pair<float, float>> jobs = {{1, 2}, {3, 7}, {5, 6}};

  sort(jobs.begin(), jobs.end(), [](pair<float, float> a, pair<float, float> b) { return (a.second / a.first) > (b.second / b.first); });

  for (auto job : jobs) {
    cout << ">> " << job.first << " " << job.second << "  ";
  }

  return 0;
}
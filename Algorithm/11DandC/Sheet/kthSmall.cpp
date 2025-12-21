// #include <algorithm>
// #include <iostream>
// #include <vector>
// using namespace std;

// int main() {
//   vector<int> A = {1, 9, 2, 6, 3, 7, 3, 10};
//   vector<int> B = {1, 6, 8, 2, 5, 11, 4, 2, 3};

//   sort(A.begin(), A.end());
//   sort(B.begin(), B.end());
//   return 0;
// }

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using P = pair<int, int>;

inline double dist(const P &a, const P &b) {
  long long dx = a.first - b.first;
  long long dy = a.second - b.second;
  return sqrt((double)dx * dx + (double)dy * dy);
}

pair<P, P> ClosestPairRec(vector<P> &Px, vector<P> &Py) {
  int n = Px.size();
  if (n <= 3) {
    double best = DBL_MAX;
    pair<P, P> bestPair;
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
        if (dist(Px[i], Px[j]) < best) {
          best = dist(Px[i], Px[j]);
          bestPair = {Px[i], Px[j]};
        }
    return bestPair;
  }

  int mid = n / 2;
  int midX = Px[mid].first;
  vector<P> Qx(Px.begin(), Px.begin() + mid);
  vector<P> Rx(Px.begin() + mid, Px.end());

  vector<P> Qy, Ry;
  Qy.reserve(mid);
  Ry.reserve(n - mid);
  for (auto &p : Py)
    (p.first <= midX ? Qy : Ry).push_back(p);

  auto qPair = ClosestPairRec(Qx, Qy);
  auto rPair = ClosestPairRec(Rx, Ry);

  double delta = min(dist(qPair.first, qPair.second),
                     dist(rPair.first, rPair.second));

  vector<P> Sy;
  for (auto &p : Py)
    if (abs(p.first - midX) < delta)
      Sy.push_back(p);

  double best = delta;
  pair<P, P> bestPair;
  if (dist(qPair.first, qPair.second) < dist(rPair.first, rPair.second))
    bestPair = qPair;
  else
    bestPair = rPair;

  for (size_t i = 0; i < Sy.size(); ++i)
    for (size_t j = i + 1; j < Sy.size() && j <= i + 15; ++j)
      if (dist(Sy[i], Sy[j]) < best) {
        best = dist(Sy[i], Sy[j]);
        bestPair = {Sy[i], Sy[j]};
      }

  return bestPair;
}

pair<P, P> ClosestPair(vector<P> &points) {
  vector<P> Px = points;
  vector<P> Py = points;
  sort(Px.begin(), Px.end(),
       [](auto &a, auto &b) { return a.first < b.first; });
  sort(Py.begin(), Py.end(),
       [](auto &a, auto &b) { return a.second < b.second; });
  return ClosestPairRec(Px, Py);
}

int main() {
  vector<P> pts = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
  auto ans = ClosestPair(pts);
  cout << "Closest pair: (" << ans.first.first << "," << ans.first.second
       << ") and (" << ans.second.first << "," << ans.second.second
       << ")\nDistance = "
       << dist(ans.first, ans.second) << "\n";
  return 0;
}

#include <iostream>
#include <vector>
using namespace std;

int peak(vector<int> &vect, int st, int end) {
  if (end - st <= 1) {
    return max(vect[st], vect[end]);
  }
  int mid = st + (end - st) / 2;
  if (vect[mid] > vect[mid - 1] && vect[mid] > vect[mid + 1]) {
    return vect[mid];
  } else if (vect[mid] > vect[mid - 1] && vect[mid] < vect[mid + 1]) {
    return peak(vect, mid, end);
  } else {
    return peak(vect, st, mid);
  }
}

int main() {

  int n;
  cout << "Enter size of array: ";
  cin >> n;
  cout << "Enter elements of array: ";
  vector<int> vect;
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    vect.push_back(k);
  }

  int result = peak(vect, 0, vect.size() - 1);
  cout << "The peak element is: " << result << endl;

  return 0;
}
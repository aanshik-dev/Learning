#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int> &vect, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  vector<int> vLeft(n1), vRight(n2);
  for (int i = 0; i < n1; i++)
    vLeft[i] = vect[left + i];
  for (int i = 0; i < n2; i++)
    vRight[i] = vect[mid + 1 + i];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (vLeft[i] <= vRight[j]) {
      vect[k++] = vLeft[i++];
    } else {
      vect[k++] = vRight[j++];
    }
  }
  while (i < n1) {
    vect[k++] = vLeft[i++];
  }
  while (j < n2) {
    vect[k++] = vRight[j++];
  }
}

void mergeSort(vector<int> &vect, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(vect, left, mid);
    mergeSort(vect, mid + 1, right);
    merge(vect, left, mid, right);
  }
}

int main() {
  vector<int> input = {3, 5, 9, 7, 6, 5, 1, 10};

  mergeSort(input, 0, input.size() - 1);

  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  return 0;
}

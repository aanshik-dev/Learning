#include <iostream>
#include <vector>
using namespace std;

void quickSort(vector<int> &arr, int low, int high) {
  if (low < high) {
    int pivot = arr[high];
    int k = low;
    for (int i = low; i < high; i++) {
      if (arr[i] < pivot) {
        swap(arr[i], arr[k++]);
      }
    }
    swap(arr[high], arr[k]);
    quickSort(arr, low, k - 1);
    quickSort(arr, k + 1, high);
  }
}

int main() {
  vector<int> input = {3, 5, 9, 7, 6, 5, 1, 10};

  quickSort(input, 0, input.size() - 1);

  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  return 0;
}
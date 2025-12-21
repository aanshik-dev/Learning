#include <iostream>
#include <vector>
using namespace std;

void insertSort(vector<int> &input) {
  for (int i = 1; i < input.size(); i++) {
    int temp = input[i];
    int j = i - 1;
    while (j >= 0 && input[j] > temp) {
      input[j + 1] = input[j];
      j--;
    }
    input[j + 1] = temp;
  }
}

int main() {
  vector<int> input = {3, 5, 9, 7, 6, 5, 1, 10};
  insertSort(input);
  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  return 0;
}
#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int> &input) {
  for (int i = 0; i < input.size(); i++) {
    for (int j = 1; j < input.size() - i; j++) {
      if (input[j - 1] > input[j]) {
        swap(input[j], input[j - 1]);
      }
    }
  }
}

int main() {
  vector<int> input = {3, 5, 9, 7, 6, 5, 1, 10};

  bubbleSort(input);

  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  return 0;
}
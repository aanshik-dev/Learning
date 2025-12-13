#include <iostream>
#include <vector>
using namespace std;

void selectSort(vector<int> &input) {
  for (int i = 0; i < input.size() - 1; i++) {
    int min = i;
    for (int j = i + 1; j < input.size(); j++) {
      if (input[j] < input[min]) {
        min = j;
      }
    }
    swap(input[i], input[min]);
  }
}

int main() {
  vector<int> input = {3, 5, 9, 7, 6, 5, 1, 10};

  selectSort(input);

  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  return 0;
}
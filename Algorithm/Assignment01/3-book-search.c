#include <stdio.h>

// 2 4 6 8 10 12 14 16

// (13*7)/14 => 6 + {1*2/4}

int bookSearch(int *arr, int st, int end, int target) {
  int pos = -1;
  int val = st + ((target - arr[st])*(end - st)) / (arr[end] - arr[st]);
  if(val == st && arr[val] != target) {
    return -1;
  }
  if (arr[val] == target) {
    pos = val;
  } else if (arr[val] < target) {
    pos = bookSearch(arr, val, end, target);
  }else if (arr[val] > target) {
    pos = bookSearch(arr, st, val, target);
  }
  return pos;
}

int main() {
  int size, target;
  printf("\nPlease enter the size of the array and the target: ");
  scanf("%d", &size);
  scanf("%d", &target);
  int arr[size];
  printf("Please enter the array: ");
  for (int i = 0; i < size; i++) {
    scanf("%d", &arr[i]);
  }
  int idx = bookSearch(arr, 0, size - 1, target);
  printf("The index is : %d\n\n", idx);
}
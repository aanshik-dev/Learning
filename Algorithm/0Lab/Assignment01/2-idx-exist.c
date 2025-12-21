#include <stdio.h>

int equalIdx(int *arr, int st, int end) {
  // case 1:  -10 -8  2  2  3  4  5  6  8
  // index:    0   1  2  3  4  5  6  7  8

  int mid = (st + end) / 2;
  int idx = -1;
  if (end - st == 1) {
    return arr[end] == end ? end : -1;
  }
  if (arr[mid] == mid) {
    return mid;
  } else if (arr[mid] < mid) {
    idx = equalIdx(arr, mid, end);
  } else if (arr[mid] > mid) {
    idx = equalIdx(arr, st, mid);
  }
  return idx;
}

int main() {
  int size;
  printf("\nPlease enter the size of the array: ");
  scanf("%d", &size);
  int arr[size];
  printf("Please enter the array: ");
  for (int i = 0; i < size; i++) {
    scanf("%d", &arr[i]);
  }
  int min = equalIdx(arr, 0, size - 1);
  printf("The index is : %d\n\n", min);
}
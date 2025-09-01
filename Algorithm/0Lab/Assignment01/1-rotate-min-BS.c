#include <stdio.h>

int minFind(int *arr, int st, int end) {
  int mid = (st + end) / 2;
  if (end - st == 1) {
    return (arr[end] < arr[st] ? end : st);
  }
  int min;
  if (arr[st] >= arr[end]) {
    if (arr[mid] >= arr[st]) {
      min = minFind(arr, mid, end);
    } else {
      min = minFind(arr, st, mid);
    }
  } else {
    return st;
  }
  return min;
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
  int min = minFind(arr, 0, size - 1);
  printf("The index is : %d\n\n", min);

  // case 1: 25 30 35 40 45 50 5 10
  // case 2: 25 30 40 5 8 9 10 15 20
}
#include <stdio.h>

int peakFind(int *arr, int st, int end) {
  int mid = (st + end) / 2;
  if (end - st >= 2) {
    if (arr[mid] < arr[mid + 1] && arr[mid - 1] < arr[mid]) {
      return peakFind(arr, mid, end);
    } else if (arr[mid] > arr[mid + 1] && arr[mid - 1] > arr[mid]) {
      return peakFind(arr, st, mid);
    } else {
      return mid;
    }
  }
  return arr[end] > arr[st] ? end : st;
}

int binSearch(int *arr, int st, int end, int trgt, int dir) {
  int mid = st + (end - st) / 2;
  printf("[%d %d]\n", arr[st], arr[end]);
  if (st <= end) {
    if (arr[mid] == trgt) {
      return mid;
    } else if (arr[mid] < trgt && dir == 1) {
      return binSearch(arr, mid+1, end, trgt, 1);
    } else if (arr[mid] > trgt && dir == 1) {
      return binSearch(arr, st, mid-1, trgt, 1);
    }else if (arr[mid] < trgt && dir == 0) {
      return binSearch(arr, st, mid-1, trgt, 0);
    }else if (arr[mid] > trgt && dir == 0) {
      return binSearch(arr, mid+1, end, trgt, 0);
    }
  }
  return -1;
}

int main() {
  int size, target;
  printf("\nPlease enter the size of the array: ");
  scanf("%d", &size);
  int arr[size];
  printf("Please enter the array: ");
  for (int i = 0; i < size; i++) {
    scanf("%d", &arr[i]);
  }
  printf("Please enter the target value: ");
  scanf("%d", &target);

  int peak_idx = peakFind(arr, 0, size - 1);
  int idx = binSearch(arr, 0, peak_idx, target, 1);
  if(idx == -1) idx = binSearch(arr, peak_idx, size - 1, target, 0);
  printf("The index is : %d\n\n", idx);
}
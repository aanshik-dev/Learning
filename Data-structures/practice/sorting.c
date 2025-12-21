#include <stdio.h>

// 10 2 3 1 56 48 24 79 11 90 35 23 36 78

// 1. start from 1, iterate till end
// 2. let for ith iteration, key = arr[i]
// 3. start from j=i-1, iterate and shift right till value smaller than key = arr[i] is found
// 4. keep arr[j+1] = key
int insertSort(int arr[], int size) {
  for (int i = 1; i < size; i++) {
    int key = arr[i];
    int j = i - 1;
    while (arr[j] > key && j >= 0) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
  return 0;
}

// 1. iterate for n times
// 2. iterate for n-1 times
// 3. start from 0, compare i and i+1, if arr[i+1] < arr[i], then swap
int bubbleSort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j + 1] < arr[j]) {
        arr[j + 1] = arr[j + 1] ^ arr[j];
        arr[j] = arr[j + 1] ^ arr[j];
        arr[j + 1] = arr[j + 1] ^ arr[j];
      }
    }
  }
  return 0;
}

// 1. iterate for n times
// 2. For ith iteration assume min = i as min index
// 3. Start from i+1, iterate till n and update min
// 4. If min != i, swap
int selectSort(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    int min = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[min])
        min = j;
    }
    if (min == i)
      continue;
    arr[i] = arr[i] ^ arr[min];
    arr[min] = arr[i] ^ arr[min];
    arr[i] = arr[i] ^ arr[min];
  }
  return 0;
}

void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  int L[n1], R[n2];
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = (r + l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

// 9, 2, 3, 1, 10, 48, 24, 79, 56, 90, 35, 23, 36, 78

// void quickSort(int arr[], int l, int r) {
//    int pivot = arr[l];
//    int i = l + 1, j = r;
//    while (i <= j) {
//       while (arr[i] < pivot && i <= r)
//          i++;
//       while (arr[j] > pivot && j >= l) {
//          j--;
//       }
//       if (i < j) {
//          arr[i] = arr[i] ^ arr[j];
//          arr[j] = arr[i] ^ arr[j];
//          arr[i] = arr[i] ^ arr[j];
//       }
//    }
//    if (j != l) {
//       arr[l] = arr[l] ^ arr[j];
//       arr[j] = arr[l] ^ arr[j];
//       arr[l] = arr[l] ^ arr[j];
//    }

//    if (l < j) {
//       quickSort(arr, l, j - 1);
//    }
//    if (i < r) {
//       quickSort(arr, j + 1, r);
//    }
//    return;
// }

void quickSort(int arr[], int l, int r) {
  if (l >= r)
    return;
  int pivot = arr[l];
  int i = l + 1, j = r;
  while (i <= j) {
    while (i <= r && arr[i] < pivot)
      i++;
    while (j >= l && arr[j] > pivot)
      j--;
    if (i < j) {
      arr[i] ^= arr[j];
      arr[j] ^= arr[i];
      arr[i] ^= arr[j];
      i++;
      j--;
    }
  }
  if (j > l) {
    arr[l] ^= arr[j];
    arr[j] ^= arr[l];
    arr[l] ^= arr[j];
  }
  quickSort(arr, l, j - 1);
  quickSort(arr, j + 1, r);
}

int main() {
  int arr[] = {9, 2, 3, 1, 10, 48, 24, 79, 56, 90, 35, 23, 36, 78};
  int n = sizeof(arr) / sizeof(int);
  quickSort(arr, 0, n - 1);
  printf("\n[Quick Sort] Sorted Array: ");
  for (int i = 0; i < n; i++) {
    printf(" %d ", arr[i]);
  }
  printf("\n\n");

  return 0;
}
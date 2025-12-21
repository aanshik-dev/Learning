// Write a function in C to implement
// binary search on a sorted array.
#include <stdio.h>
void binsearch(int[], int, int, int);

int main() {
  int find;
  int arr[] = {
      0,
      2,
      4,
      5,
      6,
      8,
      9,
      10,
      13,
      14,
      15,
      17,
      18,
      20};
  int size = sizeof(arr) / sizeof(int);

  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n\n");

  printf("Enter a number to search: ");
  scanf("%d", &find);

  binsearch(arr, size, find, 0);
  return 0;
}

// 0,2,4, 5 ,6,8,9, 10 ,13,14,15,17,18,20
void binsearch(int arr[], int size, int key, int idx) {
  int mid = size / 2;
  if (key == arr[mid]) {
    printf("%d is Present at Position %d\n", key, idx + mid + 1);
    return;
  }
  if (mid == 0) {
    printf("%d is not present in array\n", key);
    return;
  } else {
    if (key > arr[mid]) {
      binsearch(arr + mid + 1, size - mid - 1, key, idx + mid + 1);
    } else if (key < arr[mid]) {
      binsearch(arr, mid, key, idx);
    }
  }
}
/*
// Searches for a number in array
int binSearch(int arr[], int size, int trgt) {
    int left = 0;
    int right = size-1;
    while(left <= right) {
        int mid = (right+left)/2;
        if(trgt == arr[mid])
        return mid+1;
        else if(trgt > arr[mid])
        left = mid +1;
        else
        right = mid -1;
    }
    return 0;
}
*/
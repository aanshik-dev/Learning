#include <stdio.h>

int main() {
   int arr[] = {1, 2, -20, 6, 3, 7, 5, 9, 4, 22, 61, 0};
   int min = arr[1], max = arr[1], n = sizeof(arr) / sizeof(int);
   for (int i = 0; i < n; i++) {
      if (min > arr[i]) {
         min = arr[i];
      }
      if (max < arr[i]) {
         max = arr[i];
      }
   }
   printf("Minimum of array: %d\nMaximum of array: %d\n", min, max);
   return 0;
}
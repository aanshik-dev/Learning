#include <stdio.h>

int main() {
   int arr1[] = {1, 2, 5, 6, 8, 9};
   int arr2[] = {0, 1, 3, 4, 6, 7, 9, 10, 13};
   int n = sizeof(arr1) / sizeof(int), m = sizeof(arr2) / sizeof(int), x = 0, y = 0;
   int arr[n + m];
   for (int i = 0; i < n + m; i++) {
      if (x < n && y < m) {
         if (arr1[x] < arr2[y]) {
            arr[i] = arr1[x];
            x++;
         } else {
            arr[i] = arr2[y];
            y++;
         }
      } else if (x < n) {
         arr[i] = arr1[x];
         x++;
      } else {
         arr[i] = arr2[y];
         y++;
      }
   }
   for (int i = 0; i < n + m; i++) {
      printf(" %d ", arr[i]);
   }
   return 0;
}
#include <stdio.h>

int main() {
   int arr1[] = {1, 3, 6, 2, 8, 4, 7};
   int arr2[] = {6, 9, 1, 5, 5, 0, 1, 6, 3, 2, 12, 3, 9, 4, 0, 10, 0};
   int n = sizeof(arr1) / sizeof(int), m = sizeof(arr2) / sizeof(int), x = 0;
   printf("\nArray 1: ");
   for (int i = 0; i < n; i++) {
      printf("%d ", arr1[i]);
   }
   printf("\nArray 2: ");
   for (int i = 0; i < m; i++) {
      printf("%d ", arr2[i]);
   }
   for (int i = 0; i < n; i++) {
      for (int j = x; j < m; j++) {
         if (arr1[i] == arr2[j]) {
            int temp = arr2[x];
            arr2[x++] = arr2[j];
            arr2[j] = temp;
         }
      }
   }
   for (int i = x; i < m; i++) {
      for (int j = i + 1; j < m; j++) {
         if (arr2[i] > arr2[j]) {
            int temp = arr2[i];
            arr2[i] = arr2[j];
            arr2[j] = temp;
         }
      }
   }

   printf("\n\nArray 2 after processing: ");
   for (int i = 0; i < m; i++) {
      printf("%d ", arr2[i]);
   }
   printf("\n\n");
   return 0;
}
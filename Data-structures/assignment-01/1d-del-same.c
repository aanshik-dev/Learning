#include <stdio.h>

int main() {
   int arr[] = {1, 2, 3, 3, 3, 4, 6, 8, 2, 9, 0};
   int n = sizeof(arr) / sizeof(int);
   printf("Initial Array\n");
   for (int i = 0; i < n; i++) {
      printf(" %d ", arr[i]);
   }
   for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
         if (arr[i] == arr[j]) {
            for (int k = j; k < n; k++) {
               arr[k] = arr[k + 1];
            }
            j--;
            n--;
         }
      }
   }
   printf("\nFinal Array\n");
   for (int i = 0; i < n; i++) {
      printf(" %d ", arr[i]);
   }
   return 0;
}
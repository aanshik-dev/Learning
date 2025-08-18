#include <stdio.h>

int main() {
   int arr[] = {2, 5, 6, 8, 7, 7, 4, 6, 6, 3, 9, 11, 17, 6, 12};
   int n = sizeof(arr) / sizeof(int), m = n;
   printf("\nInitial Array: ");
   for (int i = 0; i < m; i++) {
      printf(" %d ", arr[i]);
   }
   for (int i = 0; i < n; i++) {
      if (arr[i] % 2 == 1) {
         int temp = arr[i];
         for (int j = i; j < m; j++) {
            arr[j] = arr[j + 1];
         }
         arr[m - 1] = temp;
         i--;
         n--;
      }
   }

   printf("\nFinal Array: ");
   for (int i = 0; i < m; i++) {
      printf(" %d ", arr[i]);
   }
   printf("\n\n");
   return 0;
}
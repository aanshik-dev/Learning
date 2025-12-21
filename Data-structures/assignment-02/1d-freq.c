#include <stdio.h>

int main() {
   int arr[] = {1, 3, 5, 3, 6, 6, 8, 3, 1, 2, 0, 4, 4, 4, 9};
   int n = sizeof(arr) / sizeof(int), freq = 1;
   for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
         if (arr[i] == arr[j]) {
            freq++;
            for (int k = j; k < n; k++) {
               arr[k] = arr[k + 1];
            }
            j--;
            n--;
         }
      }
      printf("%d occured %d time in the array\n", arr[i], freq);
      freq = 1;
   }

   return 0;
}
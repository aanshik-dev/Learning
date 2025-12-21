#include <stdio.h>

int main() {
   int arr[] = {1, 2, 0, 4, 5, 0, 0, 6, 7, 0, 9, 0, 0};
   int n = sizeof(arr) / sizeof(int); // 13 with 6 - 0
   for (int i = 0; i < n; i++) {
      if (arr[i] == 0) {
         for (int j = i--; j < n; j++) {
            arr[j] = arr[j + 1];
         }
         arr[--n] = 0;
      }
   }
   for (int i = 0; i < 13; i++) {
      printf(" %d ", arr[i]);
   }
   return 0;
}
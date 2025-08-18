#include <stdio.h>

int main() {
   int arr[] = {1, 2, 3, 5, 8, 3, 0, 7, 5, 6};
   int n = sizeof(arr) / sizeof(int) - 1;
   printf("\nInitial Array : ");
   for (int i = 0; i <= n; i++) {
      printf(" %d ", arr[i]);
   }
   for (int i = 0; i <= n / 2; i++) {
      arr[i] = arr[i] ^ arr[n - i];
      arr[n - i] = arr[i] ^ arr[n - i];
      arr[i] = arr[i] ^ arr[n - i];
   }
   printf(" || ");
   for (int i = 0; i <= n; i++) {
      printf(" %d ", arr[i]);
   }
   printf(" : Final Array\n\n");
   return 0;
}
// Write a program in C to merge two
// arrays of the same size sorted in
// descending order. Merged array should
// remain sorted.

#include <stdio.h>

int main() {
   int arr1[] = {10, 9, 4, 3, 1};
   int arr2[] = {9, 8, 7, 4, 1};
   int size = sizeof(arr1) / sizeof(int);
   for (int i = 0; i < size; i++) {
      printf(" %2d ", arr1[i]);
   }
   printf("\n");
   for (int i = 0; i < size; i++) {
      printf(" %2d ", arr2[i]);
   }
   printf("\n\n");

   int arr[2 * size];
   int a = 0, b = 0;
   for (int i = 0; i < 2 * size; i++) {
      if (arr1[a] > arr2[b])
         arr[i] = arr1[a++];
      else if (arr1[a] <= arr2[b])
         arr[i] = arr2[b++];

      printf(" %d ", arr[i]);
   }

   return 0;
}
// Write a function in C to find the
// second largest element in an array.

#include <stdio.h>

int seclarge(int[], int);

int seclarge(int arr[], int size) {
   int ind, lar = arr[0], sec = arr[0];
   for (int i = 0; i < size; i++) {
      if (arr[i] > lar) {
         lar = arr[i];
         ind = i;
      }
   }
   for (int i = 0; i < size; i++) {
      if (arr[i] > sec && arr[i] < lar) {
         sec = arr[i];
      }
   }
   return sec;
}

int main() {

   int arr[] = {0, 9, 5, 7, 9, 3, 6};
   int size = sizeof(arr) / sizeof(int);
   for (int i = 0; i < size; i++)
      printf("%d  ", arr[i]);
   printf("\n\n");

   printf("The Second Largest Number is: %d\n", seclarge(arr, size));

   return 0;
}

// Write a function in C to generate all random permutation of array elements

#include <stdio.h>

void permute(int[], int);
void prtarr(int[], int);

int main() {
   int arr[] = {1, 2, 3};
   int size = sizeof(arr) / sizeof(int);

   printf("Array : \n");
   prtarr(arr, size);
   endZero(arr, size);
   printf("Sorted Array : \n");
   prtarr(arr, size);

   return 0;
}

// Prints and Array
void prtarr(int arr[], int size) {
   for (int i = 0; i < size; i++)
      printf("%d ", arr[i]);
   printf("\n\n");
}

// 1,2,3,4
//
// sorts an array using insertion sort
void permute(int arr[], int size) {
   if (size = 1)
      printf("%d\n", arr[0]);
   else {
      for (int i = 0; i < size; i++) {
         printf("%d", arr[i]);
         permute(arr, size)
      }
   }
}

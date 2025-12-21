// Write a function in C to move all zeroes to the end of a given array.
#include <stdio.h>
void endZero(int[], int);
void prtarr(int[], int);

int main() {
   int arr[] = {8, 0, 0, 19, 9, 6, 0, 10, 0, 2, 0, 15, 13, 0};
   int size = sizeof(arr) / sizeof(int);

   printf("Unsorted Array : \n");
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

void endZero(int arr[], int size) {
   if (size > 0) {
      if (arr[0] == 0) {
         for (int i = 0; i < size; i++) {
            arr[i] = arr[i + 1];
         }
         arr[size - 1] = 0;
         endZero(arr, size - 1);
      } else if (arr[0] != 0) {
         endZero(arr + 1, size - 1);
      }
   }
}

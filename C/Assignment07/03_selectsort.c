// Write a function in C to implement selection sort.
#include <stdio.h>
void selectSort(int[], int);
void prtarr(int[], int);

int main() {
   int arr[] = {8, 5, 3, 9, 6, 7, 10, 4, 2, 10, 15, 13, 26};
   int size = sizeof(arr) / sizeof(int);

   printf("Unsorted Array : \n");
   prtarr(arr, size);
   selectSort(arr, size);
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

// sorts an array using selection sort
void selectSort(int arr[], int size) {
   int low = arr[0], post = 0;
   for (int i = 0; i < size; i++) {
      if (low > arr[i]) {
         low = arr[i];
         post = i;
      }
   }
   int save = arr[0];
   arr[0] = arr[post];
   arr[post] = save;
   if (size > 1)
      selectSort(arr + 1, size - 1);
}

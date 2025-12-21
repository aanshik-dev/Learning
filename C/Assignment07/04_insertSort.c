// Write a function in C to implement insertion sort.
#include <stdio.h>
void insertSort(int[], int);
void prtarr(int[], int);

int main() {
   int arr[] = {8, 5, 19, 23, 9, 6, 7, 10, 4, 2, 10, 15, 13, 26};
   int size = sizeof(arr) / sizeof(int);

   printf("Unsorted Array : \n");
   prtarr(arr, size);
   insertSort(arr, size);
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
/*
// sorts an array using insertion sort
void insertSort(int arr[], int size) {
    for(int i=1; i<size; i++) {
        for(int j=0; j<i; j++) {
            if(arr[i] < arr[j]) {
                int save = arr[i];
                for(int k=i; k>j; k--) {
                    arr[k]= arr[k-1];
                }
                arr[j] = save;
            }
        }
    }
}*/

// 8,5,19,23,9,6,7,10,4,2,10,15,13,26
void insertSort(int arr[], int size) {
   for (int i = 1; i < size; i++) {
      int key = arr[i];
      int j = i - 1;
      while (arr[j] > key && j >= 0) {
         arr[j + 1] = arr[j];
         j--;
      }
      arr[j + 1] = key;
   }
}

// Write a function in C to check whether an array is a subset of another array.
#include <stdio.h>
int isSubset(int[], int[], int, int);
void prtarr(int[], int);
int binSearch(int[], int, int);
void selectSort(int[], int);

int main() {
   int arr1[] = {
       0,
       1,
       4,
       5,
       2,
       11,
       5,
       8,
       15,
       6,
       21,
       9,
       10,
       13};
   int size1 = sizeof(arr1) / sizeof(int);
   int arr2[] = {
       0,
       2,
       4,
       5,
       6,
       8,
       9,
       10,
       13};
   int size2 = sizeof(arr2) / sizeof(int);
   printf("unsorted Array 1: \n");
   prtarr(arr1, size1);
   selectSort(arr1, size1);
   printf("Sorted Array 1: \n");
   prtarr(arr1, size1);
   printf("Array 2: \n");
   prtarr(arr2, size2);

   int flag = isSubset(arr1, arr2, size1, size2);
   if (flag == 1)
      printf("Array 2 is Subset of Array 1\n");
   else if (flag == 0)
      printf("Array 2 is NOT Subset of Array 1\n");
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
   int low = arr[0],
       post = 0;
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

// Searches for a number in array
int binSearch(int arr[], int size, int trgt) {
   int left = 0;
   int right = size - 1;
   while (left <= right) {
      int mid = (right + left) / 2;
      if (trgt == arr[mid])
         return mid + 1;
      else if (trgt > arr[mid])
         left = mid + 1;
      else
         right = mid - 1;
   }
   return 0;
}

// checks if sunset or not
int isSubset(int arr1[], int arr2[], int size1, int size2) {
   for (int i = 0; i < size2; i++) {
      int flag = binSearch(arr1, size1, arr2[i]);
      if (flag == 0)
         return 0;
   }
   return 1;
}
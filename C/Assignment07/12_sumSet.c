// Write a program in C to find all subarrays with a given sum from a given array.

#include <stdio.h>

void selectSort(int[], int);
void prtarr(int len, int arr[]);
void sumset(int idx, int sum, int trgt, int len, int curlen, int arr[], int temp[]);

int main() {
   int sum;
   int arr[] = {1, 2, 4, 5, 6, 7, 8, 10, 12, 14, 15, 16};
   int len = sizeof(arr) / sizeof(int);
   printf("Array:\n");
   prtarr(len, arr);
   printf("\nEnter The Sum: ");
   scanf("%d", &sum);
   int temp[len];
   selectSort(arr, len);
   printf("\nSubarrays having Sum equal to %d:\n", sum);
   for (int i = 0; i < len; i++) {
      if (arr[i] >= sum) {
         sumset(0, 0, sum, i, 0, arr, temp);
         break;
      }
   }
   return 0;
}

// Prints and Array
void prtarr(int len, int arr[]) {
   for (int i = 0; i < len; i++) {
      printf("%d ", arr[i]);
   }
   printf("\n");
}
// Select Sort an Array
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

void sumset(int idx, int sum, int trgt, int len, int curlen, int arr[], int temp[]) {
   if (sum == trgt) {
      for (int i = 0; i < curlen; i++) {
         printf(" %d ", temp[i]);
      }
      printf("\n");
      return;
   } else if (sum > trgt) {
      return;
   }
   for (int i = idx; i < len; i++) {
      temp[curlen] = arr[i];
      sumset(i + 1, sum + arr[i], trgt, len, curlen + 1, arr, temp);
   }
}
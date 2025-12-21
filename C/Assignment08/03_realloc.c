// Write C program to allocate memory for a 2D array of float.Number rows and
// columns should be user input. Free the memory.

#include <stdio.h>
#include <stdlib.h>
void prtArr(int arr[], int n);

int main() {
   int n;
   printf("Enter Number of Elements: ");
   scanf("%d", &n);
   int *arr;

   arr = (int *)malloc(n * sizeof(int));
   if (arr == NULL) {
      printf("\nERROR: Failed to allocate memory\n");
      return 0;
   } else
      printf("\nSuccess: Memory Allocated\nAddress of Base: %u\n\n", arr);

   printf("Enter the elements of array: \n");
   for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
   }
   printf("Entered Array:\n");
   prtArr(arr, n);

   printf("\nEnter New size of Array: ");
   scanf("%d", &n);

   arr = (int *)realloc(arr, n * sizeof(int));
   if (arr == NULL) {
      printf("\nERROR: Failed to reallocate memory\n");
      return 0;
   } else
      printf("\nSuccess: Memory Reallocated\nAddress of Base: %u\n\n", arr);

   printf("Enter the elements of array: \n");
   for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
   }
   printf("Entered Array:\n");
   prtArr(arr, n);

   free(arr);

   return 0;
}
void prtArr(int arr[], int n) {
   for (int i = 0; i < n; i++)
      printf("%d  ", arr[i]);
   printf("\n");
}

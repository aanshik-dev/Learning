// Write C program to allocate memory for a 1D array of float.Number elements should

// be user input. Store values in the array. Write a function to print those values. Free

// the allocated memory at the end.

#include <stdio.h>
#include <stdlib.h>
void prtArr(float arr[], int n);

int main() {
   int n;
   printf("Enter Number of Elements: ");
   scanf("%d", &n);
   float *arr;
   arr = (float *)malloc(n * sizeof(float));
   if (arr == NULL) {
      printf("ERROR: Failed to allocate memory\n");
      return 0;
   } else
      printf("\nSuccess: Memory Allocated\nAddress of Base: %u\n\n", arr);
   printf("Enter the elements of array: \n");
   for (int i = 0; i < n; i++) {
      scanf("%f", &arr[i]);
   }
   printf("Entered Array:\n");
   prtArr(arr, n);
   free(arr);
   return 0;
}
void prtArr(float arr[], int n) {
   for (int i = 0; i < n; i++)
      printf("%0.2f  ", arr[i]);
   printf("\n");
}
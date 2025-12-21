// Write C program to allocate memory for a 2D array of float.Number rows and columns should be user input. Free the memory.

#include <stdio.h>
#include <stdlib.h>
void prtArr(int row, int col, float **arr);

int main() {
   int n, m;
   printf("Enter Size of 2D Array: ");
   scanf("%d %d", &n, &m);
   float **arr;
   arr = (float **)malloc(n * sizeof(float *));
   if (arr == NULL) {
      printf("\nERROR: Failed to allocate memory\n");
      return 0;
   } else
      printf("\nAddress of Column: %u\n\n", arr);

   for (int i = 0; i < n; i++) {
      arr[i] = (float *)malloc(m * sizeof(float));
      if (arr[i] == NULL) {
         printf("\nERROR: Failed to allocate memory\n");
         return 0;
      } else
         printf("Address of Row[%d]: %u\n", i, arr[i]);
   }

   printf("\nEnter the elements of 2D array\n");
   for (int i = 0; i < n; i++) {
      printf("Row[%d]: ", i + 1);
      for (int j = 0; j < m; j++) {
         scanf("%f", &arr[i][j]);
      }
   }

   printf("\nEntered Array:\n\n");
   prtArr(n, m, arr);
   for (int i = 0; i < n; i++)
      free(arr[i]);
   free(arr);

   return 0;
}
void prtArr(int row, int col, float **arr) {
   for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
         printf("%0.2f ", arr[i][j]);
      }
      printf("\n");
   }
}
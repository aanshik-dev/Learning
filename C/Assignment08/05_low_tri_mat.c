// Write a program in C to dynamically allocate and
// deallocate memory for a lower triangular matrix.

#include <stdio.h>
#include <stdlib.h>
void prtArr(int row, int **arr);

int main() {
   int n;
   printf("Enter Size of Square matrix: ");
   scanf("%d", &n);
   int **arr;
   arr = (int **)malloc(n * sizeof(int));
   if (arr == NULL) {
      printf("\nERROR: Failed to allocate memory\n");
      return 0;
   } else
      printf("\nAddress of Column: %u\n\n", arr);

   for (int i = 0; i < n; i++) {
      arr[i] = (int *)malloc((i + 1) * sizeof(int));
      if (arr[i] == NULL) {
         printf("\nERROR: Failed to allocate memory\n");
         return 0;
      } else
         printf("Address of Row[%d]: %u\n", i, arr[i]);
   }

   printf("\nEnter elements of lower triangular Matrix\n");
   for (int i = 0; i < n; i++) {
      printf("Row[%d]: ", i + 1);
      for (int j = 0; j < i + 1; j++) {
         scanf("%d", &arr[i][j]);
      }
   }

   printf("\nLower Triangular Matrix:\n\n");
   prtArr(n, arr);
   for (int i = 0; i < n; i++)
      free(arr[i]);
   free(arr);

   return 0;
}
void prtArr(int row, int **arr) {
   for (int i = 0; i < row; i++) {
      for (int j = 0; j < i + 1; j++) {
         printf("%d ", arr[i][j]);
      }
      for (int j = i + 1; j < row; j++)
         printf("%d ", 0);
      printf("\n");
   }
}
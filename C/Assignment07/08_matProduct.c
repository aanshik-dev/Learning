// Write a program in C for the multiplication of two matrices.
#include <stdio.h>
void arrin(int row, int col, int arr[row][col]);
void prtarr(int row, int col, int arr[row][col]);
void matProduct(int row1, int col1, int col2, int arr1[row1][col1], int arr2[col1][col2], int arr[row1][col2]);

int main() {
   int row1, col1, row2, col2;
   printf("Enter Row and Columns of Matrix A: ");
   scanf("%d %d", &row1, &col1);
   int arr1[row1][col1];
   arrin(row1, col1, arr1);
   printf("\nMatrix A:\n");
   prtarr(row1, col1, arr1);

   printf("Enter Row and Columns of Matrix B: ");
   scanf("%d %d", &row2, &col2);
   int arr2[row2][col2];
   arrin(row2, col2, arr2);
   printf("\nMatrix B:\n");
   prtarr(row2, col2, arr2);

   if (col1 == row2) {
      int arr[row1][col2];
      matProduct(row1, col1, col2, arr1, arr2, arr);
      printf("\nMatrix A x B:\n");
      prtarr(row1, col2, arr);
   } else
      printf("\nColumns of A Should be Equal to rows of B\n");
   return 0;
}
// Takes array as input
void arrin(int row, int col, int arr[row][col]) {
   printf("\nEnter Rows of Matrix with %d elements\n", col);
   for (int i = 0; i < row; i++) {
      printf("Row[%d]: ", i + 1, col);
      for (int j = 0; j < col; j++) {
         scanf("%d", &arr[i][j]);
      }
   }
}

// Prints and Array
void prtarr(int row, int col, int arr[row][col]) {
   for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
         printf("%d ", arr[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}

void matProduct(int row1, int col1, int col2, int arr1[row1][col1], int arr2[col1][col2], int arr[row1][col2]) {
   for (int i = 0; i < row1; i++) {
      for (int j = 0; j < col2; j++) {
         int sum = 0;
         for (int k = 0; k < col1; k++) {
            sum = sum + (arr1[i][k] * arr2[k][j]);
         }
         arr[i][j] = sum;
      }
   }
}
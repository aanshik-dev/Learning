// Write a function in C for the addition of two matrices of the same size
#include <stdio.h>
void arrin(int row, int col, int arr[row][col]);
void prtarr(int row, int col, int arr[row][col]);
void matsum(int row, int col, int arr1[row][col], int arr2[row][col], int arr[row][col]);

int main() {
   int row, col; // 4x 6
   printf("Enter Row and Columns of  Matrix A: ");
   scanf("%d %d", &row, &col);
   int arr1[row][col];
   arrin(row, col, arr1);
   printf("\nMatrix A:\n");
   prtarr(row, col, arr1);

   int arr2[row][col];
   arrin(row, col, arr2);
   printf("\nMatrix B:\n");
   prtarr(row, col, arr2);

   int arr[row][col];
   matsum(row, col, arr1, arr2, arr);
   printf("\nMatrix A + B:\n");
   prtarr(row, col, arr);
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

void matsum(int row, int col, int arr1[row][col], int arr2[row][col], int arr[row][col]) {
   for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
         arr[i][j] = arr1[i][j] + arr2[i][j];
      }
   }
}
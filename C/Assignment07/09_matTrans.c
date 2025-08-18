// Write a function in C to find the transpose of a given matrix.

#include <stdio.h>
void arrin(int row, int col, int arr[row][col]);
void prtarr(int row, int col, int arr[row][col]);
void matTrans(int row, int col, int arr1[row][col], int arr2[col][row]);

int main() {
   int row, col;
   printf("Enter Row and Columns of Matrix: ");
   scanf("%d %d", &row, &col);
   int arr1[row][col];
   arrin(row, col, arr1);
   printf("\nMatrix A:\n");
   prtarr(row, col, arr1);

   int arr2[col][row];
   matTrans(row, col, arr1, arr2);
   printf("\nTranspose Of Matrix\n");
   prtarr(col, row, arr2);

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

void matTrans(int row, int col, int arr1[row][col], int arr2[col][row]) {
   for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
         arr2[j][i] = arr1[i][j];
      }
   }
}
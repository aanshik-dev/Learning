// Write a function in C for the addition of two matrices of the same size
#include <stdio.h>
void arrin(int row, int col, int arr[row][col]);
void prtarr(int row, int col, int arr[row][col]);
void rowcolSum(int row, int col, int arr[row][col], int rowarr[row][1], int colarr[1][col]);

int main() {
   int row, col; // 4x 6
   printf("Enter Row and Columns of  Matrix: ");
   scanf("%d %d", &row, &col);
   int arr[row][col];
   int rowarr[row][1];
   int colarr[1][col];
   arrin(row, col, arr);
   printf("\nInput Matrix:\n");
   prtarr(row, col, arr);

   rowcolSum(row, col, arr, rowarr, colarr);
   printf("\nSum of Rows of Matrix:\n");
   prtarr(row, 1, rowarr);
   printf("\nSum of Columns of Matrix:\n");
   prtarr(1, col, colarr);
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

void rowcolSum(int row, int col, int arr[row][col], int rowarr[row][1], int colarr[1][col]) {
   for (int i = 0; i < row; i++) {
      int sum = 0;
      for (int j = 0; j < col; j++) {
         sum = sum + arr[i][j];
      }
      rowarr[i][0] = sum;
   }
   for (int i = 0; i < col; i++) {
      int sum = 0;
      for (int j = 0; j < row; j++) {
         sum = sum + arr[j][i];
      }
      colarr[0][i] = sum;
   }
}

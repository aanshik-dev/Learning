// Write a function in C to check whether a given matrix is an identity matrix.
#include <stdio.h>
void arrin(int row, int col, int arr[row][col]);
void prtarr(int row, int col, int arr[row][col]);
int isMatI(int row, int col, int arr[row][col]);

int main() {
   int row, col;
   printf("Enter Row and Columns of  Matrix: ");
   scanf("%d %d", &row, &col);
   int arr[row][col];
   arrin(row, col, arr);

   printf("\nInput Matrix:\n");
   prtarr(row, col, arr);
   printf("\nChecking if Identity....\n");
   int flag = isMatI(row, col, arr);
   if (flag == 1)
      printf("\nYes, The Matrix is Identity Matrix\n");
   else if (flag == 0)
      printf("\nNo,The Matrix is NOT Identity Matrix\n");
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

int isMatI(int row, int col, int arr[row][col]) {
   if (row == col) {
      for (int i = 0; i < row; i++) {
         for (int j = 0; j < row; j++) {
            if (i == j && arr[i][j] != 1)
               return 0;
            else if (i != j && arr[i][j] != 0)
               return 0;
         }
      }
      return 1;
   } else
      return 0;
}

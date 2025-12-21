#include <stdio.h>

int main() {
   int r, c;
   printf("Please Enter number of rows and column of matrics: ");
   scanf(" %d %d", &r, &c);
   int mat[r][c];
   for (int i = 0; i < r; i++) {
      printf("Enter row %d: ", i + 1);
      for (int j = 0; j < c; j++) {
         scanf(" %d", &mat[i][j]);
      }
   }
   printf("\nEntered Matrix\n");
   for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
         printf("%0.2d ", mat[i][j]);
      }
      printf("\n");
   }
   int n, x, y, flag = 0;
   printf("\nEnter a numbern to find neighbours: ");
   scanf(" %d", &n);
   for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
         if (mat[i][j] == n) {
            flag = 1;
            x = i;
            y = j;
            break;
         }
      }
   }
   if (flag == 0) {
      printf("Number Not found in Matrix\n\n");
   } else {
      int arr[8], e = 0;
      if (y - 1 >= 0) {
         arr[e++] = mat[x][y - 1];
      }
      if (x - 1 >= 0 && y - 1 >= 0) {
         arr[e++] = mat[x - 1][y - 1];
      }
      if (x - 1 >= 0) {
         arr[e++] = mat[x - 1][y];
      }
      if (x - 1 >= 0 && y + 1 < c) {
         arr[e++] = mat[x - 1][y + 1];
      }
      if (y + 1 < c) {
         arr[e++] = mat[x][x + 1];
      }
      if (x + 1 < r && y + 1 < c) {
         arr[e++] = mat[x + 1][y + 1];
      }
      if (x + 1 < r) {
         arr[e++] = mat[x + 1][y];
      }
      if (x + 1 < r && y - 1 >= 0) {
         arr[e++] = mat[x + 1][y - 1];
      }
      for (int i = 0; i < e; i++) {
         for (int j = i + 1; j < e; j++) {
            if (arr[i] > arr[j]) {
               int temp = arr[i];
               arr[i] = arr[j];
               arr[j] = temp;
            }
         }
      }
      printf("\nNeighbours of %d are : ", n);
      for (int i = 0; i < e; i++) {
         printf("%d ", arr[i]);
      }
      printf("\n\n");
   }

   return 0;
}
#include <stdio.h>
#define N 5

void path(int mat[N][N], int sum[N][N], int r, int c);

int main() {

   int mat[N][N] = {{1, 3, 5, 2, 7}, {5, 2, 4, 9, 0}, {2, 6, 3, 1, 9}, {3, 3, 1, 0, 5}, {1, 1, 3, 1, 4}};
   // 1 3 5 2 7   01 04 09 11 18
   // 5 2 4 9 0   06 06 10 19 18
   // 2 6 3 1 9   08 12 13 14 23
   // 3 3 1 0 5   11 14 14 14 19
   // 1 1 3 1 4   12 13 16 15 19  

   int matsum[N][N];
   matsum[0][0] = mat[0][0];
   for (int i = 1; i < N; i++) {
      matsum[i][0] = matsum[i - 1][0] + mat[i][0];
      matsum[0][i] = matsum[0][i - 1] + mat[0][i];
   }

   for (int i = 1; i < N; i++) {
      for (int j = 1; j < N; j++) {
         matsum[i][j] = mat[i][j] + (matsum[i - 1][j] < matsum[i][j - 1] ? matsum[i - 1][j] : matsum[i][j - 1]);
      }
   }

   printf("\nPath Followed\n");
   path(mat, matsum, N - 1, N - 1);
   printf("\nSum of element of shortest path: %d", matsum[N - 1][N - 1]);
   printf("\n\nInput Matrix\n");
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         printf(" %0.2d ", mat[i][j]);
      }
      printf("\n");
   }
   printf("\n");
   return 0;
}

void path(int mat[N][N], int sum[N][N], int r, int c) {
   if (r == 0 && c == 0) {
      printf("[%d,%d]:%d", r, c, mat[r][c]);
      return;
   } else if (r == 0)
      path(mat, sum, r, c - 1);
   else if (c == 0)
      path(mat, sum, r - 1, c);
   else if (sum[r - 1][c] < sum[r][c - 1])
      path(mat, sum, r - 1, c);
   else
      path(mat, sum, r, c - 1);
   printf(" -> [%d,%d]:%d", r, c, mat[r][c]);
}
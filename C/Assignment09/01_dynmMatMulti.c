// Write a function for matrix multiplication which takes
// two matrices as parameter and returns the resultant matrix.
// Dynamically allocate memory for all matrices.

#include <stdio.h>
#include <stdlib.h>

void mtrxIn(int row, int col, int **mat);
void mtrxPrt(int row, int col, int **mat);
int **alloc(int row, int col);
void matMulti(int ra, int ca, int rb, int cb, int **matA, int **matB);
void del(int row, int ***mat);

int main() {
   // Input size of Matrix A
   int ra, ca, rb, cb, **matA, **matB, **mat;

   printf("Enter the Size of Matrix A: ");
   scanf("%d %d", &ra, &ca);
   matA = alloc(ra, ca);

   printf("\nEnter the Values of Matrix A\n");
   mtrxIn(ra, ca, matA);
   printf("\n [ Matrix A ]\n\n");
   mtrxPrt(ra, ca, matA);

   // Input size of Matrix B
   printf("\nEnter the Size of Matrix B: ");
   scanf("%d %d", &rb, &cb);
   matB = alloc(rb, cb);

   printf("\nEnter the Values of Matrix B\n");
   mtrxIn(rb, cb, matB);
   printf("\n [ Matrix B ]\n\n");
   mtrxPrt(rb, cb, matB);

   matMulti(ra, ca, rb, cb, matA, matB);

   del(ra, &matA);
   del(rb, &matB);

   return 0;
}

int **alloc(int row, int col) {
   int **mat = (int **)malloc(row * sizeof(int *));
   if (mat == NULL)
      printf("\nERROR: Failed to allocate Memory\n");
   else
      printf("\nSUCCESS: Memory allocated to Column\nBase address: %u\n\n", mat);
   for (int i = 0; i < row; i++) {
      *(mat + i) = (int *)malloc(col * sizeof(int));
      if (*(mat + i) == NULL)
         printf("ERROR: Failed to allocate Memory\n");
      else
         printf("Address of Row[%d]: %u\n", i + 1, *(mat + i));
   }
   return mat;
}

void del(int row, int ***mat) {
   for (int i = 0; i < row; i++) {
      free(*(*mat + i));
   }
   free(*mat);
}

void matMulti(int ra, int ca, int rb, int cb, int **matA, int **matB) {
   if (ca == rb) {
      int **prod;
      prod = alloc(ra, cb);
      for (int i = 0; i < ra; i++) {    // 0 1
         for (int j = 0; j < cb; j++) { // 0 1 2 3
            int sum = 0;
            for (int k = 0; k < ca; k++) {
               sum = sum + (*(*(matA + i) + k)) * (*(*(matB + k) + j));
            }
            *(*(prod + i) + j) = sum;
         }
      }
      printf("\n [ Matrix A x B ]\n\n");
      mtrxPrt(ra, cb, prod);
      del(ra, &prod);
   } else {
      printf("\nERROR: Column of Matrix A not equal to Row of Matrix B\n\n ");
   }
}

void mtrxIn(int row, int col, int **mat) {
   for (int i = 0; i < row; i++) {
      printf("Row[%d]: ", i + 1);
      for (int j = 0; j < col; j++) {
         scanf("%d", *(mat + i) + j);
      }
   }
}

void mtrxPrt(int row, int col, int **mat) {

   for (int i = 0; i < row; i++) {
      printf(" | ");
      for (int j = 0; j < col; j++) {
         printf("%02d ", *(*(mat + i) + j));
      }
      printf(" |\n");
   }
}
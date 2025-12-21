#include <stdio.h>
int main() {
   int n, i, j;
   printf("Please Enter a number N: ");
   scanf("%d", &n);
   printf("\n\n");
   for (i = n; i >= 1; i--) {
      for (j = 1; j <= i; j++) {
         printf("%d ", j);
      }
      printf("\n");
   }
   return 0;
}
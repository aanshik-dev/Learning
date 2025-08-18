#include <stdio.h>
int main() {
   int n, i, k, l, j;
   printf("Please Enter a number N: ");
   scanf("%d", &n);
   printf("\n\n");

   for (i = 1; i <= n; i++) {
      if (i == 1 || i == n) {
         for (j = 1; j <= n; j++) {
            printf("*");
         }
      } else {
         for (k = 1; k <= n; k++) {
            if (k == 1 || k == n) {
               printf("*");
            } else {
               printf(" ");
            }
         }
      }
      printf("\n");
   }
   return 0;
}
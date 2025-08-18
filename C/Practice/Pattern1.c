/*
*****
   *
  *
 *
*****

*/

#include <stdio.h>
int main() {
   int n, i, j, k;
   printf("Please Enter a Number: ");
   scanf("%d", &n);
   printf("\n\n");

   for (i = 1; i <= n; i++) {
      if (i == 1 || i == n) {
         for (j = 1; j <= n; j++)
            printf("*");
         printf("\n");
      } else {
         for (k = 0; k < n - i; k++) {
            printf(" ");
         }
         printf("*");
         printf("\n");
      }
   }

   return 0;
}
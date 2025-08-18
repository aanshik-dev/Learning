#include <stdio.h>
int main() {
   int n, i, j;
   printf("Please Enter a number N: ");
   scanf("%d", &n);
   printf("\n\n");

   for (i = 1; i <= n; i++) {
      for (j = 1; j <= n - i; j++) {
         printf(" ");
      }
      for (int k = 1; k <= i; k++) {
         printf("%%");
      }
      printf("\n");
   }
   return 0;
}
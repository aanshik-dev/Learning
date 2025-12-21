#include <stdio.h>
int main() {
   int n, i;
   printf("Please Enter a number N: ");
   scanf("%d", &n);

   for (i = 1; i <= n; i++) {
      printf("#\n");
   }
   return 0;
}
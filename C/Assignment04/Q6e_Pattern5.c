#include <stdio.h>

int main() {
   int n;
   printf("Please Enter a Number: ");
   scanf("%d", &n);
   printf("\n\n");
   for (int i = 1; i <= n; i++) {

      for (int j = n - i; j > 0; j--)
         printf(" ");
      for (int j = 1; j <= 2 * i - 1; j++) {

         if (j % 2 != 0)
            printf("*");
         else if (j % 2 == 0)
            printf(" ");
      }
      printf("\n");
   }
   return 0;
}

/*
 *
 * *
 * * *
 * * * *
 */
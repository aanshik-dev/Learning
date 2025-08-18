#include <stdio.h>
int main() {
   int n, c = 0, i, j;
   printf("Please Enter a number N: ");
   scanf("%d", &n);

   for (i = 1; i <= n; i++) {
      for (j = 1; j <= i; j++) {
         if (c == 9) {
            c = 0;
         } else {
            c++;
         }
         printf("%d", c);
      }
      printf("\n");
   }
   return 0;
}

/*
1
23
456
7890
12345 */
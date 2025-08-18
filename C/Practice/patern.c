#include <stdio.h>
int main() {
   int a = 0, b = 1, i = 1, j = 1, n;
   printf("Enter N: ");
   scanf("%d", &n);
   for (int i = 1; i <= n; i++) {
      a = i % 2;
      for (int j = 1; j <= i; j++) {
         if (a == 0) {
            printf("%d ", a);
            a = 1;
         } else if (a == 1) {
            printf("%d ", a);
            a = 0;
         }
      }
      printf("\n");
      j = 1;
   }
}
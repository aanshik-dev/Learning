#include <stdio.h>
int main() {
   int a, b, i, j, s = 0;
   printf("Please enter the Lower limit: ");
   scanf("%d", &a);
   printf("Please enter the Upper limit: ");
   scanf("%d", &b);

   for (i = a; i <= b; i++) {
      for (j = 2; i == 1 || j < i; j++) {
         if (i % j == 0 || i == 1) {
            s = 1;
            break;
         }
      }

      if (s == 0) {
         printf("%d\n", i);
      }
      s = 0;
   }
   return 0;
}

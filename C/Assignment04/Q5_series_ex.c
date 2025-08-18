#include <math.h>
#include <stdio.h>

int main() {
   int n, i, j;
   float x, s = 1;
   printf("Please enter number of terms: ");
   scanf("%d", &n);
   printf("Please enter variable value: ");
   scanf("%f", &x);

   for (i = 1; i < n; i++) {
      int f = 1;
      for (j = 1; j <= i; j++) {
         f = f * j;
      }
      s = s + pow(x, i) / f;
   }
   printf("The Resultant is %0.2f", s);

   return 0;
}

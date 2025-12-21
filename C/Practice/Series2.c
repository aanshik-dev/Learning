#include <stdio.h>
int main() {
   int n, i, o, s = 0;
   float a, sum = 0;
   printf("Please enter a number n: ");
   scanf("%d", &n);
   printf("Please enter a number a: ");
   scanf("%f", &a);
   printf("%f", a);
   for (i = 1; i <= n; i = i++) {
      o = (2 * i) - 1;
      if (s == 0) {
         sum = sum + a / o;
         s = 1;
         printf("%d/%d -", a, o);
      } else if (s == 1) {
         sum = sum - a / o;
         s = 0;
         printf("%d/%d +", a, i);
      }
   }
}
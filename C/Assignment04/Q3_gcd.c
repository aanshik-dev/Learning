#include <stdio.h>
int main() {
   int n, m, i, d;
   printf("Please enter first number: ");
   scanf("%d", &n);
   printf("Please enter second number: ");
   scanf("%d", &m);

   for (i = 1; i <= n; i++) {
      if (n % i == 0 && m % i == 0)
         d = i;
   }

   printf("The GCD of %d and %d is: %d", n, m, d);
   return 0;
}

#include <stdio.h>

int fact(int);

int fact(int a) {
   int p = 1;
   for (int j = 1; j <= a; j++) {
      p = p * j;
   }
   return p;
}

int main() {

   int n, i;
   float sum = 1;
   printf("Please Enter Number of Terms: ");
   scanf("%d", &n);
   for (i = 1; i < n; i++) {
      sum = sum + 1.0 / fact(2 * i);
   }
   printf("The Sum of %d terms is: %0.4f", n, sum);

   return 0;
}
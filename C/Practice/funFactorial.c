#include <stdio.h>

int fact(int); // Prototype

int main() {
   int n, k;
   printf("Please Enter a Number: ");
   scanf("%d", &n);
   k = fact(n);
   printf("The Factorial is %d", k);
}

int fact(int a) {
   int fac = 1, i;
   for (i = a; i > 0; i--) {
      fac = fac * i;
   }
   return fac;
}
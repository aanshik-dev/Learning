// Write a recursive function in C to
// find x^n, where x is a real value,
// and n is a positive integer.

#include <stdio.h>
int expo(int, int);

int main() {
   int b, e;
   printf("Enter a real number: ");
   scanf("%d", &b);
   printf("Enter positive power: ");
   scanf("%d", &e);
   if (e >= 0)
      printf("\n %d^%d is %d\n", b, e, expo(b, e));
   else
      printf("\n Please enter positive power.\n");
   return 0;
}

int expo(int base, int pow) {
   if (pow > 0)
      return base * expo(base, pow - 1);
   return 1;
}

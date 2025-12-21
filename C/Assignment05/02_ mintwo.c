// Write a function in C to find the
// minimum of two numbers.
#include <stdio.h>

void min(int a, int b);
void min(int a, int b) {
   if (a < b)
      printf("\n\t%d is smaller in %d and %d\n", a, a, b);
   else if (a > b)
      printf("\n\t%d is smaller in %d and %d\n", b, a, b);
   else
      printf("\n\tBoth numbers are equal to %d\n", a);
}

int main() {
   int a, b;
   printf("Enter first number : ");
   scanf("%d", &a);
   printf("Enter Second number : ");
   scanf("%d", &b);
   min(a, b);
   return 0;
}
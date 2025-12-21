// Write a function in C to print all
// Strong numbers inside a given range
// [a, b]. You need to pass a and b as
// parameters to the function.
// Hint: Sum of Factorial of digits = Strong Number
#include <stdio.h>

int fact(int);
void stgprt(int, int);

int main() {
   int a, b;
   printf("Enter Lower Limit: ");
   scanf("%d", &a);
   printf("Enter Upper Limit: ");
   scanf("%d", &b);
   printf("\n");

   stgprt(a, b);

   return 0;
}

int fact(int num) {
   if (num > 1) {
      return num * fact(num - 1);
   } else if (num >= 0) {
      return 1;
   }
}

void stgprt(int a, int b) {
   for (int i = a; i <= b; i++) {
      int sum = 0, num = i;
      while (num != 0) {
         sum = sum + fact(num % 10);
         num = num / 10;
      }
      if (sum == i)
         printf("%d\n", i);
   }
}
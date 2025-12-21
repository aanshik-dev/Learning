// Write a function in C to check whether
// a number is Armstrong or not. If it is
// an Armstrong number, the function
// should return 1. Otherwise, it should
// return 0. Write the main function and
// call the function from the main
// function. You need to define the
// function after the main function and
// declare the function outside (before)

// the main function.
#include <stdio.h>

int isArmstg(int a);

int main() {

   int n;
   printf("Enter a number : ");
   scanf("%d", &n);

   int isAstg = isArmstg(n);
   if (isAstg == 1)
      printf("%d is an Armstrong Number", n);
   else
      printf("%d is not an Armstrong Number", n);
   return 0;
}

int isArmstg(int n) {
   int num = n, sum = 0, digit = 0;
   while (num != 0) {
      digit++;
      num = num / 10;
   }
   num = n;
   while (num != 0) {
      int pow = digit, prod = 1;
      while (pow != 0) {
         prod = prod * (num % 10);
         pow--;
      }
      sum = sum + prod;
      num = num / 10;
   }
   if (n == sum)
      return 1;
   else
      return 0;
}
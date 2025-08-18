// Write a function in C to check
// whether a number is prime or not.
// If it is a prime number, the function
// should return 1. Otherwise, it should
// return 0. Write the main function and
// call the function from the main
// function. You need to define the
// function after the main function
// and declare the function inside
// the main function.
#include <stdio.h>

int main() {

   int isPrime(int a);

   int n;
   printf("Enter a number : ");
   scanf("%d", &n);
   int isp = isPrime(n);
   if (isp == 1)
      printf("%d is Prime", n);
   else
      printf("%d is not Prime", n);
   return 0;
}

int isPrime(int n) {
   int flag = 1;
   if (n > 1) {
      if (n != 2)
         for (int i = 2; i < n / 2; i++) {
            if (n % i == 0) {
               flag = 0;
               break;
            }
         }
      return flag;
   } else
      return 0;
}
// Write a function in C that takes a real

// number as an argument and returns that
// number’s absolute value.

#include <stdio.h>
int mod(int);
int main() {
   int a;
   printf("Enter a Number : ");
   scanf("%d", &a);
   printf("Absolute Value of %d is %d", a, mod(a));
   return 0;
}

int mod(int real) {
   if (real >= 0)
      return real;
   else
      return -1 * real;
}
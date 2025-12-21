// Write a recursive function in C to
// find the factorial of a positive
// integer.

#include <stdio.h>
int fact(int);

int main() {
   int a;
   printf("Enter a Number : ");
   scanf("%d", &a);
   if (a >= 0)
      printf("\n %d! = %d\n", a, fact(a));
   return 0;
}

int fact(int num) {
   if (num > 1)
      return num * fact(num - 1);
   else
      return 1;
}

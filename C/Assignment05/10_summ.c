// Write a recursive function in C to find the summation of the first n natural numbers.

#include <stdio.h>
int summ(int);

int main() {
   int a;
   printf("Enter a Natural Number : ");
   scanf("%d", &a);
   if (a > 0)
      printf("\nSummation of first %d natural numbers is = %d\n", a, summ(a));
   return 0;
}

int summ(int num) {
   if (num == 0)
      return 0;
   return num + summ(num - 1);
}
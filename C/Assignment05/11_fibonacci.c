// Write a recursive function in C to
// find the ith number in the Fibonacci
// sequence.
// 1 1 2 3 5 8 13 21

#include <stdio.h>
int fibo(int);

int main() {
  int a;
  printf("Enter a Natural Number : ");
  scanf("%d", &a);
  printf("\n Fibonacci of %d is %d\n", a, fibo(a));
  return 0;
}

int fibo(int num) {
  if (num <= 0)
    return 0;
  if (num > 2)
    return fibo(num - 1) + fibo(num - 2);
  return 1;
}

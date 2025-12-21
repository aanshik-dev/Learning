// Write a function in C to print all
// Perfect numbers inside a given range
// [a, b]. You need to pass a and b as
// parameters to the function.

#include <stdio.h>

void perfect(int, int);

int main() {
   int a, b;
   printf("Enter Lower Limit: ");
   scanf("%d", &a);
   printf("Enter Upper Limit: ");
   scanf("%d", &b);
   printf("\n");
   perfect(a, b);
   return 0;
}

void perfect(int a, int b) {
   for (int i = a; i <= b; i++) {
      int sum = 1;
      for (int j = 2; j < i; j++) {
         if (i % j == 0)
            sum = sum + j;
      }
      if (i != 1 && sum == i)
         printf("%d\n", i);
   }
}
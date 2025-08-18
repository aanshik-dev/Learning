
#include <stdio.h>
int main() {
   int i, n = 8;
   float sum = 0;
   printf("Please enter a Number");
   scanf("%d", &n);
   for (i = 1; i <= n; i++) {
      sum = sum + 1.0 / (i);
      printf(" 1/%d + ", i);
   }
   printf("\n Sum is %f", sum);
}
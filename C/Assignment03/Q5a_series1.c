#include <math.h>
#include <stdio.h>
int main() {
   float n,
       s = 0,
       i = 0;
   printf("Please Enter A Number n: ");
   scanf("%f", &n);
   while (i < n) {
      s = s + (pow(-1, i)) / (2 * i + 1);
      i++;
   }
   printf("The Summation %0.0f terms of Series is %0.2f\n", n, 4 * s);
   return 0;
}
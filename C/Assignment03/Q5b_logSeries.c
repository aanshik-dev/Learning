#include <math.h>
#include <stdio.h>
int main() {
   float n, s = 0, i = 0, x;
   printf("Please Enter number of terms n: ");
   scanf("%f", &n);
   printf("Please Enter value of Variable X: ");
   scanf("%f", &x);

   while (i < n) {
      s = s + (pow(-1, i) * pow(x, i + 1)) / (i + 1);
      i++;
   }
   printf("The Summation %0.0f terms of Series is %0.2f\n", n, s);
   return 0;
}

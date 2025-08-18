#include <math.h>
#include <stdio.h>
int main() {
   int a, b, c;
   float r1, r2, d;
   printf("Please Enter Coefficients\na: ");
   scanf("%d", &a);
   printf("b: ");
   scanf("%d", &b);
   printf("c: ");
   scanf("%d", &c);
   d = b * b - 4 * a * c;

   if (d >= 0.0) {
      d = sqrt(d);
      r1 = (-1 * b + d) / 2 * a;
      r2 = (-1 * b - d) / 2 * a;
      printf("The roots of the equation %dx^2 + %dx + %d are %0.3f and %0.3f.", a, b, c, r1, r2);
   } else {
      printf("The roots of the equation %dx^2 + %dfx + %d does not exist.", a, b, c);
   }
   return 0;
}

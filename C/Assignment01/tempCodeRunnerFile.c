#include <stdio.h>
int main() {
   int r;
   float ar, pi = 3.14;
   printf("Please Enter Radius in m: ");
   scanf("%d", &r);
   ar = pi * r * r;
   printf("Area of circle with radius %dm is %0.2f m^2", r, ar);
   return 0;
}

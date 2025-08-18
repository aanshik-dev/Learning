#include <math.h>
#include <stdio.h>
int main() {
   int a,
       b,
       c;
   float s,
       sq,
       ar;
   printf("Please Enter Sides of triangle: ");
   scanf("%d %d %d", &a, &b, &c);

   if (a + b > c && b + c > a && a + c > b) {
      s = (a + b + c) / 2.0;
      sq = s * (s - a) * (s - b) * (s - c);
      ar = sqrt(sq);
      printf("Area of Triangle is: %0.2f", ar);
   } else {
      printf("Sides of Triangle are invalid");
   }
   return 0;
}
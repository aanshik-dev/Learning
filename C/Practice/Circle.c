#include <stdio.h>

int main() {
   int x = 8, y = 5, r = 4, g = 4, f = 6, a = 0;
   printf("Enter Radius Of Circle: ");
   scanf("%d", &r);
   printf("Enter 'X' Coordinate Of Centre: ");
   scanf("%d", &g);
   printf("Enter 'Y' Coordinate Of Centre: ");
   scanf("%d", &f);
   printf("Enter 'X' Coordinate Of Point: ");
   scanf("%d", &x);
   printf("Enter 'Y' Coordinate Of Point: ");
   scanf("%d", &y);

   a = (x - g) * (x - g) + (y - f) * (y - f) - (r * r);
   if (a > 0) {
      printf("The Given Point [%d,%d] Lies Outside The Circle", x, y);
   } else if (a == 0) {
      printf("The Given Point [%d,%d] Lies On The Circle", x, y);
   } else {
      printf("The Given Point [%d,%d] Lies Inside The Circle", x, y);
   }
}
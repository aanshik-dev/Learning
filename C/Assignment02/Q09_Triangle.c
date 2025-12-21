#include <stdio.h>
int main() {
   int a, b, c;
   printf("Please Enter Sides of triangle\na: ");
   scanf("%d", &a);
   printf("b: ");
   scanf("%d", &b);
   printf("c: ");
   scanf("%d", &c);
   if (a == b && b == c)
      printf("Equilateral Triangle");
   else if (a == b || b == c || c == a)
      printf("Isosceles Triangle");
   else {
      printf("Scalene Triangle");
   }
   return 0;
}

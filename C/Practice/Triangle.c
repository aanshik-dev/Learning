
#include <stdio.h>
int main() {
   int a = 6, b = 6, c = 6;
   printf("Please Enter Sides of triangle ");
   scanf("%d %d %d", &a, &b, &c);
   if (a == b && b == c)
      printf("Equilateral Triangle");
   else if (a == b || b == c || c == a)
      printf("Isosceles Triangle");
   else {
      printf("Scalene Triangle");
   }
}
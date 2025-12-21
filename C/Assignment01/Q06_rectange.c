#include <stdio.h>
int main() {
   int l, b, ar;
   printf("Please Enter Length in m: ");
   scanf("%d", &l);
   printf("Please Enter breadth in m: ");
   scanf("%d", &b);
   ar = l * b;
   printf("The area of rectangle with length %dm and breadth %dm is: %d", l, b, ar);
   return 0;
}

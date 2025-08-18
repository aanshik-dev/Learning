#include <stdio.h>
int main() {
   int a,
       b,
       c;
   printf("Please enter a number a: ");
   scanf("%d", &a);
   printf("Please enter a number b: ");
   scanf("%d", &b);
   printf("Please enter a number c: ");
   scanf("%d", &c);

   if (a < b || a < c) {
      printf("The number %d is smallest", a);
   } else if (b < a || b < c) {
      printf("The number %d is smallest", b);
   } else if (c < a || c < b) {
      printf("The number %d is smallest", c);
   }
   return 0;
}
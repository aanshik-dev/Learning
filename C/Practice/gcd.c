#include <stdio.h>
int gcdfinder(int, int);

int main() {
   int a, b;
   printf("Enter a: ");
   scanf("%d", &a);
   printf("Enter b: ");
   scanf("%d", &b);
   printf("%d", gcdfinder(a, b));
}

int gcdfinder(int a, int b) {
   if (a == 0)
      return b;

   return gcdfinder(b % a, a);
}

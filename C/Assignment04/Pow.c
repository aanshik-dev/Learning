#include <stdio.h>

int power(int, int);

int main() {
   int b, e, res;
   printf("Enter Base: ");
   scanf("%d", &b);
   printf("Enter Power: ");
   scanf("%d", &e);

   res = power(b, e);
   printf("%d", res);
}

int power(int base, int exp) {
   if (exp > 0) {
      return base * power(base, --exp);
   } else {
      return 1;
   }
}
#include <stdio.h>

int bincon(int x) {
   return x == 0 ? 0 : x % 2 + 10 * bincon(x / 2);
}

int main() {
   int n;
   printf("Enter a number: ");
   scanf(" %d", &n);
   printf("Binary of %d is %d\n", n, bincon(n));
   return 0;
}

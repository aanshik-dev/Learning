#include <stdio.h>
int main() {
   int n, i;
   printf("Please Enter A Number: ");
   scanf("%d", &n);
   for (i = 1; i <= 10; i++) {
      printf("%d X %d = %d\n", n, i, n * i);
   }
   return 0;
}

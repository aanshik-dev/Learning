#include <stdio.h>
void toh(int n, char s, char t, char a);

int main() {
   int n;
   printf("Enter n: ");
   scanf("%d", &n);

   toh(n, 'S', 'D', 'A');

   return 0;
}

void toh(int n, char s, char t, char a) {
   if (n > 0) {
      toh(n - 1, s, a, t);
      printf("Move disk %d from %c to %c.\n", n, s, t);
      toh(n - 1, a, t, s);
   }
}

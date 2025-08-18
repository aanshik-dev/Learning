#include <stdio.h>

int main() {
   int n, t = 0, s = 0;
   printf("Please Enter a Number: ");
   scanf("%d", &n);
   printf("\n\n");
   for (int i = 1; i > 0 && i <= n; 1) {
      if (i == n)
         t = 1;
      for (int j = 1; j <= 2 * i - 1; j++) {
         if (s == 0) {
            printf("0");
            s = 1;
         } else if (s == 1) {
            printf("1");
            s = 0;
         }
      }
      printf("\n");

      if (t == 0)
         i++;
      else if (t == 1)
         i--;
   }
   return 0;
}

/*
1
010
10101
0101010
10101
010
1
*/
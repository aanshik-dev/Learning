#include <stdio.h>

void print(int a) {
   int s = 1;
   for (int j = 1; j <= 2 * a - 1; j++) {
      if (s == 0) {
         printf("0");
         s = 1;
      } else if (s == 1) {
         printf("1");
         s = 0;
      }
   }
   printf("\n");
}

int main() {
   int n;
   printf("Please Enter a Number: ");
   scanf("%d", &n);
   printf("\n\n");

   for (int i = 1; i <= n; i++) {
      print(i);
   }
   for (int i = n - 1; i > 0; i--) {
      print(i);
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
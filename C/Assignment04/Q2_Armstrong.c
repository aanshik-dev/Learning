#include <math.h>
#include <stdio.h>
int main() {
   int i;
   for (i = 100; i <= 999; i++) {
      int j = i, s = 0, p, r;
      while (j != 0) {
         r = j % 10;
         p = r * r * r;
         s = s + p;
         j = j / 10;
      }

      if (i == s) {
         printf("%d\n", i);
      }
   }
   return 0;
}

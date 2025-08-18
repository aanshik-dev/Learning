#include <stdio.h>
int main() {
   float x, pro = 1;
   int n, i;
   printf("Please enter base number: ");
   scanf("%f", &x);
   printf("Please enter power: ");
   scanf("%d", &n);

   for (i = 1; i <= n; i++) {
      pro = pro * x;
   }
   printf("The Resultant is %0.2f", pro);

   return 0;
} 

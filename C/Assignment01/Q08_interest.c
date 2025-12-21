#include <math.h>
#include <stdio.h>
int main() {
   int r, p;
   float i, d;
   printf("Please Enter Principal Amount: ");
   scanf("%d", &p);
   printf("Please Enter Rate of Interest in %%: ");
   scanf("%d", &r);

   i = (r / 100.0) * p;
   d = p + i;
   printf("Total Simple Interest: ₹ %0.2f \n", i);
   printf("Total Debt: ₹ %0.2f \n", d);
   return 0;
}
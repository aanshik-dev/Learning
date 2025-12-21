#include <stdio.h>
int main() {
   int m, s = 0;
   printf("Please enter a Month in Number: ");
   scanf("%d", &m);

   if (m == 2)
      s = 1;
   else if (m == 4 || m == 6 || m == 9 || m == 11)
      s = 2;
   else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
      s = 3;

   switch (s) {

   case 1:
      printf("Number Of Days: 28");
      break;
   case 2:
      printf("Number Of Days: 30");
      break;
   case 3:
      printf("Number Of Days: 31");
      break;
   default:
      printf("Invalid Month Number");
   }
   return 0;
}

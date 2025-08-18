#include <stdio.h>
int main() {
   int y;
   printf("Please enter a year: ");
   scanf("%d", &y);
   if ((y % 100 != 0 && y % 4 == 0) || y % 400 == 0)
      printf("Year %d is a Leap Year.", y);
   else
      printf("Year %d is not a Leap Year.", y);
   return 0;
}

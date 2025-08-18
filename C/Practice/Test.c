#include <stdio.h>
int main() {
   int y = 2007;
   printf("Please enter a year");
   scanf("%d", &y) if (y % 100 != 0 && y % 4 == 0)
       printf("Leap Year: %d", y);
   else {
      if (y % 400 == 0)
         printf("Leap Year: %d", y);
      else
         printf("Not A Leap Year: %d", y);
   }
}

#include <stdio.h>
int main() {
   int n = 0;         // try with 0, 1, 5, 7, 10, and 20
   int condition = 1; // try with 0 and 1
   if (n == 5) {
      printf("1\n");
   } else if (n % 2 == 0) {
      if (n == 10 && condition == 1) {
         printf("2\n");
      } else {
         printf("3\n");
      }
      printf("4\n");
   } else if (condition) {
      printf("5\n");
   } else if (0) {
      printf("6\n");
   } else {
      printf("7\n");
   }
   printf("8\n");
   return 0;
}

/*
Output: 0,0(3,4,8)
        1,0(7,8)
        5,0(1,8)
        7,0(7,8)
        10,0(3,4,8)
        20,0(3,4,8)
        0,1( 3,4,8)
        1,1(5,8)
        5,1(1,8)
        7,1(5,8)
        10,1(2,4,8)
        20,1(3,4,8)

*/
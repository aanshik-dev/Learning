// Write a recursive function in C to
// solve Tower of Hanoi problem.

#include <stdio.h>

void toh(int, char, char, char);

int main() {
   int num;
   printf("Enter Number of Tiles: ");
   scanf("%d", &num);
   printf("\n");
   toh(num, 'A', 'C', 'B');

   return 0;
}

void toh(int n, char src, char des, char aux) {
   if (n > 0) {
      toh(n - 1, src, aux, des);
      printf(" Move Tile %d from %c to %c\n", n, src, des);
      toh(n - 1, aux, des, src);
   }
}

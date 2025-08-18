#include <stdio.h>
int main() {
   int a = 4, b = 6, c = 7, d = 6, e = 4;
   float sum = 0, avg = 0;
   sum = a + b + c + d + e;
   avg = sum / 5;
   printf("Average is: %.2f\n", avg);
   return 0;
}
// Write a program in C to print the
// addresses of all elements in an array.
// Try for int, char and double arrays.
// Print the elements using pointer.

#include <stdio.h>

int main() {

   int arrz[] = {0, 1, 2, 3, 4};
   char arrc[] = {'a', 'b', '@', 't'};
   double arrd[] = {7.0, 8.0, 9, 0, 1.0};

   for (int i = 0; i < sizeof(arrz) / sizeof(int); i++) {
      int *z = &arrz[i];
      printf("%.2d. Address of Element: %u and Value of Element: %d \n", i + 1, z, *z);
   }
   printf("\n\n");
   for (int i = 0; i < sizeof(arrc) / sizeof(char); i++) {
      char *c = &arrc[i];
      printf("%.2d. Address of Element: %u and Value of Element: %c \n", i + 1, c, *c);
   }
   printf("\n\n");
   for (int i = 0; i < sizeof(arrd) / sizeof(double); i++) {
      double *d = &arrd[i];
      printf("%.2d. Address of Element: %u and Value of Element: %.4lf \n", i + 1, d, *d);
   }
   return 0;
}

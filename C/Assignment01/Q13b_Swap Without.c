#include <stdio.h>
int main() {
   int a, b;
   printf("The unswaped values of a and b are: a=%d|b=%d \n", a, b);
   a = b - a;
   b = b - a;
   a = a + b;
   printf("The swaped values of a and b are: a=%d|b=%d", a, b);
   return 0;
}

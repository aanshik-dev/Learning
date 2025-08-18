#include <stdio.h>
int main() {
   int a, b, c;
   printf("The unswaped values of a and b are: a=%d|b=%d \n", a, b);
   c = a;
   a = b;
   b = c;
   printf("The swaped values of a and b are: a=%d|b=%d", a, b);
   return 0;
}

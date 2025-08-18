#include <stdio.h>
int main() {
   float f, c;
   printf("Please Enter Temperature in Fahreheit: ");
   scanf("%f", &f);

   c = (f - 32) * 5 / 9;
   printf("Temperature in Celcius: %0.2f", c);
   return 0;
}
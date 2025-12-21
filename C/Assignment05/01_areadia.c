// Write a function in C to compute the
// area of a circle. You need to pass the
// diameter of the circle as a parameter
// to the function. Write the main
// function and call it from the main
// function. You need to define the
// function before the main function.
#include <stdio.h>
#define pi 3.1415

void area(int dia);
void area(int dia) {
   float area = pi * (dia / 2.0) * (dia / 2.0);
   // printf("Area : %.4f cm^2", area);
}

int main() {
   int d;
   // printf("Enter Diameter in cm : ");
   scanf("%d", &d);
   area(d);
   return 0;
}
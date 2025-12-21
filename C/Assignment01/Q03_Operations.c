#include <stdio.h>
int main() {
   int a = 7,
       b = 5,
       c = 0,
       d = 5,
       result = 0;
   result = a + b;
   printf("Sum Is: %d\n", result);
   result = a - b;
   printf("Difference Is: %d\n", result);
   result = a / b;
   printf("Quotient Is: %d\n", result);
   result = a * b;
   printf("Product Is: %d\n", result);
   result = a % b;
   printf("Remainder Is: %d\n", result);
   result++;
   printf("Post Increment Is: %d\n", result);
   result--;
   printf("Post Decrement Is: %d\n", result);
   ++result;
   printf("Pre Increment Is: %d\n", result);
   result = (a < b);
   printf("If a<b Is: %d\n", result);
   result = (a <= b);
   printf("If a<=b Is: %d\n", result);
   result = (d > b);
   printf("If d>b Is: %d\n", result);
   result = (d >= b);
   printf("If d>=b Is: %d\n", result);
   return 0;
}
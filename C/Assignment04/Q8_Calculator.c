#include <stdio.h>
int main() {
   float n,
       m;
   char o;
   printf("Please enter Operation to be performed\nValid Operations + - * /\nEnter In order (Num1)_(Operator)_(Num2)\n\n   :  ");
   scanf("%f %c %f", &n, &o, &m);

   switch (o) {

   case '+':
      printf("Addition: %0.2f + %0.2f = %0.2f", n, m, n + m);
      break;
   case '-':
      printf("Subtraction: %0.2f - %0.2f = %0.2f", n, m, n - m);
      break;
   case '*':
      printf("Multiplication: %0.2f × %0.2f = %0.2f", n, m, n * m);
      break;
   case '/':
      if (m == 0)
         printf("Division: %0.2f ÷ %0.2f = Not Defined", n, m);
      else
         printf("Division: %0.2f ÷ %0.2f = %0.2f", n, m, n / m);
      break;
   default:
      printf("This Operation Is Invalid");
   }
   return 0;
}
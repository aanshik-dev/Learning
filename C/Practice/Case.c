#include <stdio.h>
int main() {

   int o = 0, a, b;
   printf("Please Choose an Operation from: \n 1. Addition\n 2. Subtraction\n 3. Multiplication\n 4. Division \n");
   scanf("%d", &o);
   switch (o) {
   case 1:
      printf("please enter 2 Numbers to add \n");
      scanf("%d %d", &a, &b);
      printf("The Sum of 2 Numbers is %d \n", a + b);
      break;

   case 2:
      printf("please enter 2 Numbers to subtract \n");
      scanf("%d %d", &a, &b);
      printf("The difference of 2 Numbers is %d \n", a - b);
      break;

   case 3:
      printf("please enter 2 Numbers to Multiply\n");
      scanf("%d %d", &a, &b);
      printf("The product of 2 Numbers is %d \n", a * b);
      break;

   case 4:
      printf("please enter 2 Numbers to divide \n");
      scanf("%d %d", &a, &b);
      printf("The Quotient of 2 Numbers is %d \n", a / b);
      break;

   default:
      printf("This Operation is Invalid");
   }
}
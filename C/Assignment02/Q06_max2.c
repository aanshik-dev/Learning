#include <stdio.h>
int main() {
   int n, m;
   printf("Please enter a number: ");
   scanf("%d", &n);
   printf("Please enter another number to compare: ");
   scanf("%d", &m);
   if (n > m)
      printf("The number %d is greater than %d", n, m);
   else if (n < m)
      printf("The number %d is greater than %d", m, n);
   else
      printf("Both numbers are equal and value is %d", n);
   return 0;
}

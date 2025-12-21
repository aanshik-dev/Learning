#include <stdio.h>
int reverse(int, int);
int reverse(int num, int rev) {
   rev = rev * 10 + num % 10;
   if (num / 10 == 0)
      return rev;
   return reverse(num / 10, rev);
}

int main() {
   int num;
   printf("Enter a Number: ");
   scanf("%d", &num);
   printf("Reversed Num: %d", reverse(num, 0));
   return 0;
}

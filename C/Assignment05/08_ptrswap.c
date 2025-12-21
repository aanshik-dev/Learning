// write a function in C that takes two
// pointers to integers and swaps the
// variables

#include <stdio.h>

int swap(int *, int *);

int main() {
   int a, b;
   printf("Enter a Number : ");
   scanf("%d", &a);
   printf("Enter another Number : ");
   scanf("%d", &b);
   printf("\nBefore Swaping:\n%d  %d\n", a, b);
   swap(&a, &b);
   printf("\nAfter  Swaping:\n%d  %d\n", a, b);
   return 0;
}

int swap(int *a, int *b) {
   int i = *b;
   *b = *a;
   *a = i;
}

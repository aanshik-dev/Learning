#include <stdio.h>

union U {
   char c;
   float f;
};

struct P {
   char ch;
   union U u;
};

struct S {
   int num;
   struct P p;
};

int main() {

   struct S s;

   printf("Enter an integer for struct S: ");
   scanf("%d", &s.num);

   printf("Enter a character for struct P: ");
   scanf(" %c", &s.p.ch);

   printf("Enter a character for union U: ");
   scanf(" %c", &s.p.u.c);

   printf("Enter a float for union U: ");
   scanf("%f", &s.p.u.f);

   printf("\nValues are accessed from struct P:\n");
   printf("Integer: %d\n", s.num);
   printf("Character (ch in P): %c\n", s.p.ch);
   printf("Character (c in U): %c\n", s.p.u.c);
   printf("Float (f in U): %.2f\n", s.p.u.f);

   return 0;
}

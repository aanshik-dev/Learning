#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf pos;

void C(int x) {
  if (x == 0) {
    printf("Division by zero\n");
    longjmp(pos, 1);
  }
  printf("Result: %d\n", x);
}

void B(int x) {
  C(x);
}

void A(int x) {
  B(x);
}

int main(int argc, char *argv[]) {
  int val = atoi(argv[1]);
  int jump = setjmp(pos);
  if (jump == 0) {
    A(val);
    printf("Executed normally.\n");
  } else {
    printf("Returned to main\n");
  }

  return 0;
}

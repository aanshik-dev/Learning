#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

jmp_buf pos;

void handler(int sig) {
  longjmp(pos, 1);
}

int main() {
  char name[100];
  int n;
  int jump = setjmp(pos);
  if (jump != 0) {
    write(1, "Timeout!\n", 9);
    return 0;
  }

  signal(SIGALRM, handler);

  write(1, "Enter your name: ", 17);
  alarm(10);
  n = read(0, name, sizeof(name));
  alarm(0);

  if (n > 0) {
    write(1, "Hello, ", 7);
    write(1, name, n);
  }
  return 0;
}

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarm_handler(int sig) {
  printf("\nKilling Self Process\n");
  kill(getpid(), SIGKILL);
}

int main() {
  printf("My PID is: %d\n", getpid());
  signal(SIGALRM, alarm_handler);
  alarm(5);
  pause();

  return 0;
}

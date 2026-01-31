#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid1 = fork();
  if (pid1 == 0) {
    printf("Child 1 (PID: %d)\n", getpid());
    printf("Child 1 finished.\n");
  } else if (pid1 > 0) {
    pid_t pid2 = fork();
    if (pid2 == 0) {
      printf("Child 2 (PID: %d)\n", getpid());
      printf("Child 2 finished.\n");
    } else if (pid2 > 0) {
      wait(NULL);
      wait(NULL);
      printf("Parent (PID: %d)\n", getpid());
      printf("Both children finished.\n");
    }
  }
  return 0;
}
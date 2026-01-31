#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    printf("Child process (PID: %d)\n", getpid());
    execlp("./q2_data", "q2_data", NULL);
    printf("execlp failed");
    exit(1);
  } else if (pid > 0) {
    printf("Parent process (PID: %d)\n", getpid());
    wait(NULL);
    printf("Child finished.\n");
  } else {
    perror("Fork failed");
    exit(1);
  }

  return 0;
}

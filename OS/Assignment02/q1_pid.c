#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid == 0) {
    printf("Child: Fork: %d\n", pid);
    printf("Child: PID: %d\n", getpid());
    printf("Child: Parent PPID: %d\n", getppid());
  } else if (pid > 0) {
    wait(NULL);
    printf("Parent: Fork: %d\n", pid);
    printf("Parent: PID: %d\n", getpid());
    printf("Parent: Parent PPID: %d\n", getppid());
  } else {
    perror("Fork failed");
  }
  return 0;
}

//  [GrandParent] PID 564
//      ^
//      |
//  [Parent] PID 647 Fork: 648
//     ^
//     |
//  [Child] PID 648  Fork: 0
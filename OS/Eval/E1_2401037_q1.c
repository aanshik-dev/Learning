#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int fd[2];
pid_t pid;

void alarm_handler(int sig) {
  printf("\nPerent: Child is Killed !! Respawn\n");
  kill(pid, SIGKILL);
  wait(NULL);
}

int main() {
  pipe(fd);
  signal(SIGALRM, alarm_handler);

  pid = fork();

  if (pid < 0) {
    printf("Error Creating Child !!");
    return -1;
  }

  if (pid == 0) {
    close(fd[0]); // close read
    int stuck = 1;

    while (1) {
      printf("Child: I am Alive and working !!\n");
      if (!(stuck % 5 == 0)) {
        write(fd[1], "Alive", 5);
      } else {
        sleep(5);
      }
      stuck++;
      sleep(1);
    }
  } else if (pid > 0) {

    close(fd[1]); // Write Close
    char msg[50];
    while (1) {
      alarm(3);
      int msgSize = read(fd[0], msg, sizeof(msg));
      if (msgSize > 0) {
        printf("Parent: Child Alive !!\n");
        alarm(0);
      } else {
        printf("Parent: Message not recieved !!\n");
        pid = fork();
        if (pid == 0) {
          close(fd[0]); // close write
          int stuck = 1;

          while (1) {
            printf("Child: I am Alive and working !!\n");
            if (!(stuck % 5 == 0)) {
              write(fd[1], "Alive", 5);
            } else {
              sleep(5);
            }

            stuck++;
            sleep(1);
          }
        }
      }
    }
  }

  return 0;
}

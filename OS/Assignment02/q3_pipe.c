#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char buffer[100];
  int pipeline[2];
  if (pipe(pipeline) == -1) {
    perror("pipe failed");
    return 1;
  }
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork failed");
    return 1;
  }
  if (pid == 0) {
    close(pipeline[1]);
    read(pipeline[0], buffer, sizeof(buffer));
    printf("%s\nChild: Are Babuji Ram Ram ! Tu dada ban gail badu !!\n", buffer);
    close(pipeline[0]);
  } else if (pid > 0) {
    close(pipeline[0]);
    char message[] = "Parent: Hello ham tuhar babuji bolat raha !!";
    write(pipeline[1], message, strlen(message) + 1);
    close(pipeline[1]);
  }
  return 0;
}
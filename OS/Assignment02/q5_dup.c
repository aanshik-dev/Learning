#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {

  int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
    perror("Error opening file");
    return 1;
  }
  int dup_fd = dup(fd);
  if (dup_fd < 0) {
    perror("Error duplicating file descriptor");
    return 1;
  }
  dup2(dup_fd, STDOUT_FILENO);
  printf("This will be written to the file.\n");
  close(fd);
  close(dup_fd);

  return 0;
}

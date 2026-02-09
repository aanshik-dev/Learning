#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_FILES 20
#define BUFFER_SIZE 1024

int count_occurrences(const char *filename, const char *keyword) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("File open failed");
    return 0;
  }

  char buffer[BUFFER_SIZE];
  int count = 0;
  int keylen = strlen(keyword);

  while (fgets(buffer, BUFFER_SIZE, fp)) {
    char *pos = buffer;
    while ((pos = strstr(pos, keyword)) != NULL) {
      count++;
      pos += keylen;
    }
  }

  fclose(fp);
  return count;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <keyword> <file1> <file2> ...\n", argv[0]);
    exit(1);
  }

  char *keyword = argv[1];
  int num_files = argc - 2;

  int pipes[MAX_FILES][2];
  pid_t pid;
  int total_count = 0;

  for (int i = 0; i < num_files; i++) {
    pipe(pipes[i]);

    pid = fork();

    if (pid == 0) {
      /* -------- CHILD PROCESS -------- */
      close(pipes[i][0]); // Close read end

      int count = count_occurrences(argv[i + 2], keyword);
      write(pipes[i][1], &count, sizeof(int));

      close(pipes[i][1]);
      exit(0);
    } else {
      /* -------- PARENT PROCESS -------- */
      close(pipes[i][1]); // Close write end
    }
  }

  /* Parent waits and collects results */
  for (int i = 0; i < num_files; i++) {
    int child_count;
    wait(NULL);
    read(pipes[i][0], &child_count, sizeof(int));
    total_count += child_count;
    close(pipes[i][0]);
  }

  printf("\nTotal occurrences of \"%s\": %d\n", keyword, total_count);

  return 0;
}

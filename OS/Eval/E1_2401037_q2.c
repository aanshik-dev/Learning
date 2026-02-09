#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int st;
  int end;
  int count;
} tStruct;

char keyword[] = "massive";
int th = 4;
int numLines = 0;
char lines[1000][200];

void *findWord(void *arg) {
  tStruct *thData = (tStruct *)arg;
  int words = 0;
  for (int i = thData->st; i < thData->end; i++) {
    if (strstr(lines[i], keyword) != NULL) {
      words++;
    }
  }
  thData->count = words;
  pthread_exit(NULL);
}

int main() {
  FILE *fd = fopen("text.txt", "r");
  if (fd == NULL) {
    perror("Error Opening File !!");
    return 1;
  }
  while (fgets(lines[numLines], 200, fd)) {
    numLines++;
  }
  pthread_t threads[th];
  tStruct thData[th];
  int part = numLines / th;

  for (int i = 0; i < th; i++) {
    thData[i].st = i * part;
    thData[i].end = (i == th - 1) ? numLines : (i + 1) * part;
    thData[i].count = 0;
    pthread_create(&threads[i], NULL, findWord, &thData[i]);
  }

  // Printing
  int totalWords = 0;
  for (int i = 0; i < th; i++) {
    pthread_join(threads[i], NULL);
    printf("Thread [%d] Words: [%d]\n", i + 1, thData[i].count);
    totalWords += thData[i].count;
  }
  printf("Total Word Count of [%s]: %d\n", keyword, totalWords);

  return 0;
}

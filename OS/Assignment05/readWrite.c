#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

sem_t mutex;
sem_t wmutex;
sem_t wrt;
sem_t readPermit;

int readcount = 0;
int writecount = 0;

void *reader(void *arg) {
  int id = *(int *)arg;
  char str[100];

  while (1) {

    sem_wait(&readPermit);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
      sem_wait(&wrt);
    sem_post(&mutex);

    sem_post(&readPermit);

    int fdr = open("file.txt", O_RDONLY);
    if (fdr != -1) {
      int size = read(fdr, str, 99);
      if (size > 0) {
        str[size] = '\0';
        printf("[Reader %d] Read: %s\n", id, str);
      } else {
        printf("[Reader %d] File is empty.\n", id);
      }
      close(fdr);
    }

    sleep(1);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
      sem_post(&wrt);
    sem_post(&mutex);

    sleep(1);
  }
}

void *writer(void *arg) {
  int id = *(int *)arg;
  char str[100];

  while (1) {

    // printf("[Writer %d] Enter a string: ", id);
    // fflush(stdout);

    // if (fgets(str, sizeof(str), stdin) == NULL)
    //   continue;

    sem_wait(&wmutex);
    writecount++;
    if (writecount == 1)
      sem_wait(&readPermit);
    sem_post(&wmutex);

    sprintf(str, "Hello World Writer ID : %d\n", id);

    sem_wait(&wrt);
    int fdw = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fdw != -1) {
      write(fdw, str, strlen(str));
      printf("[Writer %d] Wrote to file.\n", id);
      close(fdw);
    }
    sem_post(&wrt);

    sem_wait(&wmutex);
    writecount--;
    if (writecount == 0)
      sem_post(&readPermit);
    sem_post(&wmutex);

    sleep(1);
  }
}

int main() {

  if (sem_init(&mutex, 0, 1) ||
      sem_init(&wmutex, 0, 1) ||
      sem_init(&wrt, 0, 1) ||
      sem_init(&readPermit, 0, 1)) {
    printf("ERROR creating the Semaphores !!");
    exit(1);
  }

  pthread_t r[4], w[3];
  int ids[7];

  for (int i = 0; i < 4; i++) {
    ids[i] = i + 1;
    pthread_create(&r[i], NULL, reader, &ids[i]);
  }

  for (int i = 0; i < 3; i++) {
    ids[i + 4] = i + 1;
    pthread_create(&w[i], NULL, writer, &ids[i + 4]);
  }

  for (int i = 0; i < 4; i++)
    pthread_join(r[i], NULL);

  for (int i = 0; i < 3; i++)
    pthread_join(w[i], NULL);

  return 0;
}
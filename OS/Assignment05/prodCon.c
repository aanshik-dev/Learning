#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int arr[10];
sem_t mutex;
sem_t empty;
sem_t full;

void *producer(void *arg) {
  int k = 0;
  while (1) {
    sem_wait(&empty);
    sem_wait(&mutex);
    arr[k] = k + 1;
    printf("Producer: Added [%d]    [ ", arr[k]);
    for (int i = 0; i < 10; i++) {
      printf("%d ", arr[i]);
    }
    k = (k + 1) % 10;
    printf("]\n");
    sem_post(&mutex);
    sem_post(&full);
    sleep(1);
  }
  return NULL;
}

void *consumer(void *arg) {
  int k = 0;
  while (1) {
    sem_wait(&full);
    sem_wait(&mutex);
    printf("Consumer: Removed [%d]  [ ", arr[k]);
    arr[k] = 0;
    for (int i = 0; i < 10; i++) {
      printf("%d ", arr[i]);
    }
    printf("]\n");
    k = (k + 1) % 10;
    sem_post(&mutex);
    sem_post(&empty);
    sleep(1);
  }
  return NULL;
}

int main() {
  int sem = sem_init(&mutex, 0, 1);
  int emp = sem_init(&empty, 0, 10);
  int ful = sem_init(&full, 0, 0);

  if (sem || emp || ful) {
    printf("ERROR creating the Semaphores !!");
    exit(1);
  }

  pthread_t th1, th2;
  if (pthread_create(&th1, NULL, producer, NULL)) {
    printf("\n ERROR creating thread 1");
    exit(1);
  }
  if (pthread_create(&th2, NULL, consumer, NULL)) {
    printf("\n ERROR creating thread 2");
    exit(1);
  }
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  return 0;
}

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int N, X, in = 0, men = 0, women = 0;
int prevX = 0, waitM = 0, waitW = 0;
char last = 'N';
sem_t mutex, QueM, QueW;

void exitBath() {
  sem_wait(&mutex);
  in--;

  if (men > 0)
    men--;
  else if (women > 0)
    women--;

  if (in == 0) {
    prevX = 0;
    if (last == 'M' && waitW > 0) {
      for (int i = 0; i < N && i < waitW; i++)
        sem_post(&QueW);
    } else if (last == 'W' && waitM > 0) {
      for (int i = 0; i < N && i < waitM; i++)
        sem_post(&QueM);
    } else if (waitM > 0) {
      for (int i = 0; i < N && i < waitM; i++)
        sem_post(&QueM);
    } else if (waitW > 0) {
      for (int i = 0; i < N && i < waitW; i++)
        sem_post(&QueW);
    }
  }
  sem_post(&mutex);
}

void *createMen(void *arg) {
  sem_wait(&mutex);
  waitM++;
  while (women > 0 || in == N || (last == 'M' && prevX >= X && waitW > 0)) {
    sem_post(&mutex);
    sem_wait(&QueM);
    sem_wait(&mutex);
  }
  waitM--;
  men++;
  in++;
  last = 'M';
  prevX++;
  printf("Man entered | Men Inside: %d | Men Waiting : %d | Women Waiting: %d\n", in, waitM, waitW);
  sem_post(&mutex);
  sleep(1);
  printf("Man leaving !!\n");
  exitBath();
}

void *createWoman(void *arg) {
  sem_wait(&mutex);
  waitW++;
  while (men > 0 || in == N || (last == 'W' && prevX >= X && waitM > 0)) {
    sem_post(&mutex);
    sem_wait(&QueW);
    sem_wait(&mutex);
  }
  waitW--;
  women++;
  in++;
  last = 'W';
  prevX++;
  printf("Woman entered | Women Inside: %d | Men Waiting : %d | Women Waiting: %d\n", in, waitM, waitW);
  sem_post(&mutex);
  sleep(1);
  printf("Woman leaving !!\n");
  exitBath();
}

int main() {
  int people;
  printf("Enter capacity N: ");
  scanf("%d", &N);

  printf("Enter starvation limit X: ");
  scanf("%d", &X);

  printf("Enter number of people: ");
  scanf("%d", &people);

  char g[people];

  printf("Enter genders (M/W): ");
  for (int i = 0; i < people; i++)
    scanf(" %c", &g[i]);

  pthread_t t[people];

  sem_init(&mutex, 0, 1);
  sem_init(&QueM, 0, 0);
  sem_init(&QueW, 0, 0);

  for (int i = 0; i < people; i++) {
    if (g[i] == 'M')
      pthread_create(&t[i], NULL, createMen, NULL);
    else if (g[i] == 'W')
      pthread_create(&t[i], NULL, createWoman, NULL);
    else {
      printf("\nInvalid Gender !!");
      return -1;
    }
  }
  for (int i = 0; i < people; i++)
    pthread_join(t[i], NULL);
  return 0;
}

// M W W M M W M M W M W M W W W W M M M W M
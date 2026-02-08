#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int st;
  int end;
} Interval;

int isPrime(int n) {
  if (n <= 1)
    return 0;
  if (n == 2)
    return 1;

  for (int i = 2; i * i <= n; i += 1) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

void *threadfunc(void *arg) {
  Interval *intrvl = (Interval *)arg;

  for (int i = intrvl->st; i <= intrvl->end; i++) {
    if (isPrime(i)) {
      printf("%d\n", i);
    }
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  int num = 100000;
  if (argc != 2) {
    printf("Invalid number of arguments\n");
    return 1;
  }

  int N = atoi(argv[1]);
  pthread_t threads[N];
  Interval intrvl[N];

  int gap = num / N;
  int start = 1;

  for (int i = 0; i < N; i++) {
    intrvl[i].st = start;
    intrvl[i].end = (i == N - 1) ? num : start + gap - 1;

    pthread_create(&threads[i], NULL, threadfunc, &intrvl[i]);
    start += gap;
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
int N, T;

typedef struct {
  int start_row;
  int end_row;
} thread_data;

/* Thread function */
void *multiply(void *arg) {
  thread_data *data = (thread_data *)arg;

  for (int i = data->start_row; i < data->end_row; i++) {
    for (int j = 0; j < N; j++) {
      C[i][j] = 0;
      for (int k = 0; k < N; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t threads[MAX];
  thread_data td[MAX];

  printf("Enter matrix size N: ");
  scanf("%d", &N);

  printf("Enter number of threads: ");
  scanf("%d", &T);

  /* Initialize matrices with random values */
  srand(1);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = rand() % 10;
      B[i][j] = rand() % 10;
    }
  }

  int rows_per_thread = N / T;
  int extra = N % T;
  int current_row = 0;

  /* Create threads */
  for (int i = 0; i < T; i++) {
    td[i].start_row = current_row;
    td[i].end_row = current_row + rows_per_thread + (i < extra ? 1 : 0);
    current_row = td[i].end_row;

    pthread_create(&threads[i], NULL, multiply, &td[i]);
  }

  /* Wait for all threads */
  for (int i = 0; i < T; i++) {
    pthread_join(threads[i], NULL);
  }

  /* Parent prints result */
  printf("\nResultant Matrix C:\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%4d ", C[i][j]);
    }
    printf("\n");
  }

  return 0;
}

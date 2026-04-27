#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int balance;
  pthread_mutex_t mutex;
} BankAccount;

typedef struct {
  int amount;
  char type;
} workArgs;

BankAccount account;

sem_t w_sem;
sem_t r_sem;
int reader_count = 0;

void deposit(int amount) {
  pthread_mutex_lock(&account.mutex);
  printf("> Depositing %d\n", amount);
  int temp = account.balance;
  temp += amount;
  account.balance = temp;
  printf("Balance after deposit: %d\n\n", account.balance);
  pthread_mutex_unlock(&account.mutex);
}

void withdraw(int amount) {
  pthread_mutex_lock(&account.mutex);
  printf("> Withdrawing %d\n", amount);
  int temp = account.balance;
  temp -= amount;
  if (temp < 0) {
    int choice;
    int amnt;
    printf("Insufficient Balance, Withdrawal of %d refused !!\n", amount);
    printf("1.Enter new amount\n2.Skip\nEnter your Choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
      printf("Enter the amount: ");
      scanf("%d", &amnt);
      withdraw(amnt);
    }
  } else {
    account.balance = temp;
    printf("Balance after withdrawal: %d\n\n", account.balance);
  }
  pthread_mutex_unlock(&account.mutex);
}

void acquire_read() {
  sem_wait(&r_sem);
  reader_count++;
  if (reader_count == 1) {
    sem_wait(&w_sem);
  }
  sem_post(&r_sem);
}

void release_read() {
  sem_wait(&r_sem);
  reader_count--;
  if (reader_count == 0) {
    sem_post(&w_sem);
  }
  sem_post(&r_sem);
}

void acquire_write() {
  sem_wait(&w_sem);
}

void release_write() {
  sem_post(&w_sem);
}

void *auditor_thread(void *arg) {
  acquire_read();
  printf("Auditor reading balance: %d\n", account.balance);
  release_read();
  return NULL;
}

void *worker_thread(void *arg) {
  workArgs *w = (workArgs *)arg;

  acquire_write();

  if (w->type == 'D') {
    deposit(w->amount);
  } else if (w->type == 'W') {
    withdraw(w->amount);
  }

  release_write();

  return NULL;
}

int main() {

  printf("Enter the initial balance in the account: ");
  scanf("%d", &account.balance);

  int n;
  printf("Enter the number of workers: ");
  scanf("%d", &n);

  pthread_t workers[n];
  pthread_t auditor;
  workArgs args[n];

  pthread_mutex_init(&account.mutex, NULL);
  sem_init(&w_sem, 0, 1);
  sem_init(&r_sem, 0, 1);

  printf("Enter the amount and mode - \n");
  for (int i = 0; i < n; i++) {
    printf("Worker %d -> ", i + 1);
    scanf("%d %c", &args[i].amount, &args[i].type);
  }

  printf("\nInitial Balance: %d\n\n", account.balance);

  for (int i = 0; i < n; i++) {
    pthread_create(&workers[i], NULL, worker_thread, &args[i]);
  }
  pthread_create(&auditor, NULL, auditor_thread, NULL);

  for (int i = 0; i < n; i++) {
    pthread_join(workers[i], NULL);
  }
  pthread_join(auditor, NULL);

  printf("Final Balance: %d\n\n", account.balance);

  return 0;
}
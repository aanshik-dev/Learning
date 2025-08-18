#include <stdio.h>

int main() {
  int t,
      n = 0,
      m = 1,
      u = 0,
      i;
  printf("Please enter Total Terms: ");
  scanf("%d", &t);
  for (i = 1; i <= t; i++) {
    printf("%d ", n);
    u = n + m;
    n = m;
    m = u;
  }
  return 0;
}

// 0 1 1 2 3 5 8 13